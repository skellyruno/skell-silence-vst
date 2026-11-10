#pragma once
#include <algorithm>
#include <cmath>

namespace skell::dsp {
// Length classes are selected once at the onset of a rendered gap. If the
// duration is only an estimate, growing the gap must not abruptly switch
// the rules matrix to another set of instruments mid-phrase.
inline int classifyGapBeats(double beats, float shortMax, float mediumMax,
                            float longMax) noexcept {
  const double safeBeats=std::isfinite(beats)?std::max(0.0,beats):0.0;
  const double medium=std::max(double(shortMax),double(mediumMax));
  const double longer=std::max(medium,double(longMax));
  return safeBeats<double(shortMax)?0:safeBeats<medium?1:safeBeats<longer?2:3;
}
class GapClassLatch {
public:
  void reset() noexcept { active=false; current=-1; }
  int advance(bool gapActive,double beats,float shortMax,float mediumMax,float longMax) noexcept {
    if(!gapActive) {reset();return -1;}
    if(!active) {
      current=classifyGapBeats(beats,shortMax,mediumMax,longMax);
      active=true;
    }
    return current;
  }
private:
  bool active=false;
  int current=-1;
};
}
