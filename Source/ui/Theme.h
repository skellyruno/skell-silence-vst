#pragma once
#include <JuceHeader.h>
#include <algorithm>
#include <array>
namespace skell::ui::Theme {
inline const juce::Colour ink{0xff080c11}, panel{0xff111820}, border{0xff2a3441};
inline const juce::Colour inset{0xff0b1118}, raised{0xff19242e};
inline const juce::Colour cyan{0xff58d8ff}, violet{0xffb99aff}, amber{0xffffa968};
inline const juce::Colour text{0xffe4edf2}, muted{0xff93a7b4}, green{0xff86f5ad};
inline const std::array<juce::Colour,7> instruments{amber,green,violet,cyan,juce::Colour{0xff77baff},juce::Colour{0xffd0a4ff},green};
inline juce::Font font(float height,bool bold=false) { return juce::Font(juce::FontOptions(height).withStyle(bold?"Bold":"Regular")); }
inline void panelBackground(juce::Graphics& g,juce::Rectangle<float> r,float radius=11.0f) {
    g.setColour(panel); g.fillRoundedRectangle(r,radius);
    g.setColour(border); g.drawRoundedRectangle(r.reduced(0.6f),radius,1.0f);
    g.setColour(juce::Colours::white.withAlpha(0.025f));g.drawHorizontalLine(int(r.getY()+1),r.getX()+radius,r.getRight()-radius);
}
inline void title(juce::Graphics& g,const juce::String& label,juce::Rectangle<int> r) {
    g.setColour(muted); g.setFont(font(11.0f,true));g.drawFittedText(label,r,juce::Justification::centredLeft,1);
}
inline void pill(juce::Graphics& g,juce::Rectangle<float> r,juce::Colour color,bool active) {
    g.setColour(active?color.withAlpha(0.16f):raised);g.fillRoundedRectangle(r,5.0f);
    g.setColour(active?color.withAlpha(0.7f):border);g.drawRoundedRectangle(r.reduced(0.5f),5.0f,1.0f);
}
}
