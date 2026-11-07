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
};
inline float envelope(float x) noexcept {
  return std::sin(3.14159265358979323846f*std::clamp(x,0.0f,1.0f));
}
inline uint32_t nextRandom(uint32_t& s) noexcept {s^=s<<13;s^=s>>17;s^=s<<5;return s;}
inline float noise(uint32_t& s) noexcept {return float(nextRandom(s)&0xffff)/32768.0f-1.0f;}
}
