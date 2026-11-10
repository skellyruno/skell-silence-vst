#pragma once
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>
namespace skell::dsp {
// Eight mutually prime-ish delay lengths, with a norm-preserving Householder
// feedback matrix. All memory is allocated in prepare(); no RT allocations.
class Reverb {
public:
  void prepare(double sampleRate) {
    // Damping time constants stay consistent when switching sample rate.
    const double rate=std::max(8000.0,sampleRate);
    dampingScale=float(48000.0/rate);
    constexpr std::array<double,8> times{0.0311,0.0371,0.0411,0.0437,0.0531,0.0593,0.0617,0.0671};
    for(size_t i=0;i<lines.size();++i){
      auto& l=lines[i];l.data.assign(size_t(sampleRate*times[i])+1,0.0f);
      l.position=0;l.damped=0.0f;
    }
  }
  void reset() noexcept {
    for(auto& l:lines){std::fill(l.data.begin(),l.data.end(),0.0f);l.position=0;l.damped=0.0f;}
  }
  float process(float input,float space) noexcept {
    std::array<float,8> filtered{};
    float sum=0.0f,output=0.0f;
    const float baseDamping=0.35f+0.28f*std::clamp(space,0.0f,1.0f);
    // First-order normalized pole conversion; avoids pow() in the sample loop.
    // Exact at 48 kHz and smoothly adapts at other host rates.
    const float damping=std::clamp(1.0f-(1.0f-baseDamping)*dampingScale,0.0f,0.999f);
    for(size_t i=0;i<lines.size();++i){
      auto& line=lines[i];const float sample=line.data[line.position];
      line.damped=damping*line.damped+(1.0f-damping)*sample;
      filtered[i]=line.damped;
      sum+=line.damped;
      output+=(i%2==0?1.0f:-1.0f)*sample;
    }
    // H = (2/N)11^T - I preserves energy. Feedback below unity guarantees decay.
    const float shared=0.25f*sum;
    const float feedback=0.45f+0.42f*std::clamp(space,0.0f,1.0f);
    for(size_t i=0;i<lines.size();++i){
      auto& line=lines[i];
      line.data[line.position]=0.14f*input + feedback*(shared-filtered[i]);
      if(++line.position>=line.data.size())line.position=0;
    }
    return 0.125f*output;
  }
private:
  struct Line {std::vector<float> data;size_t position=0;float damped=0;};
  std::array<Line,8> lines;
  float dampingScale=1.0f;
};
}
