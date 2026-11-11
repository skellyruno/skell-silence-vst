#pragma once
#include "Theme.h"
#include "WholePercentSlider.h"
#include "../PluginProcessor.h"
#include <array>
#include <memory>
#include <functional>

namespace skell::ui {
// Three task-oriented controls. Never changes parameter identities or DSP.
class SimpleView final : public juce::Component {
public:
  explicit SimpleView(SkellSilenceAudioProcessor& processorIn) : processor(processorIn) {
    constexpr std::array<const char*,3> ids {{"mix", "tension", "space"}};
    constexpr std::array<const char*,3> tips {{
      "How much gap effect to hear. 0% = only the original song.",
      "Strength of the swell and riser effects.",
      "Amount of reverb added to the gap effects."
    }};
    for (size_t i=0; i<knobs.size(); ++i) {
      auto& slider=knobs[i];
      slider.setComponentID(i==0?"mix":i==1?"tension":"space");
      slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
      slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 90, 28);
      slider.setTooltip(tips[i]);
      if(auto* parameter=processor.parameters.getParameter(ids[i]))
        slider.setDoubleClickReturnValue(true, parameter->convertFrom0to1(parameter->getDefaultValue()));
      attachments[i]=std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processor.parameters,ids[i],slider);
      addAndMakeVisible(slider);
    }
    more.setButtonText("EDIT EFFECTS");
    more.setComponentID("simple-edit-effects");
    more.setTooltip("Open advanced controls and choose which effects play in each gap.");
    addAndMakeVisible(more);
  }
  void resized() override {
    // All geometry is in the 1200x760 design space and scaled by PluginEditor.
    for (int i=0;i<3;++i)knobs[size_t(i)].setBounds(538+i*154,51,134,135);
    more.setBounds(1015,79,116,56);
  }
  void paint(juce::Graphics& g) override {
    Theme::panelBackground(g,getLocalBounds().toFloat());
    g.setColour(Theme::green);g.fillRoundedRectangle(24.0f,24.0f,4.0f,31.0f,2.0f);
    g.setColour(Theme::text);g.setFont(Theme::font(22,true));
    g.drawText("YOU PLAY. WE FIND THE GAPS.",40,17,464,45,juce::Justification::centredLeft);
    g.setColour(Theme::muted);g.setFont(Theme::font(15));
    g.drawFittedText("Effects fill the quiet moments between hits and phrases.",40,62,460,35,
                     juce::Justification::centredLeft,2);
    g.setColour(Theme::border.withAlpha(0.9f));g.drawHorizontalLine(111,40,480);
    g.setColour(Theme::muted);g.setFont(Theme::font(14,true));
    g.drawText("1  PLAY AUDIO",40,129,138,22,juce::Justification::centredLeft);
    g.drawText("2  WATCH THE GAPS",192,129,176,22,juce::Justification::centredLeft);
    g.drawText("3  SHAPE THE EFFECT",381,129,166,22,juce::Justification::centredLeft);
    g.setColour(Theme::border);g.drawVerticalLine(515,28,getHeight()-28);
    constexpr std::array<const char*,3> titles {{"MIX", "ENERGY", "SPACE"}};
    constexpr std::array<const char*,3> captions {{"EFFECT AMOUNT", "BUILD INTENSITY", "REVERB TAIL"}};
    for (int i=0;i<3;++i) {
      const auto cx=605+i*154;
      g.setColour(i==0?Theme::green:i==1?Theme::amber:Theme::violet);
      g.setFont(Theme::font(17,true));
      g.drawText(titles[size_t(i)],cx-72,18,144,28,juce::Justification::centred);
      g.setColour(Theme::muted);g.setFont(Theme::font(12));
      g.drawText(captions[size_t(i)],cx-72,190,144,19,juce::Justification::centred);
    }
  }
  void setEditCallback(std::function<void()> cb) {more.onClick=std::move(cb);}
private:
  SkellSilenceAudioProcessor& processor;
  std::array<WholePercentSlider,3> knobs;
  std::array<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>,3> attachments;
  juce::TextButton more;
};
}
