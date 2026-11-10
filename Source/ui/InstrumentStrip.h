#pragma once
#include "Theme.h"
#include "../PluginProcessor.h"
#include <memory>
namespace skell::ui {
class InstrumentPopup final : public juce::Component {
public:
  InstrumentPopup(SkellSilenceAudioProcessor& p,int index) {
    const char* names[7][4] = {
      {"stopSpeedCurve","stopTime","stopLowpass",nullptr},
      {"airColor","airShape",nullptr,nullptr},
      {"swellLength","swellReverb",nullptr,nullptr},
      {"noiseType","noiseFadeIn","noiseFadeOut",nullptr},
      {"impactPitch","impactDecay","impactClick",nullptr},
      {"riserStart","riserCurve","riserNoiseMix",nullptr},
      {"stutterDiv","stutterDecay","stutterCount",nullptr}
    };
    for(const auto* id : names[index]) {
      if(id==nullptr) continue;
      auto* label=labels.emplace_back(std::make_unique<juce::Label>()).get();
      label->setText(juce::String(id).replaceCharacter('_',' ').toUpperCase(),juce::dontSendNotification);
      label->setColour(juce::Label::textColourId,Theme::text);addAndMakeVisible(*label);
      if(auto* choice=dynamic_cast<juce::AudioParameterChoice*>(p.parameters.getParameter(id))) {
        auto* combo=combos.emplace_back(std::make_unique<juce::ComboBox>()).get();
        combo->addItemList(choice->choices,1);addAndMakeVisible(*combo);
        comboAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(p.parameters,id,*combo));
      } else {
        auto* slider=sliders.emplace_back(std::make_unique<juce::Slider>()).get();
        slider->setSliderStyle(juce::Slider::LinearHorizontal);
        slider->setTextBoxStyle(juce::Slider::TextBoxRight,false,60,24);
        addAndMakeVisible(*slider);
        sliderAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters,id,*slider));
      }
      types.push_back(dynamic_cast<juce::AudioParameterChoice*>(p.parameters.getParameter(id))!=nullptr);
    }
    setSize(310,int(48+types.size()*46));
  }
  void resized() override {
    int sliderIndex=0,comboIndex=0;
    for(size_t i=0;i<types.size();++i){
      labels[i]->setBounds(14,int(15+i*46),110,26);
      if(types[i])combos[size_t(comboIndex++)]->setBounds(128,int(15+i*46),166,26);
      else sliders[size_t(sliderIndex++)]->setBounds(128,int(15+i*46),166,26);
    }
  }
  void paint(juce::Graphics& g) override {g.fillAll(Theme::panel);}
private:
  std::vector<std::unique_ptr<juce::Label>> labels;
  std::vector<std::unique_ptr<juce::Slider>> sliders;
  std::vector<std::unique_ptr<juce::ComboBox>> combos;
  std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;
  std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>> comboAttachments;
  std::vector<bool> types;
};
class InstrumentStrip final : public juce::Component {
public:
  InstrumentStrip(SkellSilenceAudioProcessor& p,int i):processor(p),index(i),
    enableAttachment(p.parameters,juce::String(skell::dsp::instrumentIds[size_t(i)])+"On",enabled),
    levelAttachment(p.parameters,juce::String(skell::dsp::instrumentIds[size_t(i)])+"Level",level) {
    enabled.setButtonText(juce::String(skell::dsp::instrumentNames[size_t(i)]));
    enabled.setColour(juce::ToggleButton::tickColourId,Theme::green);
    level.setSliderStyle(juce::Slider::LinearHorizontal);level.setTextBoxStyle(juce::Slider::NoTextBox,false,0,0);
    settings.setButtonText("...");settings.setTooltip("Open instrument settings");
    settings.onClick=[this]{juce::CallOutBox::launchAsynchronously(std::make_unique<InstrumentPopup>(processor,index),settings.getScreenBounds(),nullptr);};
    addAndMakeVisible(enabled);addAndMakeVisible(level);addAndMakeVisible(settings);
  }
  void paint(juce::Graphics& g) override {
    const auto c=Theme::instruments[size_t(index)];
    if(index%2==0){g.setColour(Theme::raised.withAlpha(0.25f));g.fillRoundedRectangle(getLocalBounds().toFloat().reduced(1,2),5.0f);}
    g.setColour(Theme::border.withAlpha(0.7f));g.drawHorizontalLine(getHeight()-1,8.0f,float(getWidth()-8));
    g.setColour(c);g.fillRoundedRectangle(5.0f,18.0f,3.0f,23.0f,1.5f);
    juce::Path env;
    const float x=float(getWidth()-87),y=float(getHeight()/2);
    env.startNewSubPath(x,y);
    for(int i=1;i<=32;++i){const float t=float(i)/32;
       const float yy=y-8.0f*std::sin(3.14159265f*t)*std::sin(t*7.5f+float(index));
       env.lineTo(x+54.0f*t,yy);
    }
    g.setColour(c.withAlpha(0.7f));g.strokePath(env,juce::PathStrokeType(1.5f));
  }
  void resized() override {
    enabled.setBounds(11,8,153,41);
    level.setBounds(158,14,71,30);
    settings.setBounds(getWidth()-30,16,25,26);
  }

private:
  SkellSilenceAudioProcessor& processor;int index;
  juce::ToggleButton enabled;
  juce::Slider level;
  juce::TextButton settings;
  juce::AudioProcessorValueTreeState::ButtonAttachment enableAttachment;
  juce::AudioProcessorValueTreeState::SliderAttachment levelAttachment;
};
}
