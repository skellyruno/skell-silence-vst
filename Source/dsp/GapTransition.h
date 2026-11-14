#pragma once
#include <array>
#include <algorithm>
#include <cmath>

namespace skell::dsp {
// Sample-accurate wet attack/release, independent of when the detector can
// confirm a gap. This avoids a sudden full-level wet onset with lookahead OFF.
// For release, crossfade the last wet sample into the moving reverb tail.
// Pure state: no locking, allocation, or transcendental functions on the RT path.
class GapTransition {
public:
  void prepare(double sampleRate) noexcept {
    fadeSamples=std::max(1,int(std::lround(std::max(8000.0,sampleRate)*0.005)));
    reset();
  }
  void reset() noexcept {previousActive=false;attackSamples=0;releaseRemaining=0;lastWet={0.0f,0.0f};}
  std::array<float,2> process(bool active,float left,float right) noexcept {
    if(active){
      if(!previousActive){attackSamples=0;releaseRemaining=0;}
      previousActive=true;
      attackSamples=std::min(attackSamples+1,fadeSamples);
      const float position=float(attackSamples)/float(fadeSamples);
      // C1-smooth cubic envelope: no abrupt gain derivative at either
      // boundary (a linear ramp leaves sharp corners in the wet signal).
      const float gain=position*position*(3.0f-2.0f*position);
      lastWet={left*gain,right*gain};
      return lastWet;
    }
    if(previousActive)releaseRemaining=fadeSamples;
    previousActive=false;
    // Keep the tail moving; adding a frozen wet sample to reverb caused
    // a short DC-like plateau and extra gain at the closing boundary.
    if(releaseRemaining<=0)return {left,right};
    const float position=float(releaseRemaining--)/float(fadeSamples);
    const float oldGain=position*position*(3.0f-2.0f*position);
    const float tailGain=1.0f-oldGain;
    return {lastWet[0]*oldGain+left*tailGain,
            lastWet[1]*oldGain+right*tailGain};
  }
private:
  std::array<float,2> lastWet{{0.0f,0.0f}};
  int fadeSamples=240,attackSamples=0,releaseRemaining=0;
  bool previousActive=false;
};
}
