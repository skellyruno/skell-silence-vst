#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ui/LookAndFeel.h"
#include "ui/HeaderBar.h"
#include "ui/GapTimeline.h"
#include "ui/DetectionPanel.h"
#include "ui/InstrumentRack.h"
#include "ui/LengthRulesMatrix.h"
#include "ui/TensionKnob.h"
#include "ui/SimpleView.h"

class SkellSilenceAudioProcessorEditor final : public juce::AudioProcessorEditor {
public:
 explicit SkellSilenceAudioProcessorEditor(SkellSilenceAudioProcessor&);
 ~SkellSilenceAudioProcessorEditor() override;
 void paint(juce::Graphics&) override;
 void resized() override;
 void setAdvancedMode(bool advanced);
 bool isAdvancedMode() const noexcept {return advancedMode;}
private:
 SkellSilenceAudioProcessor& processor;
 skell::ui::SilenceLookAndFeel look;
 skell::ui::HeaderBar header;
 skell::ui::GapTimeline timeline;
 skell::ui::DetectionPanel detection;
 skell::ui::InstrumentRack rack;
 skell::ui::LengthRulesMatrix matrix;
 skell::ui::TensionKnob macros;
 skell::ui::SimpleView quick;
 bool advancedMode=false;
 juce::ComponentBoundsConstrainer constrainer;
 JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SkellSilenceAudioProcessorEditor)
};
