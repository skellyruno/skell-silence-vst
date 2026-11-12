#pragma once
#include "Theme.h"
#include "../PluginProcessor.h"
#include <array>
#include <algorithm>
#include <cstdint>

namespace skell::ui {
// Decorative only, fed by the same real audio telemetry as the timeline.
// No random animation, DSP allocations, or fabricated playback state.
class AudioFeedbackStrip final : public juce::Component, private juce::Timer {
public:
  explicit AudioFeedbackStrip(SkellSilenceAudioProcessor& p) : processor(p) {
    setInterceptsMouseClicks(false,false);
    setComponentID("audio-feedback");
    startTimerHz(24);
  }
  void setVertical(bool isVertical) {
    if(vertical!=isVertical) { vertical=isVertical;repaint(); }
  }
  void paint(juce::Graphics& g) override {
    const auto r=getLocalBounds().toFloat();
    if(r.isEmpty())return;
    const float primary=vertical ? r.getHeight() : r.getWidth();
    const float secondary=vertical ? r.getWidth() : r.getHeight();
    const float center=secondary*0.5f;
    const float start=vertical ? r.getY()+5.0f : r.getX()+5.0f;
    const float length=std::max(1.0f,primary-10.0f);
    g.setColour(Theme::border.withAlpha(0.82f));
    if(vertical){
      g.fillRoundedRectangle(center-1.5f,0.0f,3.0f,primary,1.5f);
      g.setColour(Theme::green.withAlpha(0.36f));
      g.drawLine(center+3.0f,4.0f,center+3.0f,primary-4.0f,1.1f);
    }else{
      g.fillRoundedRectangle(0.0f,center-1.5f,primary,3.0f,1.5f);
      g.setColour(Theme::green.withAlpha(0.38f));
      g.drawLine(5.0f,center+3.3f,primary-5.0f,center+3.3f,1.0f);
    }
    const auto seq=processor.waveformSequence.load(std::memory_order_acquire);
    constexpr int points=72;
    juce::Path upper,lower;
    for(int i=0;i<points;++i){
      const int64_t age=int64_t(points-i);
      const int64_t absolute=int64_t(seq)-age;
      const float observed=absolute<0?0.0f:
        processor.waveform[size_t(absolute%SkellSilenceAudioProcessor::waveformSize)]
         .load(std::memory_order_acquire);
      const float amplitude=std::clamp(observed,0.0f,1.0f);
      const float position=start+float(i)*length/float(points-1);
      const float motion=amplitude*std::max(0.0f,center-3.2f);
      const auto top=vertical?juce::Point<float>(center-motion,position)
                             :juce::Point<float>(position,center-motion);
      const auto bottom=vertical?juce::Point<float>(center+motion,position)
                                :juce::Point<float>(position,center+motion);
      if(i==0){upper.startNewSubPath(top);lower.startNewSubPath(bottom);}
      else {upper.lineTo(top);lower.lineTo(bottom);}
    }
    // Two smooth opposing envelopes, not a fabricated alternating sawtooth.
    // When no audio arrives they converge into one restrained white hairline.
    g.setColour(juce::Colours::white.withAlpha(0.10f));
    g.strokePath(upper,juce::PathStrokeType(3.0f,
      juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
    g.strokePath(lower,juce::PathStrokeType(3.0f,
      juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
    g.setColour(Theme::text.withAlpha(0.88f));
    g.strokePath(upper,juce::PathStrokeType(1.05f,
      juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
    g.strokePath(lower,juce::PathStrokeType(1.05f,
      juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
  }
private:
  void timerCallback() override {
    const auto seq=processor.waveformSequence.load(std::memory_order_acquire);
    if(lastSequence!=seq){lastSequence=seq;repaint();}
  }
  SkellSilenceAudioProcessor& processor;
  bool vertical=false;
  uint64_t lastSequence=~uint64_t(0);
};
}
