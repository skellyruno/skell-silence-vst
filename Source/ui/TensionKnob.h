#pragma once
#include "Theme.h"
#include "../PluginProcessor.h"
#include <memory>
#include <array>
namespace skell::ui {
class TensionKnob final : public juce::Component,private juce::Timer {
public:
 explicit TensionKnob(SkellSilenceAudioProcessor& p):processor(p){
    const char* names[]{"tension","space","duckAfter"};
    const char* labels[]{"TENSION","SPACE","DUCK AFTER"};
    for(int i=0;i<3;++i){
      auto& s=sliders[size_t(i)];s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
      s.setTextBoxStyle(juce::Slider::TextBoxBelow,false,67,19);
      if(i==0)s.setComponentID("tension");
      const auto* param=p.parameters.getParameter(names[i]);
      if(param!=nullptr)s.setDoubleClickReturnValue(true,param->convertFrom0to1(param->getDefaultValue()));
      s.setTooltip(i==0?"Riser and swell intensity":i==1?"Reverb bloom on gap material":"Short lift after a gap");
      attachments[size_t(i)]=std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters,names[i],s);
      addAndMakeVisible(s);
      label[size_t(i)].setText(labels[i],juce::dontSendNotification);
      label[size_t(i)].setJustificationType(juce::Justification::centred);
      label[size_t(i)].setColour(juce::Label::textColourId,Theme::muted);addAndMakeVisible(label[size_t(i)]);
    }
    startTimerHz(8);
 }
 void paint(juce::Graphics& g) override {
    Theme::panelBackground(g,getLocalBounds().toFloat());
    Theme::title(g,"05  /  DYNAMICS",{15,8,160,20});
    g.setColour(Theme::border);g.drawHorizontalLine(145,14.0f,float(getWidth()-14));
    g.setColour(Theme::violet);g.setFont(Theme::font(10,true));
    g.drawText("GAPS / MIN",15,149,88,18,juce::Justification::centredLeft);
    g.setColour(Theme::text);g.setFont(Theme::font(12,true));
    g.drawText(juce::String(processor.gapsLastMinute.load()),108,149,40,18,juce::Justification::centredLeft);
    const int mask=processor.activeMask.load();
    g.setColour(mask?Theme::green:Theme::muted);g.fillEllipse(245.0f,155.0f,6,6);
    g.setColour(Theme::muted);g.setFont(Theme::font(10));
    g.drawText(mask?"FX ACTIVE":"NO GAP",258,148,70,19,juce::Justification::centredLeft);
 }
 void resized() override {
    constexpr int w=104;
    for(int i=0;i<3;++i){
       sliders[size_t(i)].setBounds(8+i*107,29,99,94);
       label[size_t(i)].setBounds(8+i*107,123,99,19);
    }
 }
private:
 void timerCallback() override {repaint(12,145,getWidth()-20,25);}
 SkellSilenceAudioProcessor& processor;
 std::array<juce::Slider,3> sliders;
 std::array<juce::Label,3> label;
 std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>,3> attachments;
};
}
