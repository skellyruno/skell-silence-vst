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
    constexpr std::array<const char*,4> labels{{"MIX","ENERGY","SPACE","EXIT LIFT"}};
    constexpr std::array<const char*,4> tooltips{{
      "How much gap effect to blend into your song.",
      "Strength of risers and swells.",
      "Reverb on gap effects.",
      "Optional brief volume lift after a gap. Set to 0% to preserve unity gain."
    }};
    for(size_t i=0;i<sliders.size();++i){
      auto& s=sliders[i];s.setSliderStyle(juce::Slider::LinearHorizontal);
      s.setTextBoxStyle(juce::Slider::TextBoxRight,false,49,24);
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
    // A two-by-two arrangement avoids knob-value/label collisions at compact sizes.
    for(int i=0;i<4;++i){
      const auto c=i==0?Theme::green:i==1?Theme::amber:i==2?Theme::violet:Theme::cyan;
      const float x=9.0f+158.0f*float(i%2), y=35.0f+54.0f*float(i/2);
      g.setColour(c.withAlpha(0.07f));g.fillRoundedRectangle(x,y,151.0f,50.0f,5.0f);
      g.setColour(c.withAlpha(0.54f));g.fillRoundedRectangle(x+9,y+1,29.0f,2.0f,1.0f);
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
      const int x=9+(i%2)*158, y=35+(i/2)*54;
      label[size_t(i)].setBounds(x+8,y+2,132,18);
      sliders[size_t(i)].setBounds(x+8,y+22,136,25);
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
