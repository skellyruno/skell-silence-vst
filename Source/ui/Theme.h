#pragma once
#include <JuceHeader.h>
#include <algorithm>
#include <array>
#include <cmath>
namespace skell::ui::Theme {
inline const juce::Colour ink{0xff080c11}, panel{0xff111820}, border{0xff2a3441};
inline const juce::Colour inset{0xff0b1118}, raised{0xff19242e};
inline const juce::Colour cyan{0xff58d8ff}, violet{0xffb99aff}, amber{0xffffa968};
inline const juce::Colour text{0xffedf5f7}, muted{0xffa0b1bf}, green{0xff86f5ad};
inline const std::array<juce::Colour,7> instruments{amber,green,violet,cyan,juce::Colour{0xff77baff},juce::Colour{0xffd0a4ff},green};
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
    g.setColour(panel); g.fillRoundedRectangle(r,radius);
    g.setColour(border); g.drawRoundedRectangle(r.reduced(0.6f),radius,1.0f);
    g.setColour(juce::Colours::white.withAlpha(0.047f));
    g.drawHorizontalLine(int(r.getY()+1),r.getX()+radius,r.getRight()-radius);
}
inline void title(juce::Graphics& g,const juce::String& label,juce::Rectangle<int> r) {
    g.setColour(muted); g.setFont(font(11.0f,true));g.drawFittedText(label,r,juce::Justification::centredLeft,1);
}
inline void pill(juce::Graphics& g,juce::Rectangle<float> r,juce::Colour color,bool active) {
    g.setColour(active?color.withAlpha(0.16f):raised);g.fillRoundedRectangle(r,5.0f);
    g.setColour(active?color.withAlpha(0.7f):border);g.drawRoundedRectangle(r.reduced(0.5f),5.0f,1.0f);
}
}
