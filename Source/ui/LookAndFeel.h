#pragma once
#include "Theme.h"
namespace skell::ui {
class SilenceLookAndFeel final : public juce::LookAndFeel_V4 {
public:
  SilenceLookAndFeel(){
    setColour(juce::Slider::thumbColourId,Theme::cyan);
    setColour(juce::Slider::trackColourId,Theme::cyan);
    setColour(juce::Slider::backgroundColourId,Theme::border);
    setColour(juce::Slider::textBoxTextColourId,Theme::text);
    setColour(juce::Slider::textBoxOutlineColourId,juce::Colours::transparentBlack);
    setColour(juce::Label::textColourId,Theme::text);
    setColour(juce::ComboBox::backgroundColourId,Theme::panel);
    setColour(juce::ComboBox::textColourId,Theme::text);
    setColour(juce::ComboBox::outlineColourId,Theme::border);
    setColour(juce::TextButton::buttonColourId,Theme::panel);
    setColour(juce::TextButton::textColourOffId,Theme::text);
    setColour(juce::ToggleButton::textColourId,Theme::text);
    setColour(juce::PopupMenu::backgroundColourId,Theme::panel);
    setColour(juce::PopupMenu::textColourId,Theme::text);
  }
  void drawRotarySlider(juce::Graphics& g,int x,int y,int w,int h,float proportion,float start,float end,juce::Slider& slider) override {
    const auto bounds=juce::Rectangle<float>(float(x),float(y),float(w),float(h));
    const float r=std::max(8.0f,std::min(bounds.getWidth(),bounds.getHeight())*0.36f);
    auto c=bounds.getCentre();
    const auto accent=slider.getComponentID()=="tension"?Theme::amber:Theme::cyan;
    g.setColour(juce::Colour(0xff151d25));g.fillEllipse(c.x-r,c.y-r,2*r,2*r);
    g.setColour(Theme::border);g.drawEllipse(c.x-r,c.y-r,2*r,2*r,1.5f);
    const float angle=start+proportion*(end-start);
    juce::Path backgroundArc,activeArc;
    backgroundArc.addCentredArc(c.x,c.y,r+4,r+4,0,start,end,true);
    activeArc.addCentredArc(c.x,c.y,r+4,r+4,0,start,angle,true);
    g.setColour(Theme::muted.withAlpha(0.3f));g.strokePath(backgroundArc,juce::PathStrokeType(3.0f));
    g.setColour(accent);g.strokePath(activeArc,juce::PathStrokeType(3.0f,juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
    g.setColour(Theme::text);g.drawLine(c.x,c.y,c.x+std::sin(angle)*r*0.70f,c.y-std::cos(angle)*r*0.70f,2.4f);
  }
};
}
