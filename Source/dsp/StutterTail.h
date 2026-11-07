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
   const auto phase=std::fmod(c.time,slice)/slice;
   const float taper=float(std::min(1.0, std::min(phase*18.0,(1-phase)*18.0)));
   return c.history.read(c.start-slice+std::fmod(c.time,slice))*cachedGain*taper;
 }
private:
 int lastIndex=-1;
 float lastDecay=-1.0f,cachedGain=1.0f;
};
}
