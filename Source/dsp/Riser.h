#pragma once
#include "InstrumentContext.h"
namespace skell::dsp {
class Riser {
public:
 void setChannel(int channel) noexcept {initialSeed=channel==0?0x713fe78du:0x8f1bbcdcu;seed=initialSeed;}
 void reset() noexcept { low=0;seed=initialSeed;phase=0; }
 float process(const GapContext& c,float start,float curve,float mix) noexcept {
   // Piecewise interpolated power curve (1/4, 1, 2, 4) avoids the
   // expensive pow() call on every sample while retaining a useful sweep.
   const float progress=std::clamp(c.progress,0.0f,1.0f);
   const float x2=progress*progress, x4=x2*x2;
   const float bend=std::clamp(curve,0.0f,1.0f)*3.0f;
   float t=0.0f;
   if(bend<1.0f){const float quick=std::sqrt(std::sqrt(progress));t=quick+(progress-quick)*bend;}
   else if(bend<2.0f)t=progress+(x2-progress)*(bend-1.0f);
   else t=x2+(x4-x2)*(bend-2.0f);
   const float n=noise(seed),cut=200.0f+(10000.0f-start*9000.0f)*t;
   low+=std::min(1.0f,float(6.2831853*cut/c.sampleRate))*(n-low);
   phase+=float(6.2831853*(150.0+1800.0*t)/c.sampleRate);if(phase>6.2831853f)phase-=6.2831853f;
   return t*(mix*0.25f*low+(1.0f-mix)*0.10f*std::sin(phase));
 }
private: float low=0,phase=0;uint32_t seed=0x713fe78du,initialSeed=0x713fe78du;
};
}
