#pragma once
#include "Theme.h"
#include "../PluginProcessor.h"
#include <memory>
namespace skell::ui {
class InstrumentPopup final : public juce::Component {
public:
  InstrumentPopup(SkellSilenceAudioProcessor& p,int index)
    :instrumentTitle(skell::dsp::instrumentNames[size_t(index)]) {
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
      juce::String caption(id);
      // Human-readable parameter captions: "stopSpeedCurve" -> "STOP SPEED CURVE".
      for(int j=caption.length()-1;j>0;--j)
        if(caption[j]>='A' && caption[j]<='Z' &&
           caption[j-1]>='a' && caption[j-1]<='z')caption=caption.substring(0,j)+" "+caption.substring(j);
      label->setText(caption.replaceCharacter('_',' ').toUpperCase(),juce::dontSendNotification);
      const auto explanation=parameterHint(juce::String(id));
      label->setTooltip(explanation);
      hints.push_back(explanation);
      label->setColour(juce::Label::textColourId,Theme::text);addAndMakeVisible(*label);
      if(auto* choice=dynamic_cast<juce::AudioParameterChoice*>(p.parameters.getParameter(id))) {
        auto* combo=combos.emplace_back(std::make_unique<juce::ComboBox>()).get();
        combo->addItemList(choice->choices,1);
        combo->setTooltip(explanation);
        addAndMakeVisible(*combo);
        comboAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(p.parameters,id,*combo));
      } else {
        auto* slider=sliders.emplace_back(std::make_unique<juce::Slider>()).get();
        slider->setSliderStyle(juce::Slider::LinearHorizontal);
        slider->setTextBoxStyle(juce::Slider::TextBoxRight,false,60,24);
        if(auto* parameter=p.parameters.getParameter(id))
          slider->setDoubleClickReturnValue(true,parameter->convertFrom0to1(parameter->getDefaultValue()));
        slider->setTooltip(explanation);
        addAndMakeVisible(*slider);
        sliderAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters,id,*slider));
      }
      types.push_back(dynamic_cast<juce::AudioParameterChoice*>(p.parameters.getParameter(id))!=nullptr);
    }
    setSize(360,int(72+types.size()*52));
  }
  void resized() override {
    int sliderIndex=0,comboIndex=0;
    for(size_t i=0;i<types.size();++i){
      const int y=58+int(i)*52;
      labels[i]->setBounds(17,y,151,27);
      if(types[i])combos[size_t(comboIndex++)]->setBounds(171,y,170,28);
      else sliders[size_t(sliderIndex++)]->setBounds(171,y,170,28);
    }
  }
  void paint(juce::Graphics& g) override {
    g.fillAll(Theme::panel);
    g.setColour(Theme::green);g.fillRoundedRectangle(15.0f,17.0f,3.0f,20.0f,1.0f);
    g.setFont(Theme::font(15,true));g.setColour(Theme::text);
    g.drawFittedText(instrumentTitle+"  /  SETTINGS",26,12,getWidth()-40,31,juce::Justification::centredLeft,1);
    g.setColour(Theme::border);g.drawHorizontalLine(46,15.0f,float(getWidth()-15));
    for(size_t i=0;i<types.size();++i) {
      g.setColour(Theme::muted);g.setFont(Theme::font(10.0f));
      g.drawFittedText(hints[i],17,85+int(i)*52,325,17,juce::Justification::centredLeft,1);
      if(i+1<types.size()){
        g.setColour(Theme::border);
        g.drawHorizontalLine(104+int(i)*52,15.0f,float(getWidth()-15));
      }
    }
  }
