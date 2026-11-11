#pragma once
#include <JuceHeader.h>
#include <cmath>

namespace skell::ui {
// UI-only presentation: preserve the exact underlying automation value and
// preset range while displaying approachable, whole-number units.
class WholeNumberSlider : public juce::Slider {
public:
  explicit WholeNumberSlider(double multiplier = 1.0, juce::String unit = {})
    : scale(multiplier), suffix(std::move(unit)) {}
  void setReadout(double multiplier, const juce::String& unit = {}) {scale=multiplier;suffix=unit;}
  juce::String getTextFromValue(double value) override {
    return juce::String(juce::roundToInt(value * scale)) + suffix;
  }
  double getValueFromText(const juce::String& input) override {
    return input.trim().getDoubleValue() / scale;
  }
private:
  double scale;
  juce::String suffix;
};
class WholePercentSlider final : public WholeNumberSlider {
public:
  WholePercentSlider() : WholeNumberSlider(100.0, "%") {}
};
}
