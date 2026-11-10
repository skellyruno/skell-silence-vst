#pragma once
#include "InstrumentContext.h"
namespace skell::dsp {
class NoiseFade {
public:
  void setChannel(int channel) noexcept {initialSeed=channel==0?0xc0ffee21u:0x5bd1e995u;seed=initialSeed;}
  void reset() noexcept { pink=0; seed=initialSeed; }
  float process(const GapContext& c,int type,float fadeIn,float fadeOut) noexcept {
    auto n=noise(seed);pink=0.92f*pink+0.08f*n;
    if(type==1) n=pink*2.5f;
    if(type==2) n=0.75f*pink+0.15f*n;
    if(type==3) n=pink*0.7f;
    const float enter=std::min(1.0f,c.progress/std::max(0.02f,fadeIn));
    const float exit=std::min(1.0f,(1.0f-c.progress)/std::max(0.02f,fadeOut));
    return n*std::min(enter,exit)*0.18f;
  }
private: float pink=0;uint32_t seed=0xc0ffee21u,initialSeed=0xc0ffee21u;
};
}
