#pragma once
#include "InstrumentContext.h"
namespace skell::dsp {
class TapeStop {
public:
  void reset() noexcept {filter=0;}
  float process(const GapContext& c,float speedCurve,float stopTime,float lp) noexcept {
    const double duration=std::max(0.01,double(stopTime))*c.sampleRate;
    const double progress=std::clamp(c.time/duration,0.0,1.0);
    const double exponent=0.5+3.5*speedCurve;
    // Integral of velocity (1-t/T)^exponent: read pointer never reverses.
    const double integrated=duration*(1.0-std::pow(1.0-progress,exponent+1.0))/(exponent+1.0);
    const double playback=c.start-std::min(c.sampleRate*0.25,c.length*0.5)+integrated;
    const float x=c.history.read(playback);
    const float cutoff=40.0f+(17000.0f*lp)*(1.0-progress)*(1.0-progress);
    const float a=std::clamp(float(6.2831853*cutoff/c.sampleRate),0.0002f,1.0f);
    filter+=a*(x-filter);
    return filter*float(1.0-0.8*progress)*envelope(std::min(1.0f, c.progress*3.0f));
  }
private: float filter=0;
};
}
