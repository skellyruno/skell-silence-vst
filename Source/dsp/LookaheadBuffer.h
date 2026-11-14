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
    // No modulo on every delayed stereo sample.
    const auto index=writePos>=delay?writePos-delay:length_-(delay-writePos);
    return channels[size_t(channel)][index];
  }
  void next() noexcept { if(++writePos==length_) writePos=0; }
private:
  std::vector<float> channels[2];
  size_t length_=1,writePos=0;
};
class HistoryBuffer {
public:
  void prepare(double sr){
    samples.assign(std::max<size_t>(4096,size_t(sr*17.0)),0.0f);
    position=0;writeIndex=0;
  }
  void reset(int64_t absolutePosition=0){
    std::fill(samples.begin(),samples.end(),0.0f);
    position=std::max<int64_t>(0,absolutePosition);
    // reset() may also be called before prepare() by a host wrapper.
    writeIndex=samples.empty()?0:size_t(position)%samples.size();
  }
  void push(float sample) noexcept {
    samples[writeIndex]=sample;
    ++position;
    if(++writeIndex==samples.size())writeIndex=0;
  }
  float read(double sampleTime) const noexcept {
    if(sampleTime<0 || sampleTime>=double(position) || position-double(sampleTime)>=double(samples.size()-2)) return 0;
    const auto p=int64_t(std::floor(sampleTime));
    const auto frac=float(sampleTime-double(p));
    const auto index=size_t(p)%samples.size();
    const auto next=index+1==samples.size()?0:index+1;
    const float a=samples[index],b=samples[next];
    return a+(b-a)*frac;
  }
  // Four-point Hermite interpolation for variable-rate tape and granular playback.
  // Preserve the existing linear read() for detector/preview compatibility and
  // avoid reading outside the retained history near its oldest/newest edges.
  float readCubic(double sampleTime) const noexcept {
    if(sampleTime<1.0 || sampleTime+2.0>=double(position) ||
       double(position)-sampleTime>=double(samples.size()-3)) return read(sampleTime);
    const int64_t p=int64_t(std::floor(sampleTime));
    const float t=float(sampleTime-double(p));
    // The normal case is four contiguous samples. One modulo and one branch
    // avoid three more divides and all per-tap wrap checks on the hot path.
    const auto length=samples.size();
    const auto base=size_t(p-1)%length;
    const float a=samples[base];
    float b,c,d;
    if(base+3<length){
      b=samples[base+1];c=samples[base+2];d=samples[base+3];
    }else{
      // Slow path only for the three positions crossing the ring boundary.
      auto index=base;
      if(++index==length)index=0;
      b=samples[index];
      if(++index==length)index=0;
      c=samples[index];
      if(++index==length)index=0;
      d=samples[index];
    }
    const float slope=0.5f*(c-a);
    const float t2=t*t,t3=t2*t;
    return (2*t3-3*t2+1)*b+(t3-2*t2+t)*slope+
           (-2*t3+3*t2)*c+(t3-t2)*0.5f*(d-b);
  }
private:
  std::vector<float> samples;
  int64_t position=0;
  size_t writeIndex=0;
};
}
