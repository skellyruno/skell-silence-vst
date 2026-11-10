#pragma once
#include "InstrumentContext.h"
namespace skell::dsp {
class TapeStop {
public:
  void reset() noexcept {filter=0;}
  float process(const GapContext& c,float speedCurve,float stopTime,float lp) noexcept {
    const double duration=std::max(0.01,double(stopTime))*c.sampleRate;
    const double progress=std::clamp(c.time/duration,0.0,1.0);
    // Closed-form integrals of linear, quadratic and cubic deceleration.
    // Unlike a per-sample pow(), this costs only multiplies and has a smooth
    // zero-velocity endpoint for all curves.
    const double remain=1.0-progress;
    const double square=remain*remain,cube=square*remain,quartic=cube*remain;
    const double linear=(1.0-square)*0.5,quadratic=(1.0-cube)/3.0,cubic=(1.0-quartic)*0.25;
    const double amount=std::clamp(double(speedCurve),0.0,1.0)*2.0;
    const double integrated=duration*(amount<1.0?linear+(quadratic-linear)*amount:
                                                        quadratic+(cubic-quadratic)*(amount-1.0));
    const double playback=c.start-std::min(c.sampleRate*0.25,c.length*0.5)+integrated;
    const float x=c.history.readCubic(playback);
    const float cutoff=40.0f+(17000.0f*lp)*(1.0-progress)*(1.0-progress);
    const float a=std::clamp(float(6.2831853*cutoff/c.sampleRate),0.0002f,1.0f);
    filter+=a*(x-filter);
    return filter*float(1.0-0.8*progress)*envelope(std::min(1.0f, c.progress*3.0f));
  }
private: float filter=0;
};
}
