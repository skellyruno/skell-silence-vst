#pragma once
#include "InstrumentContext.h"
namespace skell::dsp {
class ReverseSwell {
public:
 // Reverse a fixed pre-gap window, stretched onto the detected/learned gap.
 // This reaches the end of the source window near the next hit. The shared
 // mixer supplies a 5ms boundary crossfade to prevent clicks at the hit.
 float process(const GapContext& c,float lengthMs,float reverb) const noexcept {
   if(c.length<=1.0 || c.time<0.0 || c.start<1.0) return 0.0f;
   const double span=std::min({std::max(1.0,double(lengthMs)*c.sampleRate/1000.0),
                                c.sampleRate*2.0, std::max(1.0,c.start-1.0)});
   const double phase=std::clamp(c.time/c.length,0.0,1.0);
   const double pos=c.start-1.0-phase*span;
   const float eased=float(phase*phase*(3.0-2.0*phase));
   return c.history.readCubic(pos)*eased*(0.7f+0.3f*reverb);
 }
};
}
