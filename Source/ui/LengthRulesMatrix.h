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
class LengthRulesMatrix final : public juce::Component,private juce::Timer {
public:
 explicit LengthRulesMatrix(SkellSilenceAudioProcessor& p):processor(p) {
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
   startTimerHz(12);
 }
 void paint(juce::Graphics& g) override {
   Theme::panelBackground(g,getLocalBounds().toFloat());
   Theme::title(g,"04  /  LENGTH RULES  -  BEAT SYNCED",{15,8,getWidth()-189,22});
   const int x=193,top=42,cw=(getWidth()-x-17)/4,rh=17;
   g.setColour(Theme::inset);g.fillRoundedRectangle(juce::Rectangle<float>(float(x-6),float(top),float(getWidth()-x-7),float(rh*8)),5.0f);
   const int active=processor.activeLengthClass.load(std::memory_order_relaxed);
   if(active>=0&&active<4) {
     g.setColour(Theme::green.withAlpha(0.10f));
     g.fillRoundedRectangle(juce::Rectangle<float>(float(x+active*cw+3),float(top+3),float(cw-6),float(rh*8-6)),4.0f);
     g.setColour(Theme::green);g.fillRoundedRectangle(float(x+active*cw+cw/2-17),float(top+1),34.0f,2.0f,1.0f);
   }
   g.setFont(Theme::font(10.5f,true));
   for(int c=0;c<4;++c){
     g.setColour(active==c?Theme::text:(c==0?Theme::cyan:c==1?Theme::green:c==2?Theme::violet:Theme::amber));
     g.drawFittedText(dsp::classNames[size_t(c)],x+c*cw,top,cw,rh,juce::Justification::centred,1);
   }
   for(int i=0;i<7;++i){
     const int cy=top+(i+1)*rh;
     if(i%2==0){g.setColour(Theme::raised.withAlpha(0.32f));g.fillRect(x-5,cy,getWidth()-x-8,rh);}
     g.setColour(Theme::text);g.setFont(Theme::font(11.0f));
     g.drawFittedText(dsp::instrumentNames[size_t(i)],17,cy,167,rh,juce::Justification::centredLeft,1);
     g.setColour(Theme::border.withAlpha(0.68f));g.drawHorizontalLine(cy+rh,15.0f,float(getWidth()-16));
   }
 }
 void resized() override {
   rangeButton.setBounds(getWidth()-144,8,127,26);
   const int x=193,top=42,cw=(getWidth()-x-17)/4,rh=17;
   for(int i=0;i<7;++i)for(int c=0;c<4;++c)
     buttons[size_t(i*4+c)].setBounds(x+c*cw+cw/2-11,top+(i+1)*rh,22,rh);
 }

private:
 void timerCallback() override {
   const int next=processor.activeLengthClass.load(std::memory_order_relaxed);
   if(next!=lastActive){lastActive=next;repaint();}
 }
 SkellSilenceAudioProcessor& processor;
 int lastActive=-2;
 juce::TextButton rangeButton;
 std::array<juce::ToggleButton,28> buttons;
 std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>,28> attachments;
};
}
