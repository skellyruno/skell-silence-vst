#pragma once
#include "LookaheadBuffer.h"
#include <cmath>
#include <algorithm>
#include <cstdint>
namespace skell::dsp {
struct GapContext {
  const HistoryBuffer& history;
  double sampleRate=44100, bpm=120, start=0, length=0, time=0;
  float progress=0, tension=0.5f, space=0.25f;
  bool durationKnown=true; // false until real-time gap end is observed
};
inline float envelope(float x) noexcept {
  // Bhaskara's symmetric sine approximation on [0, pi]: exact at both
  // endpoints and midpoint; <0.002 absolute error. No per-sample sin().
  const float phase=std::clamp(x,0.0f,1.0f);
  const float parabola=phase*(1.0f-phase);
  return 16.0f*parabola/(5.0f-4.0f*parabola);
}
inline uint32_t nextRandom(uint32_t& s) noexcept {s^=s<<13;s^=s>>17;s^=s<<5;return s;}
inline float noise(uint32_t& s) noexcept {return float(nextRandom(s)&0xffff)/32768.0f-1.0f;}
}
