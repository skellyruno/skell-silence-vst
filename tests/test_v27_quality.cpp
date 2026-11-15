#include "../Source/dsp/InstrumentMixer.h"
#include "../Source/dsp/GapTransition.h"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>

int main() {
  using namespace skell::dsp;
  constexpr float pi=3.14159265358979323846f;
  // The new shared edge envelope has zero slope at both endpoints.
  assert(smoothstepUnit(-1.0f)==0.0f);
  assert(smoothstepUnit(0.0f)==0.0f);
  assert(smoothstepUnit(0.5f)==0.5f);
  assert(smoothstepUnit(1.0f)==1.0f);
  assert(smoothstepUnit(2.0f)==1.0f);
  assert(smoothstepUnit(1.0f/240.0f)<0.0001f);
  float last=0;
  for(int i=0;i<=1000;++i){
    const auto gain=smoothstepUnit(float(i)/1000.0f);
    assert(gain>=last && gain<=1.0f);
    last=gain;
  }
  double allEnergy=0.0;
  for(double rate : {44100.0,48000.0,96000.0,192000.0}){
    HistoryBuffer vocal;vocal.prepare(rate);
    const int n=int(rate*1.7);
    // Preceding phrase contains consonant-like partials and a decaying tail.
    for(int i=0;i<n;++i){
      const float t=float(i)/float(rate);
      const float sample=0.22f*std::sin(2*pi*180.0f*t)
        +0.06f*std::sin(2*pi*3200.0f*t)
        +0.035f*std::sin(2*pi*6700.0f*t);
      vocal.push(sample);
    }
    const double start=rate*1.2, length=rate*0.7;
    // Every instrument is checked independently across host sample rates.
    for(int instrument=0;instrument<7;++instrument){
      InstrumentSettings solo{};
      solo.enabled[size_t(instrument)]=true;
      solo.rules[size_t(instrument)][2]=true;
      solo.levels[size_t(instrument)]=0.7f;
      solo.stopTime=0.35f;
      solo.swellLength=280.0f;
      solo.stutterDiv=2;solo.stutterCount=6;
      InstrumentMixer mixer;mixer.prepare(rate,0);mixer.beginGap();
      double energy=0.0;float peak=0;
      const int frames=std::min(int(rate*0.45),12000);
      for(int i=0;i<frames;++i){
        const float progress=float(i)/float(length);
        const GapContext c{vocal,rate,120.0,start,length,double(i),
                           progress,0.6f,0.75f,true};
        const float out=mixer.process(c,solo,2);
        assert(std::isfinite(out));
        assert(std::abs(out)<2.0f);
        peak=std::max(peak,std::abs(out));
        energy+=double(out)*out;
        if(i==0)assert(out==0.0f);
      }
      assert(energy>1.0e-13);
      assert(peak>1.0e-6f);
      allEnergy+=energy;
    }

    // Tape STOP must actually stop by the chosen time even in a long gap;
    // the old implementation held a nonzero sample for many extra seconds.
    TapeStop tape;
    const int stopSamples=int(rate*0.25);
    float nearEnd=1.0f;float earlyPeak=0.0f;
    for(int i=0;i<stopSamples+int(rate*0.25);++i){
      const GapContext c{vocal,rate,120.0,start,rate*2.0,double(i),
                         float(i)/(float(rate)*2.0f),0.5f,0.2f,true};
      const float out=tape.process(c,0.4f,0.25f,0.8f);
      assert(std::isfinite(out));
      if(i>int(rate*0.03) && i<int(rate*0.13))
        earlyPeak=std::max(earlyPeak,std::abs(out));
      if(i==stopSamples-1)nearEnd=std::abs(out);
      if(i>=stopSamples)assert(out==0.0f);
    }
    assert(earlyPeak>0.001f);
    assert(nearEnd<0.01f);

    // Impact first called late (lookahead OFF) must match an engine that
    // processed every prior sample, rather than replaying a full-level hit.
    Impact sequential,seek;
    sequential.prepare(rate);seek.prepare(rate);
    const int offset=int(rate*0.12);
    for(int i=0;i<offset;++i){
      const GapContext c{vocal,rate,120.0,start,length,double(i),
                         float(i)/float(length),0.5f,0.3f,true};
      sequential.process(c,0.62f,0.55f,0.0f);
    }
    const GapContext late{vocal,rate,120.0,start,length,double(offset),
                          float(offset)/float(length),0.5f,0.3f,true};
    const float reference=sequential.process(late,0.62f,0.55f,0.0f);
    const float resumed=seek.process(late,0.62f,0.55f,0.0f);
    assert(std::isfinite(reference) && std::isfinite(resumed));
    assert(std::abs(reference-resumed)<0.035f);
    assert(std::abs(resumed)<0.48f);
    // Seek backwards mid-phrase: the same analytic state must be restored.
    const GapContext restart{vocal,rate,120.0,start,length,0.0,
                             0.0f,0.5f,0.3f,true};
    const float resetOnSeek=seek.process(restart,0.62f,0.55f,0.0f);
    Impact clean;clean.prepare(rate);
    assert(resetOnSeek==clean.process(restart,0.62f,0.55f,0.0f));

    // Grain taper is silent at the exact slice seams; no held edge samples.
    StutterTail stutter;stutter.reset();
    const GapContext seam{vocal,rate,120.0,start,length,0.0,
                          0.0f,0.5f,0.3f,true};
    assert(stutter.process(seam,2,0.2f,6)==0.0f);
    const int sliceSamples=int(rate*0.5/8.0);
    const GapContext nextSeam{vocal,rate,120.0,start,length,
                              double(sliceSamples),float(sliceSamples)/float(length),
                              0.5f,0.3f,true};
    assert(std::abs(stutter.process(nextSeam,2,0.2f,6))<0.002f);

    // Noise fades enter and exit exactly at zero, at every sample rate.
    NoiseFade fade;fade.setChannel(0);fade.reset();
    const GapContext startC{vocal,rate,120.0,start,length,0.0,0.0f,0.5f,0.3f,true};
    const GapContext endC{vocal,rate,120.0,start,length,length,1.0f,0.5f,0.3f,true};
    assert(fade.process(startC,1,0.2f,0.2f)==0.0f);
    assert(fade.process(endC,1,0.2f,0.2f)==0.0f);

    // Known gap boundaries: slope-softened 5ms entry/exit, no guessed end.
    auto g=startC;
    assert(gapBoundaryGain(g)==0.0f);
    g.time=1.0;assert(gapBoundaryGain(g)<0.0002f);
    g.time=length-1.0;assert(gapBoundaryGain(g)<0.0002f);
    g.durationKnown=false;
    assert(gapBoundaryGain(g)>0.999f);
  }
  assert(allEnergy>0.01);
  std::cout<<"PASS v2.7 all seven isolated effects at 44.1/48/96/192 kHz,"
           <<" stop-time silence, late Impact phase, stutter seams and C1 edges"
           <<" energy="<<allEnergy<<"\\n";
}
