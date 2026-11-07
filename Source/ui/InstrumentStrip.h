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
    enabled.setColour(juce::ToggleButton::tickColourId,Theme::violet);
    level.setSliderStyle(juce::Slider::LinearHorizontal);level.setTextBoxStyle(juce::Slider::NoTextBox,false,0,0);
    settings.setButtonText(juce::String::fromUTF8("\xE2\x9A\x99"));
    settings.onClick=[this]{juce::CallOutBox::launchAsynchronously(std::make_unique<InstrumentPopup>(processor,index),settings.getScreenBounds(),nullptr);};
    addAndMakeVisible(enabled);addAndMakeVisible(level);addAndMakeVisible(settings);
  }
  void paint(juce::Graphics& g) override {
    const auto c=juce::Colour::fromHSV(float(index)/7.0f,0.45f,0.95f,1.0f);
    g.setColour(Theme::border);g.drawHorizontalLine(getHeight()-1,8.0f,float(getWidth()-8));
    g.setColour(c);g.fillRoundedRectangle(10.0f,float(getHeight()/2-6),3.0f,12.0f,1.5f);
    juce::Path shape;const float x=float(getWidth()-72),y=float(getHeight()/2);
    shape.startNewSubPath(x,y);
    for(int j=1;j<=35;++j){float t=float(j)/35.0f;shape.lineTo(x+45*t,y-8*std::sin(3.14159f*t)*std::sin(7*t+index));}
    g.setColour(c.withAlpha(0.65f));g.strokePath(shape,juce::PathStrokeType(1.3f));
  }
  void resized() override {
    const int h=getHeight();
    enabled.setBounds(19,2,145,h-4);
    level.setBounds(160,h/2-12,std::max(35,getWidth()-270),24);
    settings.setBounds(getWidth()-28,h/2-13,26,26);
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