private:
  static juce::String parameterHint(const juce::String& id) {
    if(id=="stopSpeedCurve")return "Brake shape from smooth to aggressive";
    if(id=="stopTime")return "Time until the tape reaches zero speed";
    if(id=="stopLowpass")return "Tone rolloff as playback decelerates";
    if(id=="airColor")return "Match preceding sound or use pink / white";
    if(id=="airShape")return "Tilt the air spectrum darker or brighter";
    if(id=="swellLength")return "Reverse pre-gap audio into the next hit";
    if(id=="swellReverb")return "Reverb bloom on reverse material";
    if(id=="noiseType")return "Choose the texture filling quiet passages";
    if(id=="noiseFadeIn")return "Fade-in proportion of the gap";
    if(id=="noiseFadeOut")return "Fade-out proportion before the next hit";
    if(id=="impactPitch")return "Sub impact pitch / tonal weight";
    if(id=="impactDecay")return "Tail length of the impact";
    if(id=="impactClick")return "Transient snap at impact onset";
    if(id=="riserStart")return "Initial filter brightness";
    if(id=="riserCurve")return "Acceleration into the next hit";
    if(id=="riserNoiseMix")return "Blend filtered noise and pitched sweep";
    if(id=="stutterDiv")return "Slice duration synced to host tempo";
    if(id=="stutterDecay")return "Gain loss after every repeated slice";
    if(id=="stutterCount")return "Number of repeats in the gap";
    return "Drag to adjust; shift for fine control";
  }
  juce::String instrumentTitle;
  std::vector<juce::String> hints;
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
    enabled.setColour(juce::ToggleButton::tickColourId,Theme::instruments[size_t(index)]);
    level.setSliderStyle(juce::Slider::LinearHorizontal);
    level.setTextBoxStyle(juce::Slider::NoTextBox,false,0,0);
    level.setColour(juce::Slider::trackColourId,Theme::instruments[size_t(index)]);
    level.setTooltip("Instrument output level. Shift-drag for fine adjustment; double-click to reset.");
    level.setDoubleClickReturnValue(true,0.6);
    level.onValueChange=[this]{repaint(157,34,77,21);};
    settings.setButtonText("...");settings.setTooltip("Open detailed settings for "+juce::String(skell::dsp::instrumentNames[size_t(index)]));
    settings.setComponentID("instrument-settings-"+juce::String(index));
    settings.onClick=[this]{
      auto* editor=findParentComponentOfClass<juce::AudioProcessorEditor>();
      juce::CallOutBox::launchAsynchronously(
        std::make_unique<InstrumentPopup>(processor,index),settings.getScreenBounds(),editor);
    };
    addAndMakeVisible(enabled);addAndMakeVisible(level);addAndMakeVisible(settings);
  }
  void paint(juce::Graphics& g) override {
    const bool playing=(processor.activeMask.load(std::memory_order_relaxed)&(1<<index))!=0;
    const bool on=enabled.getToggleState();
    const auto c=Theme::instruments[size_t(index)];
    if(index%2==0 || playing){
      g.setColour(playing?c.withAlpha(0.12f):Theme::raised.withAlpha(0.25f));
      g.fillRoundedRectangle(getLocalBounds().toFloat().reduced(1,2),5.0f);
    }
    g.setColour(Theme::border.withAlpha(0.7f));g.drawHorizontalLine(getHeight()-1,8.0f,float(getWidth()-8));
    g.setColour(on?c:Theme::border);g.fillRoundedRectangle(5.0f,18.0f,3.0f,23.0f,1.5f);
    juce::Path env;
    const float x=float(getWidth()-87),y=float(getHeight()/2);
    env.startNewSubPath(x,y-12.0f*Theme::instrumentEnvelope(index,0.0f));
    for(int i=1;i<=32;++i){
       const float t=float(i)/32;
       const float yy=y-12.0f*Theme::instrumentEnvelope(index,t);
       env.lineTo(x+49.0f*t,yy);
    }
    g.setColour(on?c.withAlpha(playing?1.0f:0.55f):Theme::border);
    g.strokePath(env,juce::PathStrokeType(playing?2.0f:1.2f));
    if(playing){g.setColour(c);g.fillEllipse(float(getWidth()-99),float(getHeight()/2-3),6.0f,6.0f);}
    g.setColour(on?Theme::muted:Theme::border);
    g.setFont(Theme::font(9.0f,true));
    g.drawText(juce::String(juce::roundToInt(level.getValue()*100.0))+"%",173,37,52,13,juce::Justification::centred);
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
