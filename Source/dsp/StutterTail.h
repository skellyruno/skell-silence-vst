#pragma once
#include "InstrumentContext.h"
namespace skell::dsp {
class StutterTail {
public:
 void reset() noexcept {lastIndex=-1;lastDecay=-1.0f;cachedGain=1.0f;}
 float process(const GapContext& c, int div,float decay,int count) noexcept {
   const double beats=60.0/std::max(20.0,c.bpm);
   const double slice=std::max(30.0,beats*c.sampleRate/std::pow(2.0,double(div+1)));
   const auto index=int(c.time/slice);
   if(index>=count) return 0;
   // The gain changes once per grain rather than recomputing pow() for every sample.
   if(index!=lastIndex || decay!=lastDecay) {
     lastIndex=index;lastDecay=decay;
     cachedGain=std::pow(std::max(0.0f,1.0f-decay),index);
   }
   const double offset=c.time-double(index)*slice;
   const double phase=std::clamp(offset/slice,0.0,1.0);
   const float taper=float(std::clamp(std::min(phase,1.0-phase)*18.0,0.0,1.0));
   return c.history.readCubic(c.start-slice+offset)*cachedGain*taper;
 }
private:
 int lastIndex=-1;
 float lastDecay=-1.0f,cachedGain=1.0f;
};
}
