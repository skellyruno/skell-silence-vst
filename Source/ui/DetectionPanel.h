#pragma once
#include "Theme.h"
#include "../PluginProcessor.h"
#include <array>
#include <memory>
namespace skell::ui {
class DetectionPanel final : public juce::Component,private juce::Timer {
public:
  explicit DetectionPanel(SkellSilenceAudioProcessor& p):processor(p),
  sourceAttachment(p.parameters,"triggerSource",source),lookaheadAttachment(p.parameters,"lookahead",lookahead) {
    constexpr std::array<const char*,6> ids {"threshold","minGap","maxGap","hold","tailSensitivity","armTime"};
    constexpr std::array<const char*,6> labels_ {"THRESHOLD","MIN GAP","MAX GAP","HOLD","TAIL SENSE","ARM TIME"};
    for(int i=0;i<6;++i) {
      auto& s=knobs[size_t(i)];s.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
      s.setTextBoxStyle(juce::Slider::TextBoxBelow,false,64,16);s.setDoubleClickReturnValue(true,p.parameters.getRawParameterValue(ids[size_t(i)])->load());
      attachments[size_t(i)]=std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters,ids[size_t(i)],s);
      s.setTooltip(juce::String(labels_[size_t(i)])+" - double-click to reset; Shift-drag for fine control");
      addAndMakeVisible(s);
      auto& lab=knobLabels[size_t(i)];lab.setText(labels_[size_t(i)],juce::dontSendNotification);
      lab.setJustificationType(juce::Justification::centred);lab.setColour(juce::Label::textColourId,Theme::muted);addAndMakeVisible(lab);
    }
    source.addItemList({"AUTO","SIDECHAIN","GRID","MIDI"},1);
    source.setTooltip("Choose audio, sidechain, tempo grid, or MIDI to detect gaps.");
    lookahead.addItemList({"OFF","250 ms","500 ms","1 BEAT","1 BAR"},1);
    lookahead.setTooltip("Lookahead delays output audio and is reported to the host for compensation.");
    addAndMakeVisible(source);addAndMakeVisible(lookahead);
    latency.setColour(juce::Label::textColourId,Theme::muted);latency.setJustificationType(juce::Justification::centredRight);
    addAndMakeVisible(latency);startTimerHz(10);
  }
  void paint(juce::Graphics& g) override {
    Theme::panelBackground(g,getLocalBounds().toFloat());Theme::title(g,"GAP DETECTOR",{14,7,200,22});
    const auto strip=juce::Rectangle<float>(float(getWidth())*0.52f,32.0f,float(getWidth())*0.46f,27.0f);
    g.setColour(Theme::border);g.fillRoundedRectangle(strip,5.0f);
    const auto fast=processor.fastMeter.load(),slow=processor.slowMeter.load(),threshold=processor.thresholdMeter.load();
    const float maxRef=std::max(0.015f,std::max(slow,fast)*1.5f);
    g.setColour(Theme::violet);g.fillRoundedRectangle(strip.getX()+2,strip.getY()+5,std::clamp(threshold/maxRef,0.0f,1.0f)*(strip.getWidth()-4),4,2);
    g.setColour(Theme::cyan);g.fillRoundedRectangle(strip.getX()+2,strip.getY()+12,std::clamp(fast/maxRef,0.0f,1.0f)*(strip.getWidth()-4),4,2);
    g.setColour(Theme::amber);g.fillRoundedRectangle(strip.getX()+2,strip.getY()+19,std::clamp(slow/maxRef,0.0f,1.0f)*(strip.getWidth()-4),4,2);
  }
  void resized() override {
    const int usable=getWidth()-18,knobW=std::min(105,(usable-180)/6);
    for(int i=0;i<6;++i){int x=10+i*knobW;knobs[size_t(i)].setBounds(x,55,knobW,75);knobLabels[size_t(i)].setBounds(x,31,knobW,19);}
    const int comboX=getWidth()-175;
    source.setBounds(comboX,69,160,25);lookahead.setBounds(comboX,103,160,25);
    latency.setBounds(comboX-38,32,190,22);
  }
private:
  void timerCallback() override {
    latency.setText("LATENCY "+juce::String(1000.0*processor.latencyRequested.load()/std::max(1.0,processor.sampleRateAtomic.load()),1)+" ms",juce::dontSendNotification);
    repaint();
  }
  SkellSilenceAudioProcessor& processor;
  std::array<juce::Slider,6> knobs;
  std::array<juce::Label,6> knobLabels;
  std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>,6> attachments;
  juce::ComboBox source,lookahead;
  juce::AudioProcessorValueTreeState::ComboBoxAttachment sourceAttachment,lookaheadAttachment;
  juce::Label latency;
};
}
