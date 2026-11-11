#pragma once
#include <JuceHeader.h>
#include <SkellCore/SkullTheme.h>
#include <algorithm>
#include <array>
#include <cmath>
namespace skell::ui::Theme {
// Official SkellCore Neon palette, pinned by CMake.
inline const auto core = skellcore::ui::skullPalette(skellcore::ui::SkullSkin::Neon);
inline const juce::Colour ink = core.background;
inline const juce::Colour panel = core.panel;
inline const juce::Colour border = core.line.withAlpha(0.72f);
inline const juce::Colour inset{0xff070b08}, raised = core.panelHi;
inline const juce::Colour green = core.accent;
inline const juce::Colour text = core.bone, muted = core.boneDim;
inline const juce::Colour cyan{0xffabff79}, violet{0xff71cf79}, amber{0xffd1fb83};
inline const std::array<juce::Colour,7> instruments{
  green, juce::Colour{0xffb5fa8d},juce::Colour{0xff77d982},
  juce::Colour{0xff8ef18e},juce::Colour{0xffdcfa99},
  juce::Colour{0xff6ed874},juce::Colour{0xffa4e8a0}};
// One envelope vocabulary for both the instrument rack and timeline overlays.
inline float instrumentEnvelope(int instrument,float phase) noexcept {
    const float x=std::clamp(phase,0.0f,1.0f);
    switch(instrument){
      case 0:return (1.0f-x)*(1.0f-x);
      case 1:return std::sin(3.14159265f*x);
      case 2:return x*x;
      case 3:return std::min(1.0f,5.0f*x)*std::min(1.0f,5.0f*(1.0f-x));
      case 4:return std::exp(-7.0f*x);
      case 5:return x*x*x;
      case 6:return std::abs(std::sin(3.14159265f*5.0f*x))*(1.0f-x);
      default:return x;
    }
}
inline juce::Font font(float height,bool bold=false) { return juce::Font(juce::FontOptions(height).withStyle(bold?"Bold":"Regular")); }
inline void panelBackground(juce::Graphics& g,juce::Rectangle<float> r,float radius=11.0f) {
    g.setGradientFill(juce::ColourGradient(panel.brighter(0.075f),r.getX(),r.getY(),
                                          panel.darker(0.09f),r.getRight(),r.getBottom(),false));
    g.fillRoundedRectangle(r,radius);
    g.setColour(border.withAlpha(0.82f));
    g.drawRoundedRectangle(r.reduced(0.6f),radius,1.0f);
    g.setColour(juce::Colours::white.withAlpha(0.035f));
    g.drawHorizontalLine(int(r.getY()+1),r.getX()+radius,r.getRight()-radius);
}
inline void sectionRule(juce::Graphics& g,float x,float y,float width,juce::Colour accent=green) {
    g.setColour(border.withAlpha(0.65f));g.drawHorizontalLine(int(y),x,x+width);
    g.setColour(accent.withAlpha(0.90f));g.fillRoundedRectangle(x,y-1.0f,36.0f,2.0f,1.0f);
}
inline void title(juce::Graphics& g,const juce::String& label,juce::Rectangle<int> r) {
    g.setColour(green);g.fillRoundedRectangle(float(r.getX()),float(r.getY()+5),3.0f,float(std::max(8,r.getHeight()-11)),1.5f);
    g.setColour(text);g.setFont(font(13.0f,true));
    g.drawFittedText(label,r.withTrimmedLeft(12),juce::Justification::centredLeft,1);
}
inline void pill(juce::Graphics& g,juce::Rectangle<float> r,juce::Colour color,bool active) {
    g.setColour(active?color.withAlpha(0.16f):raised);g.fillRoundedRectangle(r,5.0f);
    g.setColour(active?color.withAlpha(0.7f):border);g.drawRoundedRectangle(r.reduced(0.5f),5.0f,1.0f);
}
}
