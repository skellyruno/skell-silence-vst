#pragma once
#include "Theme.h"
#include "WholePercentSlider.h"
#include "../PluginProcessor.h"
#include <memory>
#include <array>
namespace skell::ui {
// Advanced performance section keeps all four macros in one logical location.
class TensionKnob final : public juce::Component,private juce::Timer {
public:
 explicit TensionKnob(SkellSilenceAudioProcessor& p):processor(p){
    constexpr std::array<const char*,4> names{{"mix","tension","space","duckAfter"}};
    constexpr std::array<const char*,4> labels{{"MIX","ENERGY","SPACE","AFTER"}};
    constexpr std::array<const char*,4> tooltips{{
      "How much gap effect to blend into your song.",
      "Strength of risers and swells.",
      "Reverb on gap effects.",
      "A short level boost after a gap ends."
    }};
    for(size_t i=0;i<sliders.size();++i){
      auto& s=sliders[i];s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
      s.setTextBoxStyle(juce::Slider::TextBoxBelow,false,70,19);
      s.setComponentID(i==0?"mix":i==1?"tension":i==2?"space":"duck-after");
      if(auto* parameter=p.parameters.getParameter(names[i]))
        s.setDoubleClickReturnValue(true,parameter->convertFrom0to1(parameter->getDefaultValue()));
      s.setTooltip(tooltips[i]);
      attachments[i]=std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters,names[i],s);
      addAndMakeVisible(s);
      label[i].setText(labels[i],juce::dontSendNotification);
      label[i].setJustificationType(juce::Justification::centred);
      label[i].setColour(juce::Label::textColourId,Theme::muted);
      addAndMakeVisible(label[i]);
    }
    startTimerHz(8);
 }
 void paint(juce::Graphics& g) override {
    Theme::panelBackground(g,getLocalBounds().toFloat());
    Theme::title(g,"05  /  YOUR SOUND",{15,8,222,23});
    Theme::sectionRule(g,14.0f,145.0f,float(getWidth()-28),Theme::violet);
    for(int i=0;i<4;++i){
      const auto c=i==0?Theme::green:i==1?Theme::amber:i==2?Theme::violet:Theme::cyan;
      const float x=7.0f+80.0f*i;
      g.setColour(c.withAlpha(0.08f));g.fillRoundedRectangle(x,36.0f,76.0f,108.0f,7.0f);
      g.setColour(c.withAlpha(0.48f));g.fillRoundedRectangle(x+22.0f,34.0f,31.0f,2.0f,1.0f);
    }
    g.setColour(Theme::violet);g.setFont(Theme::font(11,true));
    g.drawText("GAPS / MIN",15,149,88,18,juce::Justification::centredLeft);
    g.setColour(Theme::text);g.setFont(Theme::font(13,true));
    g.drawText(juce::String(processor.gapsLastMinute.load()),108,149,40,18,juce::Justification::centredLeft);
    const int mask=processor.activeMask.load();
    g.setColour(mask?Theme::green:Theme::muted);g.fillEllipse(245.0f,155.0f,6,6);
    g.setColour(Theme::muted);g.setFont(Theme::font(11));
    g.drawText(mask?"FX ACTIVE":"NO GAP",258,148,70,19,juce::Justification::centredLeft);
 }
 void resized() override {
    for(int i=0;i<4;++i){
       sliders[size_t(i)].setBounds(7+i*80,48,76,81);
       label[size_t(i)].setBounds(7+i*80,123,76,19);
    }
 }
private:
 void timerCallback() override {repaint(12,145,getWidth()-20,25);}
 SkellSilenceAudioProcessor& processor;
 std::array<WholePercentSlider,4> sliders;
 std::array<juce::Label,4> label;
 std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>,4> attachments;
};
}
