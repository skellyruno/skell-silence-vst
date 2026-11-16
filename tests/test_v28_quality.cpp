#include "../Source/dsp/GapDetector.h"
#include "../Source/dsp/InstrumentMixer.h"
#include "../Source/dsp/Reverb.h"
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <array>

int main() {
  using namespace skell::dsp;
  constexpr double pi=3.14159265358979323846;
  for(const double rate : {44100.0,48000.0,96000.0,192000.0}) {
    // Synthetic vocal phrase, 250-300ms pauses, then another voiced phrase.
    // Onsets are checked against the *source* silence, not against the
    // detector's delayed 10ms RMS envelope.
    GapDetector detector;detector.prepare(rate);
    DetectorSettings s;
    s.thresholdDb=20.0f;s.minGapMs=70.0f;s.maxGapMs=1600.0f;
    s.holdMs=25.0f;s.armTimeSeconds=0.2f;s.tailSensitivity=0.6f;
    std::array<int64_t,2> beginnings{{-1,-1}},endings{{-1,-1}};
    int starts=0,ends=0;
    const int64_t silence1=int64_t(rate*0.65);
    const int64_t silence2=int64_t(rate*1.65);
    for(int64_t i=0;i<int64_t(rate*2.5);++i) {
      const bool quiet=(i>=silence1 && i<int64_t(rate*0.90)) ||
                       (i>=silence2 && i<int64_t(rate*1.95));
      const float source=quiet?0.0f:
        0.29f*std::sin(float(2.0*pi*210.0*double(i)/rate));
      const auto out=detector.processStereo(source,-0.8f*source,i,s);
      if(out.began){if(starts<2)beginnings[size_t(starts)]=out.start;++starts;}
      if(out.ended){if(ends<2)endings[size_t(ends)]=out.end;++ends;}
      assert(std::isfinite(out.fast) && std::isfinite(out.slow) &&
             std::isfinite(out.threshold));
    }
    assert(starts==2 && ends==2);
    assert(beginnings[0]>=silence1 && beginnings[0]<silence1+int64_t(rate*0.025));
    assert(beginnings[1]>=silence2 && beginnings[1]<silence2+int64_t(rate*0.025));
    assert(endings[0]>beginnings[0] && endings[1]>beginnings[1]);

    // Repeated short rests and drum-style tails may not become gaps
    // when the user selected a 90ms minimum gap.
    GapDetector percussion;percussion.prepare(rate);
    s.minGapMs=90.0f;
    int falseStarts=0;
    for(int64_t i=0;i<int64_t(rate*2.0);++i) {
      const int64_t phase=i%int64_t(rate*0.2);
      const bool quiet=phase>=int64_t(rate*0.16);
      const float pulse=quiet?0.0f:
        0.32f*std::sin(float(2.0*pi*260.0*double(i)/rate));
      if(percussion.process(pulse,i,s).began)++falseStarts;
    }
    assert(falseStarts==0);
  }

  // Smooth automation is sample accurate and reaches exactly zero in 10ms
  // even when toggling rule/enable during an active stutter grain.
  constexpr double sr=48000.0;
  HistoryBuffer input;input.prepare(sr);
  for(int i=0;i<48000;++i)input.push(0.22f*std::sin(float(i)*0.037f));
  InstrumentMixer mixer;mixer.prepare(sr,0);
  InstrumentSettings cfg{};
  cfg.enabled[6]=true;cfg.rules[6][0]=true;cfg.levels[6]=1.0f;
  cfg.stutterCount=16;cfg.stutterDiv=1;
  double soundBefore=0.0,soundAfter=0.0;
  constexpr int muteAt=1800,unmuteAt=3700;
  for(int i=0;i<6500;++i){
    if(i==muteAt)cfg.enabled[6]=false;
    if(i==unmuteAt)cfg.enabled[6]=true;
    GapContext c{input,sr,120.0,47000.0,12000.0,double(i),
                 float(i)/12000.0f,0.3f,0.0f,true};
    const float output=mixer.process(c,cfg,0);
    assert(std::isfinite(output));
    if(i>700 && i<muteAt)soundBefore+=double(output)*output;
    if(i>unmuteAt+500 && i<6000)soundAfter+=double(output)*output;
    if(i>muteAt+510 && i<unmuteAt)assert(output==0.0f);
  }
  assert(soundBefore>0.001 && soundAfter>0.001);

  // An FDN tail must not be truncated near the audible decay; sleep only
  // after all delay rings and feedback/damping states have become exact zero.
  Reverb tail;tail.prepare(sr);
  assert(tail.isIdle());
  tail.process(1.0f,0.95f);
  assert(!tail.isIdle());
  double tailEnergy=0.0;
  const int duration=int(sr*24.0);
  int firstIdle=-1;
  for(int i=0;i<duration;++i){
    const float out=tail.process(0.0f,0.95f);
    assert(std::isfinite(out));
    if(i>sr*0.1 && i<sr*1.0)tailEnergy+=double(out)*out;
    if(tail.isIdle()){firstIdle=i;break;}
  }
  assert(tailEnergy>1.e-9);
  assert(firstIdle>=int(sr*1.0) && firstIdle<duration);
  for(int i=0;i<4096;++i)assert(tail.process(0.0f,0.95f)==0.0f);

  // Re-exciting a fully slept FDN must sound identical to a new instance.
  Reverb fresh;fresh.prepare(sr);
  for(int i=0;i<8000;++i){
    const float impulse=i==0?0.35f:0.0f;
    const float a=tail.process(impulse,0.6f);
    const float b=fresh.process(impulse,0.6f);
    assert(std::abs(a-b)<1.e-6f);
  }

  std::cout<<"PASS v2.8: four sample-rate vocal/drum detector events, "
           <<"10ms live automation slew, inaudible FDN idle/re-excitation, "
           <<"tailEnergy="<<tailEnergy<<" idleAt="<<double(firstIdle)/sr<<"s\n";
}
