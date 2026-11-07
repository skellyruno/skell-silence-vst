#pragma once
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cmath>
namespace skell::dsp {
class LookaheadBuffer {
public:
  void prepare(double sr) {
    const auto length=std::max<size_t>(8192,size_t(sr*17.0));
    for(auto& v : channels) v.assign(length,0.0f);
    length_=length; reset();
  }
  void reset() noexcept { for(auto& v:channels) std::fill(v.begin(),v.end(),0.0f); writePos=0; }
  void push(int channel,float sample) noexcept { channels[size_t(channel)][writePos]=sample; }
  float delayed(int channel,int latency) const noexcept {
    if(latency<=0) return channels[size_t(channel)][writePos];
    auto delay=std::min<size_t>(size_t(latency),length_-1);
    auto index=(writePos+length_-delay)%length_;
    return channels[size_t(channel)][index];
  }
  void next() noexcept { if(++writePos==length_) writePos=0; }
private:
  std::vector<float> channels[2];
  size_t length_=1,writePos=0;
};
class HistoryBuffer {
public:
  void prepare(double sr){ samples.assign(std::max<size_t>(4096,size_t(sr*17.0)),0.0f); position=0; }
  void reset(int64_t absolutePosition=0){ std::fill(samples.begin(),samples.end(),0.0f); position=absolutePosition; }
  void push(float sample) noexcept {samples[size_t(position%samples.size())]=sample; ++position;}
  float read(double sampleTime) const noexcept {
    if(sampleTime<0 || sampleTime>=double(position) || position-double(sampleTime)>=double(samples.size()-2)) return 0;
    const auto p=int64_t(std::floor(sampleTime));
    const auto frac=float(sampleTime-double(p));
    const auto a=samples[size_t(p%int64_t(samples.size()))],b=samples[size_t((p+1)%int64_t(samples.size()))];
    return a+(b-a)*frac;
  }
private:
  std::vector<float> samples;
  int64_t position=0;
};
}
