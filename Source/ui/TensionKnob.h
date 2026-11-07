#pragma once
#include "Theme.h"
#include "../PluginProcessor.h"
#include <memory>
#include <array>
namespace skell::ui {
class TensionKnob final : public juce::Component,private juce::Timer {
public:
 explicit TensionKnob(SkellSilenceAudioProcessor& p):processor(p) {
   const char* names[]={"tension","space","duckAfter"};
   const char* labels[]={"TENSION","SPACE","DUCK AFTER"};
   for(int i=0;i<3;++i){
     auto& s=sliders[size_t(i)];s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
     s.setTextBoxStyle(juce::Slider::TextBoxBelow,false,60,18);
     if(i==0)s.setComponentID("tension");
     attachments[size_t(i)]=std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters,names[i],s);
     addAndMakeVisible(s);
     label[size_t(i)].setText(labels[i],juce::dontSendNotification);
     label[size_t(i)].setJustificationType(juce::Justification::centred);
     label[size_t(i)].setColour(juce::Label::textColourId,Theme::muted);addAndMakeVisible(label[size_t(i)]);
   }
   gapStats.setColour(juce::Label::textColourId,Theme::violet);gapStats.setJustificationType(juce::Justification::centred);
   addAndMakeVisible(gapStats);startTimerHz(8);
 }
 void paint(juce::Graphics& g) override {Theme::panelBackground(g,getLocalBounds().toFloat());}
 void resized() override {
   const int w=getWidth()/3;
   for(int i=0;i<3;++i){sliders[size_t(i)].setBounds(i*w+6,4,w-12,getHeight()-42);label[size_t(i)].setBounds(i*w+3,getHeight()-38,w-6,19);}
   gapStats.setBounds(0,getHeight()-19,getWidth(),18);
 }
private:
 void timerCallback() override {gapStats.setText("GAPS / MIN  "+juce::String(processor.gapsLastMinute.load()),juce::dontSendNotification);}
 SkellSilenceAudioProcessor& processor;
 std::array<juce::Slider,3> sliders;
 std::array<juce::Label,3> label;
 std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>,3> attachments;
 juce::Label gapStats;
};
}
