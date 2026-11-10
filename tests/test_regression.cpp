#include "../Source/dsp/GapClass.h"
#include "../Source/dsp/Impact.h"
#include "../Source/dsp/GapDetector.h"
#include "../Source/dsp/InstrumentMixer.h"
#include "../Source/dsp/GapTransition.h"
#include "../Source/dsp/MidiNoteGate.h"
#include "../Source/ui/LayoutGeometry.h"
#include <array>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>

int main() {
  using namespace skell::dsp;
  using skell::ui::Layout::panels;
  static_assert(skell::ui::Layout::valid(),"UI panel layout overlaps");
  // Pixel-space layout at minimum, default, original and large window sizes.
  for(int width : {760,912,1200,1800}) {
    const double scale=double(width)/skell::ui::Layout::designWidth;
    const int height=int(std::lround(skell::ui::Layout::designHeight*scale));
    for(size_t i=0;i<panels.size();++i) {
      auto p=panels[i];
      assert(int(std::ceil(p.right()*scale))<=width+1);
      assert(int(std::ceil(p.bottom()*scale))<=height+1);
      for(size_t j=0;j<i;++j)assert(!skell::ui::Layout::intersects(p,panels[j]));
    }
  }
  // The last of seven rule toggles must remain in the rule panel.
  constexpr int matrixTop=38,rowHeight=18;
  assert(matrixTop+(1+7)*rowHeight<=panels[4].h);
  GapClassLatch latch;
  assert(latch.advance(true,0.20,0.5f,2.0f,4.0f)==0);
  for(double growing : {0.49,0.51,1.9,2.1,4.1,9.0})
    assert(latch.advance(true,growing,0.5f,2.0f,4.0f)==0);
  assert(latch.advance(false,100.0,0.5f,2.0f,4.0f)==-1);
  assert(latch.advance(true,9.0,0.5f,2.0f,4.0f)==3);
  latch.reset();
  assert(latch.advance(true,0.9,0.5f,2.0f,4.0f)==1);
  assert(classifyGapBeats(7.0,0.5f,2.0f,4.0f)==3);
  assert(classifyGapBeats(-1,0.5f,2.0f,4.0f)==0);

  // No MIDI allocations: overlapping notes on independent channels form
  // exactly one gap; repeated note-ons and stray offs are harmless.
  MidiNoteGate gate;
  using Edge=MidiNoteGate::Edge;
  assert(gate.processRaw(0x90,60,100)==Edge::opened);
  assert(gate.processRaw(0x90,60,127)==Edge::none); // duplicate
  assert(gate.processRaw(0x91,60,100)==Edge::none); // independent channel
  assert(gate.processRaw(0x90,67,100)==Edge::none); // overlapping note
  assert(gate.activeCount()==3);
  assert(gate.processRaw(0x80,60,0)==Edge::none);
  assert(gate.processRaw(0x80,60,0)==Edge::none); // stray off
  assert(gate.processRaw(0x91,60,0)==Edge::none); // note-on zero velocity
  assert(gate.activeCount()==1);
  assert(gate.processRaw(0x80,67,0)==Edge::closed);
  assert(gate.processRaw(0xb0,64,127)==Edge::none); // ignore MIDI CC
  assert(gate.activeCount()==0);
  assert(gate.processRaw(0x99,36,100)==Edge::opened);
  gate.reset();
  assert(gate.activeCount()==0);
  assert(gate.processRaw(0x89,36,0)==Edge::none);
  assert(gate.processRaw(0x90,64,100)==Edge::opened);
  assert(gate.processRaw(0x80,64,0)==Edge::closed);

  // A predicted one-beat gap must not fade out at its guessed endpoint;
  // otherwise an extended phrase audibly dips then comes back.
  HistoryBuffer edgeHistory;edgeHistory.prepare(48000.0);
  GapContext estimated{edgeHistory,48000.0,120.0,1000.0,24000.0,23999.0,0.999f,0.5f,0.0f,false};
  assert(gapBoundaryGain(estimated)>0.99f);
  estimated.durationKnown=true;
  assert(gapBoundaryGain(estimated)<0.01f);

  // Confirm sample-wise 5ms fade protects both channels without changing the
  // stereo relationship or leaking wet material indefinitely after the gap.
  GapTransition transition;transition.prepare(48000.0);
  const auto first=transition.process(true,0.8f,-0.6f);
  assert(first[0]>0.0f && first[0]<0.01f);
  assert(std::abs(first[0]/first[1]+4.0f/3.0f)<1.0e-5f);
  for(int i=0;i<260;++i)transition.process(true,0.8f,-0.6f);
  const auto last=transition.process(true,0.8f,-0.6f);
  assert(std::abs(last[0]-0.8f)<1.0e-6f);
  assert(std::abs(last[1]+0.6f)<1.0e-6f);
  const auto release=transition.process(false,0.0f,0.0f);
  assert(release==last);
  for(int i=0;i<260;++i)transition.process(false,0.0f,0.0f);
  assert(transition.process(false,0.0f,0.0f)[0]==0.0f);
  transition.reset();
  assert(transition.process(false,0.0f,0.0f)[0]==0.0f);

  // Exercise impact envelopes at different sample rates. Reset and replay
  // must reproduce exactly the same output (offline bounce determinism).
  for(double sr : {44100.0,48000.0,96000.0,192000.0}) {
    HistoryBuffer unused;unused.prepare(sr);
    Impact impact;impact.prepare(sr);
    std::array<float,512> reference{};
    double energy=0;float peak=0;
    const int n=int(sr*0.5);
    for(int i=0;i<n;++i) {
      GapContext c{unused,sr,120.0,0.0,double(n),double(i),float(i)/float(n),0.5f,0.0f};
      const float out=impact.process(c,0.7f,0.5f,0.7f);
      if(i<512)reference[size_t(i)]=out;
      assert(std::isfinite(out));assert(std::abs(out)<=0.58f);
      peak=std::max(peak,std::abs(out));energy+=double(out)*out;
    }
    assert(peak>0.05f && energy>1.0);
    impact.reset();
    for(int i=0;i<512;++i) {
      GapContext c{unused,sr,120.0,0.0,double(n),double(i),float(i)/float(n),0.5f,0.0f};
      assert(impact.process(c,0.7f,0.5f,0.7f)==reference[size_t(i)]);
    }
  }
  // Real-time stress: all seven instruments together, 2 independent channels,
  // high-energy stereo history, no non-finite samples or sustained overload.
  constexpr double sr=48000.0;
  HistoryBuffer historyL,historyR;historyL.prepare(sr);historyR.prepare(sr);
  for(int i=0;i<int(sr);++i){
    float sample=0.32f*std::sin(float(i)*0.021f)+0.14f*std::sin(float(i)*0.317f);
    historyL.push(sample);historyR.push(-sample*0.75f);
  }
  InstrumentMixer left,right;left.prepare(sr,0);right.prepare(sr,1);
  InstrumentSettings all;
  for(auto& row:all.rules)row.fill(true);
  all.enabled.fill(true);all.levels.fill(0.35f);
  const int n=24000;
  const auto begin=std::chrono::steady_clock::now();
  float peak=0;double power=0;
  for(int i=0;i<n;++i){
    const float progress=float(i)/float(n);
    const GapContext a{historyL,sr,120.0,40000.0,double(n),double(i),progress,1.0f,0.95f};
    const GapContext b{historyR,sr,120.0,40000.0,double(n),double(i),progress,1.0f,0.95f};
    const float l=left.process(a,all,2),r=right.process(b,all,2);
    assert(std::isfinite(l) && std::isfinite(r));
    peak=std::max(peak,std::max(std::abs(l),std::abs(r)));
    power+=double(l)*l+double(r)*r;
  }
  const auto elapsed=std::chrono::duration<double>(std::chrono::steady_clock::now()-begin).count();
  assert(power>0.0001 && peak<2.0f);
  std::cout<<"PASS MIDI overlap/channel gate, layout 760-1800px, gap transition/release, stable class latch, deterministic multi-rate impact, "
           <<"stereo DSP stress: peak="<<peak<<" render="<<elapsed*1000.0
           <<" ms for 500ms stereo audio, CPU ratio="<<elapsed/0.5<<"\n";
  return 0;
}
