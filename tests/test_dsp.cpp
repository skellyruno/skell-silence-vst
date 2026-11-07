#include "../Source/dsp/GapDetector.h"
#include "../Source/dsp/GapMap.h"
#include "../Source/dsp/LookaheadBuffer.h"
#include "../Source/dsp/InstrumentMixer.h"
#include <cassert>
#include <cmath>
#include <iostream>
int main(){
  using namespace skell::dsp;
  constexpr double sampleRate=48000;
  GapDetector detector;detector.prepare(sampleRate);
  DetectorSettings p;p.thresholdDb=14;p.minGapMs=50;p.holdMs=25;p.maxGapMs=1500;p.armTimeSeconds=0.2f;
  int starts=0,ends=0;int64_t open=0,close=0;
  for(int64_t i=0;i<48000*3;i++){
    float s=i<48000?0.25f*std::sin(2*3.1415926*440*i/sampleRate):
            (i<48000*2?0.0f:0.25f*std::sin(2*3.1415926*440*i/sampleRate));
    auto d=detector.process(s,i,p);
    if(d.began){++starts;open=d.start;}
    if(d.ended){++ends;close=d.end;}
  }
  assert(starts>=1 && ends>=1);
  assert(open>=48000 && close>open);
  GapMap map;
  assert(map.append(1.0,1.7));assert(map.size()==1);assert(map.get(0).to==1.7);
  map.replace(0,{2.0,3.0});assert(map.get(0).from==2.0);
  map.erase(0);assert(map.size()==0);
  LookaheadBuffer delay;delay.prepare(sampleRate);
  for(int n=0;n<64;++n){delay.push(0,n==0?1.0f:0.0f);delay.push(1,0.0f);
    assert(std::abs(delay.delayed(0,7)-(n==7?1.0f:0.0f))<1e-5f);delay.next();}
  HistoryBuffer history;history.prepare(sampleRate);
  for(int64_t i=0;i<2000;++i)history.push(0.2f*std::sin(float(i)*0.02f));
  InstrumentMixer mx;mx.prepare(sampleRate);
  InstrumentSettings inst;for(auto& rules:inst.rules)rules={true,true,true,true};
  for(auto& enabled:inst.enabled)enabled=true;
  for(auto& level:inst.levels)level=0.2f;
  float maxPeak=0;
  for(int i=0;i<1000;++i){
    const float progress=i/1000.0f;
    GapContext c{history,sampleRate,120.0,1500.0,1000.0,double(i),progress,0.5f,0.3f};
    float v=mx.process(c,inst,2);assert(std::isfinite(v));maxPeak=std::max(maxPeak,std::abs(v));
  }
  std::cout<<"PASS gap begin="<<open<<" end="<<close<<" maxFx="<<maxPeak<<"\n";
}
