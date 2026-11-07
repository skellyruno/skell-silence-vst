#pragma once
#include "InstrumentContext.h"
namespace skell::dsp {
class Impact {
public:
 void reset() noexcept { phase=0;seed=0x673892ab; }
 float process(const GapContext& c,float pitch,float decay,float click) noexcept {
   const double age=c.time;
   if(age>c.sampleRate*2.0) return 0;
   const float f=35.0f+pitch*150.0f*std::exp(-age/(c.sampleRate*0.045));
   phase+=float(6.283185307*f/c.sampleRate); if(phase>6.283185307f)phase-=6.283185307f;
   const float body=std::sin(phase)*std::exp(-float(age/c.sampleRate)*(2.0f+decay*10.0f));
   const float snap=noise(seed)*std::exp(-float(age/c.sampleRate)*110.0f)*click;
   return 0.48f*body+0.08f*snap;
 }
private:float phase=0;uint32_t seed=0x673892ab;
};
}
