#pragma once
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>
namespace skell::dsp {
// Eight damped feedback delay lines; allocated only in prepare().
class Reverb {
public:
  void prepare(double sampleRate) {
    constexpr std::array<double,8> times{0.0311,0.0371,0.0411,0.0437,0.0531,0.0593,0.0617,0.0671};
    for(size_t i=0;i<lines.size();++i){ auto& l=lines[i];l.data.assign(size_t(sampleRate*times[i])+1,0.0f);l.pos=0;l.filter=0; }
  }
  void reset() {for(auto& l:lines){std::fill(l.data.begin(),l.data.end(),0);l.pos=0;l.filter=0;}}
  float process(float input,float space) noexcept {
    float accum=0;
    for(auto& l:lines) accum+=l.data[l.pos];
    const float shared=accum*0.125f;
    const float householder=accum*0.25f;
    const float feedback=std::clamp(0.25f+0.60f*space,0.0f,0.85f);
    for(size_t i=0;i<lines.size();++i){
      auto& l=lines[i];const float v=l.data[l.pos];l.filter=0.65f*l.filter+0.35f*v;
      l.data[l.pos]=input*0.20f+(householder-l.filter)*feedback*(i%2?1.0f:-1.0f);
      l.pos=(l.pos+1)%l.data.size();
    }
    return shared;
  }
private:
  struct Line {std::vector<float> data;size_t pos=0;float filter=0;};
  std::array<Line,8> lines;
};
}
