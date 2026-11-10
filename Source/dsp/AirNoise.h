#pragma once
#include "InstrumentContext.h"
#include <array>
#include <algorithm>
#include <cmath>

namespace skell::dsp {
// Six-band, real-time-safe spectral air: the input spectrum is tracked continuously
// with low-cost one-pole crossovers. FOLLOW freezes its envelope at the gap edge.
// There are no FFTs, allocations, coefficient calculations or locks in process().
class AirNoise {
public:
  static constexpr size_t bandCount=6;
  using Spectrum=std::array<float,bandCount>;
  void setChannel(int channel) noexcept {initialSeed=channel==0?0x9e3779b9u:0x85ebca6bu;seed=initialSeed;}
  void prepare(double sampleRate) noexcept {
    constexpr std::array<float,5> crossovers{150.0f,430.0f,1200.0f,3400.0f,8500.0f};
    const float rate=float(std::max(8000.0,sampleRate));
    for(size_t i=0;i<crossovers.size();++i)
      alpha[i]=1.0f-std::exp(-6.28318530718f*std::min(crossovers[i],rate*0.43f)/rate);
    // A 400 ms analysis window preserves the timbre of the phrase before silence.
    envelopeAlpha=1.0f-std::exp(-1.0f/(rate*0.4f));
    reset();
  }
  void reset() noexcept {
    analysisLow.fill(0); noiseLow.fill(0); energies.fill(0); profile.fill(1.0f);
    seed=initialSeed; samplesObserved=0;
  }
  // Call on the undelayed source audio, not on generated gap material.
  void observe(float input) noexcept {
    std::array<float,bandCount> bands{};
    split(input,analysisLow,bands);
    for(size_t i=0;i<bandCount;++i)
      energies[i]+=envelopeAlpha*(bands[i]*bands[i]-energies[i]);
    if(samplesObserved<1000000) ++samplesObserved;
  }
  // Called once on each gap. Snapshotting the preceding timbre avoids the
  // filtered noise drifting to the spectrum of the newly arriving instrument.
  Spectrum snapshotProfile() const noexcept {
    float maximum=0;
    for(auto v:energies) maximum=std::max(maximum,v);
    Spectrum snapshot{};
    if(samplesObserved<256 || maximum<1.0e-9f) {snapshot.fill(1.0f);return snapshot;}
    for(size_t i=0;i<bandCount;++i) {
      const float relative=std::sqrt(std::max(0.0f,energies[i])/maximum);
      snapshot[i]=std::clamp(0.15f+1.7f*relative,0.15f,1.85f);
    }
    return snapshot;
  }
  void captureProfile() noexcept {profile=snapshotProfile();}
  void setProfile(const Spectrum& captured) noexcept {profile=captured;}
  void resetPlayback() noexcept {noiseLow.fill(0);}
  float process(const GapContext& c,int color,float shape) noexcept {
    std::array<float,bandCount> bands{};
    split(noise(seed),noiseLow,bands);
    const float brightness=std::clamp(shape,0.0f,1.0f);
    float sample=0;
    for(size_t i=0;i<bandCount;++i){
      const float position=float(i)/float(bandCount-1);
      const float tilt=std::clamp(1.0f+(brightness-0.5f)*(2.0f*position-1.0f)*1.35f,0.20f,1.80f);
      const float weight=color==0?profile[i]:color==1?(1.45f-1.08f*position):1.0f;
      sample+=bands[i]*weight*tilt;
    }
    return std::clamp(sample,-2.0f,2.0f)*envelope(c.progress)*0.15f;
  }
  std::array<float,bandCount> getProfileForTest() const noexcept {return profile;}
private:
  void split(float input,std::array<float,5>& low,std::array<float,bandCount>& bands) noexcept {
    float previous=0;
    for(size_t i=0;i<low.size();++i){
      low[i]+=alpha[i]*(input-low[i]);
      bands[i]=low[i]-previous;
      previous=low[i];
    }
    bands.back()=input-previous;
  }
  std::array<float,5> alpha{},analysisLow{},noiseLow{};
  std::array<float,bandCount> energies{},profile{};
  float envelopeAlpha=0.0001f;
  uint32_t seed=0x9e3779b9u,initialSeed=0x9e3779b9u;
  int samplesObserved=0;
};
}
