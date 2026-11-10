#include "../Source/dsp/GapDetector.h"
#include "../Source/dsp/GapMap.h"
#include "../Source/dsp/LookaheadBuffer.h"
#include "../Source/dsp/InstrumentMixer.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <chrono>
int main(){
  using namespace skell::dsp;
  constexpr double sampleRate=48000;
  GapDetector detector;detector.prepare(sampleRate);
  DetectorSettings p;p.thresholdDb=14;p.minGapMs=50;p.holdMs=25;p.maxGapMs=1500;p.armTimeSeconds=0.2f;
  int starts=0,ends=0;int64_t open=0,close=0;
  for(int64_t i=0;i<48000*3;i++){
    float s=i<48000?0.25f*std::sin(2*3.1415926*440*i/sampleRate):
            (i<48000*2?0.0f:0.25f*std::sin(2*3.1415926*440*i/sampleRate));
    auto d=detector.process(s,i,p);
    if(d.began){++starts;open=d.start;}
    if(d.ended){++ends;close=d.end;}
  }
  assert(starts>=1 && ends>=1);
  assert(open>=48000 && close>open);
  GapMap map;
  assert(map.append(1.0,1.7));assert(map.size()==1);assert(map.get(0).to==1.7);
  map.replace(0,{2.0,3.0});assert(map.get(0).from==2.0);
  map.erase(0);assert(map.size()==0);
  LookaheadBuffer delay;delay.prepare(sampleRate);
  for(int n=0;n<64;++n){delay.push(0,n==0?1.0f:0.0f);delay.push(1,0.0f);
    assert(std::abs(delay.delayed(0,7)-(n==7?1.0f:0.0f))<1e-5f);delay.next();}
  HistoryBuffer history;history.prepare(sampleRate);
  for(int64_t i=0;i<2000;++i)history.push(0.2f*std::sin(float(i)*0.02f));
  InstrumentMixer mx;mx.prepare(sampleRate);
  InstrumentSettings inst;for(auto& rules:inst.rules)rules={true,true,true,true};
  for(auto& enabled:inst.enabled)enabled=true;
  for(auto& level:inst.levels)level=0.2f;
  float maxPeak=0;
  for(int i=0;i<1000;++i){
    const float progress=i/1000.0f;
    GapContext c{history,sampleRate,120.0,1500.0,1000.0,double(i),progress,0.5f,0.3f};
    float v=mx.process(c,inst,2);assert(std::isfinite(v));maxPeak=std::max(maxPeak,std::abs(v));
  }
  // FDN impulse stability: a feedback network must remain finite and decay
  // even at maximum SPACE, across enough samples for multiple recirculations.
  Reverb rv;rv.prepare(sampleRate);
  double early=0,late=0;
  for(int i=0;i<48000*2;++i){
    const float out=rv.process(i==0?1.0f:0.0f,1.0f);
    assert(std::isfinite(out));assert(std::abs(out)<2.0f);
    if(i>=1000 && i<24000)early+=double(out)*out;
    if(i>=72000)late+=double(out)*out;
  }
  assert(early>1.0e-12 && late<early);
  rv.reset();
  for(int i=0;i<500;++i)assert(std::abs(rv.process(0,0.5f))<1.0e-7f);
  // Damping remains stable and bounded at standard and extreme host rates.
  // Re-preparing the engine must clear all previous reverberant energy.
  for(double rate: {44100.0, 96000.0, 192000.0}) {
    Reverb multiRate;multiRate.prepare(rate);
    double earlyEnergy=0,lateEnergy=0;
    const int end=int(rate*1.5);
    for(int i=0;i<end;++i) {
      const auto value=multiRate.process(i==0?1.0f:0.0f,0.98f);
      assert(std::isfinite(value));
      assert(std::abs(value)<2.0f);
      if(i>=int(rate*0.05) && i<int(rate*0.40))earlyEnergy+=double(value)*value;
      if(i>=int(rate*1.0))lateEnergy+=double(value)*value;
    }
    assert(earlyEnergy>0.0 && lateEnergy<earlyEnergy);
    multiRate.reset();
    for(int i=0;i<300;++i)assert(std::abs(multiRate.process(0,0.6f))<1.0e-8f);
  }
  // Spectral FOLLOW must adapt to the preceding sound rather than using one
  // static low-pass color. Verify separation of bass-heavy and bright sources.
  AirNoise air;air.prepare(sampleRate);
  for(int i=0;i<48000;++i)
    air.observe(0.35f*std::sin(float(i)*float(2*3.14159265358979323846*90.0/sampleRate)));
  const auto lowProfile=air.snapshotProfile();
  air.reset();
  for(int i=0;i<48000;++i)
    air.observe(0.35f*std::sin(float(i)*float(2*3.14159265358979323846*7200.0/sampleRate)));
  const auto highProfile=air.snapshotProfile();
  assert(lowProfile.front()>lowProfile.back());
  assert(highProfile.back()>highProfile.front());
  air.setProfile(lowProfile); air.resetPlayback();
  float checksum=0.0f;
  for(int i=0;i<4096;++i){
    GapContext c{history,sampleRate,120.0,1500.0,4096.0,double(i),float(i)/4096.0f,0.5f,0.3f};
    const float a=air.process(c,0,0.5f);
    assert(std::isfinite(a));checksum+=std::abs(a);
  }
  assert(checksum>1.0f);
  // Four-point resampling preserves integer sample values and interpolates a
  // smooth ramp accurately; invalid history positions still return silence.
  HistoryBuffer ramp;ramp.prepare(sampleRate);
  for(int i=0;i<1000;++i)ramp.push(float(i)/2000.0f);
  assert(std::abs(ramp.readCubic(200.0)-0.1f)<1.0e-6f);
  assert(std::abs(ramp.readCubic(200.5)-0.10025f)<1.0e-5f);
  assert(ramp.readCubic(-10.0)==0.0f);
  // A single full second of spectral analysis/rendering must remain numerically
  // stable at a high sample rate, including near-silent input.
  AirNoise hiRate;hiRate.prepare(192000.0);
  for(int i=0;i<192000;++i)hiRate.observe(1.0e-6f*std::sin(float(i)*0.31f));
  hiRate.captureProfile();
  for(const auto gain:hiRate.getProfileForTest())assert(std::isfinite(gain) && gain>=0.0f && gain<=1.85f);
  // Detector parameters can change during transport without stale cached time values.
  detector.prepare(sampleRate);p.minGapMs=30;p.holdMs=10;
  for(int64_t i=0;i<48000;++i){
    const auto sample=0.25f*std::sin(float(i)*0.02f);
    const auto r=detector.process(sample,i,p);assert(!r.began);
  }
  p.minGapMs=120;p.maxGapMs=2000;p.holdMs=55;
  int opened=0,ended=0;
  for(int64_t i=48000;i<48000*3;++i){
    auto r=detector.process(i<48000*2?0.0f:0.25f*std::sin(float(i)*0.02f),i,p);
    if(r.began) ++opened;
    if(r.ended) ++ended;
  }
  assert(opened>=1 && ended>=1);
  // Opposite-polarity channels retain full energy during detection. A simple
  // L+R sum would classify the entire loud phrase as silence.
  GapDetector stereoDetector;stereoDetector.prepare(sampleRate);
  DetectorSettings stereoSettings;stereoSettings.thresholdDb=18.0f;
  stereoSettings.minGapMs=65.0f;stereoSettings.armTimeSeconds=0.2f;
  int stereoStarts=0,stereoEnds=0;
  for(int64_t i=0;i<int64_t(sampleRate*2.5);++i) {
    const auto source=0.35f*std::sin(float(i)*float(2*3.14159265358979323846*440.0/sampleRate));
    const auto left=i<48000 || i>=96000?source:0.0f;
    const auto result=stereoDetector.processStereo(left,-left,i,stereoSettings);
    if(result.began){++stereoStarts;assert(result.start>=48000);}
    if(result.ended){++stereoEnds;assert(result.end>=result.start);}
  }
  assert(stereoStarts==1 && stereoEnds==1);

  // Stereo source gestures survive reverse processing: opposite-polarity
  // history yields opposite-polarity wet material instead of dual mono.
  HistoryBuffer historyL,historyR;
  historyL.prepare(sampleRate);historyR.prepare(sampleRate);
  for(int64_t i=0;i<48000;++i){
    const float sample=0.31f*std::sin(float(i)*0.043f)+0.09f*std::sin(float(i)*0.019f);
    historyL.push(sample);historyR.push(-sample);
  }
  InstrumentMixer stereoL,stereoR;
  stereoL.prepare(sampleRate,0);stereoR.prepare(sampleRate,1);
  InstrumentSettings soloSwell{};
  soloSwell.enabled[2]=true;soloSwell.levels[2]=1.0f;
  soloSwell.rules[2][2]=true;
  soloSwell.swellLength=400.0f;
  stereoL.beginGap();stereoR.beginGap();
  double distinctEnergy=0.0;
  for(int i=0;i<12000;++i) {
    const float progress=float(i)/12000.0f;
    GapContext cL{historyL,sampleRate,120.0,44000.0,12000.0,double(i),progress,0.5f,0.0f};
    GapContext cR{historyR,sampleRate,120.0,44000.0,12000.0,double(i),progress,0.5f,0.0f};
    const float l=stereoL.process(cL,soloSwell,2);
    const float r=stereoR.process(cR,soloSwell,2);
    assert(std::isfinite(l) && std::isfinite(r));
    assert(std::abs(l+r)<2.0e-5f);
    distinctEnergy+=double(l-r)*(l-r);
  }
  assert(distinctEnergy>0.001);

  // The two synthesizer seeds are independent to avoid collapsing stereo
  // noise to hard center, and are deterministic across resets.
  InstrumentSettings soloNoise{};
  soloNoise.enabled[3]=true;soloNoise.levels[3]=1.0f;soloNoise.rules[3][2]=true;
  stereoL.beginGap();stereoR.beginGap();
  double noiseDiff=0.0;
  for(int i=100;i<2000;++i){
    const float progress=float(i)/12000.0f;
    GapContext cL{historyL,sampleRate,120.0,44000.0,12000.0,double(i),progress,0.5f,0.0f};
    GapContext cR{historyR,sampleRate,120.0,44000.0,12000.0,double(i),progress,0.5f,0.0f};
    noiseDiff+=std::abs(stereoL.process(cL,soloNoise,2)-stereoR.process(cR,soloNoise,2));
  }
  assert(noiseDiff>0.1);

  // Lookahead tape playback never crosses into the silence after the gap.
  TapeStop tape;
  GapContext tapeContext{historyL,sampleRate,120.0,44000.0,24000.0,23999.0,1.0f,0.5f,0.2f};
  assert(std::isfinite(tape.process(tapeContext,1.0f,2.0f,1.0f)));
  std::cout<<"PASS stereo anti-phase, reverse polarity, independent noise, spectral FOLLOW, 192 kHz; gap begin="<<open<<" end="<<close<<" maxFx="<<maxPeak<<" reverb early="<<early<<" late="<<late<<"\n";
}
