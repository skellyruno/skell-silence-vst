#include "../Source/dsp/InstrumentMixer.h"
#include "../Source/dsp/GapDetector.h"
#include <chrono>
#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>

int main(){
  using namespace skell::dsp;
  volatile float sink=0.0f;
  constexpr double pi=3.14159265358979323846;
  std::cout<<"PERF v2.8 C++ -O2 synthetic, whole DSP mixer, NOT FL Studio CPU\n";
  for(const double sr : {44100.0,48000.0,96000.0,192000.0}) {
    HistoryBuffer h;h.prepare(sr);
    for(int i=0;i<int(sr*1.0);++i)
      h.push(0.28f*std::sin(float(2*pi*180*i/sr)));
    const int frames=int(sr*0.35);
    for(int mode=0;mode<3;++mode){
      InstrumentSettings cfg{};
      if(mode!=0) {
        for(auto& rules:cfg.rules)rules.fill(true);
        cfg.enabled.fill(true);cfg.levels.fill(mode==1?0.0f:0.45f);
      }
      InstrumentMixer mix;mix.prepare(sr);
      double energy=0;float peak=0;
      const auto begin=std::chrono::steady_clock::now();
      for(int i=0;i<frames;++i){
        GapContext ctx{h,sr,120.0,sr*0.9,double(frames),double(i),
                       float(i)/frames,0.6f,0.7f,true};
        const float x=mix.process(ctx,cfg,2);
        peak=std::max(peak,std::abs(x));energy+=double(x)*x;sink=x;
      }
      const auto elapsed=std::chrono::duration<double>(
        std::chrono::steady_clock::now()-begin).count();
      std::cout<<"PERF sampleRate="<<sr<<" mode="<<(mode==0?"OFF":mode==1?"MUTED":"ALL7")
               <<" audioMs="<<(1000.0*frames/sr)
               <<" renderMs="<<(1000.0*elapsed)
               <<" cpuRatio="<<(elapsed*sr/frames)
               <<" peak="<<peak<<" energy="<<energy<<"\n";
    }
  }
  (void)sink;
}
