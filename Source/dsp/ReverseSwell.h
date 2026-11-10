#pragma once
#include "InstrumentContext.h"
namespace skell::dsp {
class ReverseSwell {
public:
 float process(const GapContext& c,float lengthMs,float reverb) const noexcept {
   const double span=std::min(double(lengthMs)*c.sampleRate/1000.0,c.sampleRate*2.0);
   const double pos=c.start-1.0-c.progress*span;
   const float v=c.history.readCubic(pos);
   return v*c.progress*c.progress*(0.7f+0.3f*reverb);
 }
};
}
