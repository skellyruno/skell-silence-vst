#pragma once
#include "InstrumentContext.h"
namespace skell::dsp {
class AirNoise {
public:
  void reset() noexcept {low=0; seed=0x9e3779b9;}
  float process(const GapContext& c, int color,float shape) noexcept {
    const float n=noise(seed),a=std::min(1.0f,float(6.2831853*std::clamp(300.0f+shape*9000.0f,100.0f,20000.0f)/c.sampleRate));
    low+=a*(n-low);
    const float shaped=color==2?n:(color==1?low:0.6f*low+0.4f*n);
    return shaped*envelope(c.progress)*0.17f;
  }
private: float low=0;uint32_t seed=0x9e3779b9;
};
}
