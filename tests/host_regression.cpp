#include "../Source/PluginProcessor.h"
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

namespace {
void setNormalized(SkellSilenceAudioProcessor& p,const char* id,float value) {
  auto* param=p.parameters.getParameter(id);
  assert(param!=nullptr);
  param->setValueNotifyingHost(value);
}
}
int main(){
  juce::ScopedJuceInitialiser_GUI juceInit;
  auto first=std::make_unique<SkellSilenceAudioProcessor>();
  assert(first->getName()=="Skell Silence");
  assert(first->getNumPrograms()==1);
  for(const auto* id : {"lookahead","mix","threshold","tailSensitivity","stopTime",
                        "stutterDecay","rule_stutter_0","pluginEnabled"}) {
    assert(first->parameters.getParameter(id)!=nullptr);
  }

  setNormalized(*first,"lookahead",0.0f);
  setNormalized(*first,"mix",0.0f);
  setNormalized(*first,"threshold",0.65f);
  setNormalized(*first,"stopTime",0.45f);
  first->gapMap.append(4.0,4.75);
  first->windowW.store(912);first->windowH.store(578);
  juce::MemoryBlock state;
  first->getStateInformation(state);
  assert(state.getSize()>500);
  auto second=std::make_unique<SkellSilenceAudioProcessor>();
  second->setStateInformation(state.getData(),int(state.getSize()));
  assert(second->gapMap.size()==1);
  assert(std::abs(second->gapMap.get(0).from-4.0)<1.e-8);
  assert(std::abs(second->gapMap.get(0).to-4.75)<1.e-8);
  assert(second->windowW.load()==912);
  assert(std::abs(second->parameters.getParameter("threshold")->getValue()-
                  first->parameters.getParameter("threshold")->getValue())<1.e-6);
  assert(std::abs(second->parameters.getParameter("stopTime")->getValue()-
                  first->parameters.getParameter("stopTime")->getValue())<1.e-6);
  assert(second->parameters.getParameter("lookahead")->getValue()==0.0f);

  first->prepareToPlay(48000.0,256);
  second->prepareToPlay(48000.0,256);
  assert(first->getLatencySamples()==0 && second->getLatencySamples()==0);
  juce::AudioBuffer<float> a(2,256),b(2,256);
  juce::MidiBuffer midi;
  for(int block=0;block<100;++block){
    std::array<float,256> original{};
    for(int i=0;i<256;++i){
      const float x=0.25f*std::sin(float(block*256+i)*0.033f);
      original[size_t(i)]=x;
      a.setSample(0,i,x);a.setSample(1,i,-x);
      b.setSample(0,i,x);b.setSample(1,i,-x);
    }
    first->processBlock(a,midi);
    second->processBlock(b,midi);
    for(int i=0;i<256;++i){
      // MIX=0 and OFF lookahead must be bit-exact dry, for both channels.
      assert(a.getSample(0,i)==original[size_t(i)]);
      assert(a.getSample(1,i)==-original[size_t(i)]);
      assert(a.getSample(0,i)==b.getSample(0,i));
      assert(a.getSample(1,i)==b.getSample(1,i));
    }
  }
  first->releaseResources();second->releaseResources();

  // PDC and host bypass: the 250ms reported latency must agree with the
  // exact impulse position on both channels, including block boundaries.
  auto delayed=std::make_unique<SkellSilenceAudioProcessor>();
  assert(delayed->parameters.getParameter("lookahead")->getValue()==0.25f);
  delayed->prepareToPlay(48000.0,256);
  assert(delayed->getLatencySamples()==12000);
  for(int block=0;block<70;++block){
    a.clear();
    if(block==0){a.setSample(0,0,0.7f);a.setSample(1,0,-0.7f);}
    delayed->processBlockBypassed(a,midi);
    for(int i=0;i<256;++i){
      const int sample=block*256+i;
      const float expect=sample==12000?0.7f:0.0f;
      assert(std::abs(a.getSample(0,i)-expect)<1.e-7f);
      assert(std::abs(a.getSample(1,i)+expect)<1.e-7f);
    }
  }

  std::cout<<"PASS Windows JUCE host regression: legacy parameter IDs, "
           <<"preset/map/window state, concurrent instances, "
           <<"bit-exact MIX=0, bypass latency 12000 samples at 48k\n";
}
