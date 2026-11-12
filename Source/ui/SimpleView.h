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
      "0% is pure dry audio and the default. Turn MIX up to hear gap effects.",
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
      slider.setMouseDragSensitivity(240);
      addAndMakeVisible(slider);
    }
    more.setButtonText("FX DETAIL");
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
    g.setColour(Theme::green.withAlpha(0.92f));
    g.fillRoundedRectangle(26.0f,23.0f,3.0f,35.0f,1.5f);
    g.setColour(Theme::muted);g.setFont(Theme::font(12.0f,true));
    g.drawText("GAP FX READY  /  DRY UNTIL YOU TURN UP MIX",42,18,452,24,juce::Justification::centredLeft);
    g.setColour(Theme::text);g.setFont(Theme::font(24.0f,true));
    g.drawFittedText("MAKE THE QUIET MOMENTS MOVE.",42,44,457,36,juce::Justification::centredLeft,1);
    g.setColour(Theme::muted);g.setFont(Theme::font(14.5f));
    g.drawFittedText("Play your track to find gaps. Raise MIX to hear the effects.",42,88,454,25,
                     juce::Justification::centredLeft,1);
    constexpr std::array<const char*,3> steps{{"01  DETECT", "02  SHAPE", "03  BLEND"}};
    for(int i=0;i<3;++i){
      const float x=43.0f+float(i)*153.0f;
      g.setColour(Theme::raised);g.fillRoundedRectangle(x,144.0f,138.0f,34.0f,6.0f);
      g.setColour(Theme::border);g.drawRoundedRectangle(x+0.5f,144.5f,137.0f,33.0f,6.0f,1.0f);
      g.setColour(i==0?Theme::green:Theme::muted);g.setFont(Theme::font(12.0f,true));
      g.drawText(steps[size_t(i)],int(x),146,138,30,juce::Justification::centred);
    }
    g.setColour(Theme::border);g.drawVerticalLine(514,24,getHeight()-24);
    // Machined inset plates separate the knob material from the panel surface.
    for(int i=0;i<3;++i){
      const float x=538.0f+float(i)*154.0f;
      const juce::Rectangle<float> plate{x+8.0f,47.0f,118.0f,135.0f};
      g.setColour(juce::Colours::black.withAlpha(0.29f));
      g.fillRoundedRectangle(plate.translated(0.0f,2.0f),11.0f);
      g.setGradientFill(juce::ColourGradient(Theme::inset,plate.getX(),plate.getY(),
                                           Theme::raised,plate.getRight(),plate.getBottom(),false));
      g.fillRoundedRectangle(plate,11.0f);
      g.setColour(Theme::border.withAlpha(0.82f));
      g.drawRoundedRectangle(plate.reduced(0.5f),10.5f,1.0f);
      g.setColour(juce::Colours::white.withAlpha(0.05f));
      g.drawHorizontalLine(int(plate.getY()+1),plate.getX()+12.0f,plate.getRight()-12.0f);
    }
    constexpr std::array<const char*,3> titles{{"MIX", "ENERGY", "SPACE"}};
    constexpr std::array<const char*,3> captions{{"EFFECT LEVEL", "RISE & SWELL", "REVERB TAIL"}};
    for(int i=0;i<3;++i){
      const auto cx=605+i*154;
      g.setColour(Theme::green);g.setFont(Theme::font(17.0f,true));
      g.drawText(titles[size_t(i)],cx-72,18,144,28,juce::Justification::centred);
      g.setColour(Theme::muted);g.setFont(Theme::font(12.0f));
      g.drawText(captions[size_t(i)],cx-72,190,144,20,juce::Justification::centred);
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
