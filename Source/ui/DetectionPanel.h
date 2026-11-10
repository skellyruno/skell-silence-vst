#pragma once
#include "Theme.h"
#include "../PluginProcessor.h"
#include <array>
#include <memory>
namespace skell::ui {
class DetectionPanel final : public juce::Component,private juce::Timer {
public:
 explicit DetectionPanel(SkellSilenceAudioProcessor& p)
  :processor(p) {
   constexpr std::array<const char*,6> ids{"threshold","minGap","maxGap","hold","tailSensitivity","armTime"};
   constexpr std::array<const char*,6> names{"THRESHOLD","MIN GAP","MAX GAP","HOLD","TAIL SENSE","ARM TIME"};
   for(int i=0;i<6;++i){
      auto& s=knobs[size_t(i)];s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
      s.setTextBoxStyle(juce::Slider::TextBoxBelow,false,74,19);
      const auto* pval=p.parameters.getParameter(ids[size_t(i)]);
      if(pval!=nullptr)s.setDoubleClickReturnValue(true,pval->convertFrom0to1(pval->getDefaultValue()));
      s.setTooltip(juce::String(names[size_t(i)])+". Drag to adjust; Shift-drag for precision.");
      attachments[size_t(i)]=std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters,ids[size_t(i)],s);
      auto& l=knobLabels[size_t(i)];l.setText(names[size_t(i)],juce::dontSendNotification);
      l.setJustificationType(juce::Justification::centred);
      l.setColour(juce::Label::textColourId,Theme::muted);
      addAndMakeVisible(s);addAndMakeVisible(l);
   }
   source.setComponentID("trigger-source");
   lookahead.setComponentID("lookahead");
   source.addItemList({"AUTO","SIDECHAIN","GRID","MIDI"},1);
   source.setTooltip("Choose the detector input: source audio, sidechain, tempo grid, or MIDI.");
   lookahead.addItemList({"OFF","250 ms","500 ms","1 BEAT","1 BAR"},1);
   lookahead.setTooltip("Delay the wet/dry signal for gap detection. Reported to the DAW as latency.");
   addAndMakeVisible(source);addAndMakeVisible(lookahead);
   // Construct the attachments only once their ComboBox item IDs exist.
   // In particular LOOKAHEAD defaults to choice 2 (250 ms); attaching it
   // to an empty ComboBox loses its initial selection in JUCE 8.
   sourceAttachment=std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
       p.parameters,"triggerSource",source);
   lookaheadAttachment=std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
       p.parameters,"lookahead",lookahead);
   latency.setColour(juce::Label::textColourId,Theme::muted);
   latency.setJustificationType(juce::Justification::centredLeft);addAndMakeVisible(latency);
   startTimerHz(12);
 }
 void paint(juce::Graphics& g) override {
   Theme::panelBackground(g,getLocalBounds().toFloat());
   Theme::title(g,"02  /  GAP DETECTOR",{15,10,235,20});
   // Three indicators in the compact detector strip: fast, slow and trigger threshold.
   const juce::Rectangle<float> strip(551.0f,13.0f,234.0f,18.0f);
   g.setColour(Theme::inset);g.fillRoundedRectangle(strip,4);
   const float fast=processor.fastMeter.load(),slow=processor.slowMeter.load(),limit=processor.thresholdMeter.load();
   const float mx=std::max(0.015f,std::max(fast,slow)*1.5f);
   const float w=strip.getWidth()-8;
   g.setColour(Theme::cyan);g.fillRoundedRectangle(555.0f,17.0f,w*std::clamp(fast/mx,0.0f,1.0f),2,1);
   g.setColour(Theme::amber);g.fillRoundedRectangle(555.0f,21.0f,w*std::clamp(slow/mx,0.0f,1.0f),2,1);
   g.setColour(Theme::violet);g.fillRoundedRectangle(555.0f,25.0f,w*std::clamp(limit/mx,0.0f,1.0f),2,1);
   const int state=processor.detectorState.load(std::memory_order_relaxed);
   const char* stateNames[]{"SOUND","PENDING","GAP","RECOVERING"};
   g.setColour(state==2?Theme::violet:state==1?Theme::amber:Theme::muted);
   g.fillEllipse(317.0f,16.5f,6.0f,6.0f);
   g.setFont(Theme::font(10,true));
   g.drawText(stateNames[std::clamp(state,0,3)],328,9,94,22,juce::Justification::centredLeft);
   g.setColour(Theme::border);g.drawVerticalLine(607,48,130);
   g.setFont(Theme::font(10,true));g.setColour(Theme::muted);
   g.drawText("TRIGGER",621,41,94,16,juce::Justification::centredLeft);
   g.drawText("LOOKAHEAD",621,84,125,16,juce::Justification::centredLeft);
 }
 void resized() override {
   for(int i=0;i<6;++i){const int x=13+i*98;
     knobLabels[size_t(i)].setBounds(x,36,94,18);
     knobs[size_t(i)].setBounds(x+4,53,86,78);
   }
   source.setBounds(620,57,165,26);
   lookahead.setBounds(620,100,165,26);
   latency.setBounds(623,127,164,15);
 }
private:
 void timerCallback() override {
   latency.setText("HOST DELAY  "+juce::String(1000.0*processor.latencyRequested.load()/std::max(1.0,processor.sampleRateAtomic.load()),0)+" ms",juce::dontSendNotification);
   repaint(310,9,480,27);
 }
 SkellSilenceAudioProcessor& processor;
 std::array<juce::Slider,6> knobs;
 std::array<juce::Label,6> knobLabels;
 std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>,6> attachments;
 juce::ComboBox source,lookahead;
 std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> sourceAttachment,lookaheadAttachment;
 juce::Label latency;
};
}
