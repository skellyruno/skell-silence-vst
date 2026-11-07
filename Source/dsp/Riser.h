#pragma once
#include "InstrumentContext.h"
namespace skell::dsp {
class Riser {
public:
 void reset() noexcept { low=0;seed=0x713fe78d;phase=0; }
 float process(const GapContext& c,float start,float curve,float mix) noexcept {
   const float t=std::pow(c.progress,0.25f+3.75f*curve);
   const float n=noise(seed),cut=200.0f+(10000.0f-start*9000.0f)*t;
   low+=std::min(1.0f,float(6.2831853*cut/c.sampleRate))*(n-low);
   phase+=float(6.2831853*(150.0+1800.0*t)/c.sampleRate);if(phase>6.2831853f)phase-=6.2831853f;
   return t*(mix*0.25f*low+(1.0f-mix)*0.10f*std::sin(phase));
 }
private: float low=0,phase=0;uint32_t seed=0x713fe78d;
};
}
