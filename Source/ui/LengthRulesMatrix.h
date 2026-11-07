#pragma once
#include "Theme.h"
#include "../PluginProcessor.h"
#include <memory>
#include <array>
namespace skell::ui {
class ClassThresholdPopup final : public juce::Component {
public:
 explicit ClassThresholdPopup(SkellSilenceAudioProcessor& p) {
   const char* ids[]={"classShortMax","classMediumMax","classLongMax"};
   const char* captions[]={"SHORT MAX / BEATS","MEDIUM MAX / BEATS","LONG MAX / BEATS"};
   for(int i=0;i<3;++i){
     labels[size_t(i)].setText(captions[i],juce::dontSendNotification);
     labels[size_t(i)].setColour(juce::Label::textColourId,Theme::text);addAndMakeVisible(labels[size_t(i)]);
     sliders[size_t(i)].setSliderStyle(juce::Slider::LinearHorizontal);
     sliders[size_t(i)].setTextBoxStyle(juce::Slider::TextBoxRight,false,65,24);
     attachments[size_t(i)]=std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters,ids[i],sliders[size_t(i)]);
     addAndMakeVisible(sliders[size_t(i)]);
   }
   setSize(340,180);
 }
 void paint(juce::Graphics& g) override {g.fillAll(Theme::panel);}
 void resized() override {
   for(int i=0;i<3;++i){labels[size_t(i)].setBounds(12,12+i*53,155,22);sliders[size_t(i)].setBounds(163,10+i*53,167,28);}
 }
private:
 std::array<juce::Label,3> labels;
 std::array<juce::Slider,3> sliders;
 std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>,3> attachments;
};
class LengthRulesMatrix final : public juce::Component {
public:
 explicit LengthRulesMatrix(SkellSilenceAudioProcessor& p) {
   rangeButton.setButtonText("EDIT RANGES");
   rangeButton.onClick=[this,&p]{juce::CallOutBox::launchAsynchronously(std::make_unique<ClassThresholdPopup>(p),rangeButton.getScreenBounds(),nullptr);};
   addAndMakeVisible(rangeButton);
   for(int i=0;i<7;++i)for(int c=0;c<4;++c){
     const int k=i*4+c;
     auto& toggle=buttons[size_t(k)];
     toggle.setButtonText({});toggle.setClickingTogglesState(true);
     toggle.setTooltip(juce::String(dsp::instrumentNames[size_t(i)])+" / "+dsp::classNames[size_t(c)]);
     addAndMakeVisible(toggle);
     const auto id="rule_"+juce::String(dsp::instrumentIds[size_t(i)])+"_"+juce::String(c);
     attachments[size_t(k)]=std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(p.parameters,id,toggle);
   }
 }
 void paint(juce::Graphics& g) override {
   Theme::panelBackground(g,getLocalBounds().toFloat());
   Theme::title(g,"LENGTH RULES  /  BEAT-SYNCED",{14,6,getWidth()-190,22});
   const int x=180,top=38,cw=std::max(1,(getWidth()-x-14)/4),rh=std::max(1,(getHeight()-top-7)/8);
   g.setFont(Theme::font(10.0f,true));
   for(int c=0;c<4;++c){g.setColour(Theme::violet.withAlpha(0.75f));g.drawFittedText(dsp::classNames[size_t(c)],x+c*cw,top,cw,rh,juce::Justification::centred,1);}
   for(int i=0;i<7;++i){
     g.setColour(Theme::text);g.drawFittedText(dsp::instrumentNames[size_t(i)],14,top+(i+1)*rh,160,rh,juce::Justification::centredLeft,1);
     g.setColour(Theme::border);g.drawHorizontalLine(top+(i+2)*rh,14.0f,float(getWidth()-14));
   }
 }
 void resized() override {
   rangeButton.setBounds(getWidth()-138,5,126,27);
   const int x=180,top=38,cw=std::max(1,(getWidth()-x-14)/4),rh=std::max(1,(getHeight()-top-7)/8);
   for(int i=0;i<7;++i)for(int c=0;c<4;++c) {
     buttons[size_t(i*4+c)].setBounds(x+c*cw+cw/2-12,top+(i+1)*rh+rh/2-12,24,24);
   }
 }
private:
 juce::TextButton rangeButton;
 std::array<juce::ToggleButton,28> buttons;
 std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>,28> attachments;
};
}
