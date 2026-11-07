#pragma once
#include <JuceHeader.h>
namespace skell::ui::Theme {
inline const juce::Colour ink{0xff07090c},panel{0xff0e1217},border{0xff1b232c};
inline const juce::Colour cyan{0xff5ad2ff},violet{0xffb48cff},amber{0xffff9a5a};
inline const juce::Colour text{0xffc5ccd6},muted{0xff8292a2},green{0xff8bec9a};
inline juce::Font font(float height,bool bold=false) {return juce::Font(juce::FontOptions(height).withStyle(bold?"Bold":"Regular"));}
inline void panelBackground(juce::Graphics& g,juce::Rectangle<float> rect,float radius=12.0f) {
 g.setColour(panel);g.fillRoundedRectangle(rect,radius);
 g.setColour(border.brighter(0.18f));g.drawRoundedRectangle(rect.reduced(0.5f),radius,1.0f);
 g.setColour(green.withAlpha(0.24f));g.fillRoundedRectangle(rect.getX()+15.0f,rect.getY(),std::min(48.0f,rect.getWidth()-30.0f),1.0f,0.5f);
}
inline void title(juce::Graphics& g,const juce::String& label,juce::Rectangle<int> bounds) {
 g.setColour(muted);g.setFont(font(12.0f,true));g.drawFittedText(label,bounds,juce::Justification::centredLeft,1);
}
}
