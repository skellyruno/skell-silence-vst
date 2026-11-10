#pragma once
#include "TapeStop.h"
#include "AirNoise.h"
#include "NoiseFade.h"
#include "ReverseSwell.h"
#include "Impact.h"
#include "Riser.h"
#include "StutterTail.h"
#include "Reverb.h"
#include <array>
#include <algorithm>

namespace skell::dsp {
inline constexpr std::array<const char*,7> instrumentIds {"tape","air","swell","noise","impact","riser","stutter"};
inline constexpr std::array<const char*,7> instrumentNames {"TAPE STOP","FILTERED AIR","REVERSE SWELL","NOISE FADE","IMPACT","RISER","STUTTER TAIL"};
inline constexpr std::array<const char*,4> classNames {"SHORT","MEDIUM","LONG","EXTRA LONG"};
struct InstrumentSettings {
  std::array<bool,7> enabled{};
  std::array<float,7> levels{};
  std::array<std::array<bool,4>,7> rules{};
  float stopSpeedCurve=0.4f,stopTime=0.4f,stopLowpass=0.7f;
  int airColor=0;float airShape=0.5f;
  float swellLength=500,swellReverb=0.5f;
  int noiseType=1;float noiseFadeIn=0.18f,noiseFadeOut=0.18f;
  float impactPitch=0.3f,impactDecay=0.5f,impactClick=0.4f;
  float riserStart=0.4f,riserCurve=0.5f,riserNoiseMix=0.8f;
  int stutterDiv=2,stutterCount=6;float stutterDecay=0.22f;
};
// Only taper toward a gap end when that end has actually been detected or
// loaded from a learned map. A guessed end is not a reliable fade boundary.
inline float gapBoundaryGain(const GapContext& c) noexcept {
  const double fromStart=std::max(0.0,c.time);
  const double remaining=c.durationKnown?std::max(0.0,c.length-c.time):fromStart;
  return std::clamp(float(std::min(fromStart,remaining)/c.sampleRate*200.0),0.0f,1.0f);
}
class InstrumentMixer {
public:
  void prepare(double sampleRate,int channel=0) {
    air.setChannel(channel);fade.setChannel(channel);riser.setChannel(channel);impact.setChannel(channel);
    reverb.prepare(sampleRate);air.prepare(sampleRate);impact.prepare(sampleRate);reset();
  }
  void reset() {beginGap();air.reset();reverb.reset();}
  void beginGap(const AirNoise::Spectrum* frozenProfile=nullptr) noexcept {
    stop.reset();
    if(frozenProfile!=nullptr)air.setProfile(*frozenProfile);
    else air.captureProfile();
    air.resetPlayback();fade.reset();impact.reset();riser.reset();stutter.reset();
  }
  void observeInput(float sample) noexcept {air.observe(sample);}
  AirNoise::Spectrum snapshotSpectrum() const noexcept {return air.snapshotProfile();}
  float process(const GapContext& c, const InstrumentSettings& p,int lengthClass) noexcept {
    const auto allowed=[&](int i){return p.enabled[size_t(i)] && p.rules[size_t(i)][size_t(lengthClass)];};
    float v=0, wetFeed=0;
    const float t=0.55f+c.tension*0.9f;
    if(allowed(0)) v+=p.levels[0]*stop.process(c,p.stopSpeedCurve,p.stopTime,p.stopLowpass);
    if(allowed(1)) v+=p.levels[1]*air.process(c,p.airColor,p.airShape);
    if(allowed(2)) {float s=swell.process(c,p.swellLength,p.swellReverb)*t;v+=p.levels[2]*s;wetFeed+=p.levels[2]*s;}
    if(allowed(3)) v+=p.levels[3]*fade.process(c,p.noiseType,p.noiseFadeIn,p.noiseFadeOut);
    if(allowed(4)) {
      auto hit=c;
      if(lengthClass==3) { // Extra-long gaps: impact on the final beat.
        const double onset=std::max(0.0,c.length-c.sampleRate*60.0/std::max(20.0,c.bpm));
        hit.time=c.time-onset;
      }
      if(hit.time>=0 && hit.time<c.sampleRate*0.75)
        v+=p.levels[4]*impact.process(hit,p.impactPitch,p.impactDecay,p.impactClick);
    }
    if(allowed(5)) v+=p.levels[5]*riser.process(c,p.riserStart,p.riserCurve,p.riserNoiseMix)*t;
    if(allowed(6)) {float s=stutter.process(c,p.stutterDiv,p.stutterDecay,p.stutterCount);v+=p.levels[6]*s;wetFeed+=p.levels[6]*s;}
    const float bloom=reverb.process(wetFeed,c.space);
    v+=bloom*c.space*0.5f*(1.0f-c.progress*c.progress);
    const float edge=gapBoundaryGain(c); // 5 ms on known boundaries
    return v*edge;
  }
  float tail(float space) noexcept { return reverb.process(0,space)*space*0.12f; }
private:
  TapeStop stop;AirNoise air;ReverseSwell swell;NoiseFade fade;Impact impact;Riser riser;StutterTail stutter;Reverb reverb;
};
}
