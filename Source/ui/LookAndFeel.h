#pragma once
#include "Theme.h"
#include <cmath>
namespace skell::ui {
class SilenceLookAndFeel final : public juce::LookAndFeel_V4 {
public:
  SilenceLookAndFeel(){
    setColour(juce::Slider::thumbColourId,Theme::green);
    setColour(juce::Slider::trackColourId,Theme::green);
    setColour(juce::Slider::backgroundColourId,Theme::border);
    setColour(juce::Slider::textBoxTextColourId,Theme::text);
    setColour(juce::Slider::textBoxBackgroundColourId,Theme::inset);
    setColour(juce::Slider::textBoxOutlineColourId,Theme::border);
    setColour(juce::Label::textColourId,Theme::text);
    setColour(juce::ComboBox::backgroundColourId,Theme::inset);
    setColour(juce::ComboBox::textColourId,Theme::text);
    setColour(juce::ComboBox::outlineColourId,Theme::border);
    setColour(juce::TextButton::buttonColourId,Theme::raised);
    setColour(juce::TextButton::textColourOffId,Theme::text);
    setColour(juce::TextButton::textColourOnId,Theme::green);
    setColour(juce::ToggleButton::textColourId,Theme::text);
    setColour(juce::PopupMenu::backgroundColourId,Theme::panel);
    setColour(juce::PopupMenu::textColourId,Theme::text);
    setColour(juce::TooltipWindow::backgroundColourId,Theme::raised);
    setColour(juce::TooltipWindow::textColourId,Theme::text);
  }
  void drawButtonBackground(juce::Graphics& g,juce::Button& b,const juce::Colour&,bool hover,bool down) override {
    auto r=b.getLocalBounds().toFloat().reduced(0.7f);
    const bool active=b.getToggleState();
    g.setColour(active?Theme::green.withAlpha(0.15f):(down?Theme::raised.brighter(0.18f):hover?Theme::raised.brighter(0.10f):Theme::raised));
    g.fillRoundedRectangle(r,6.0f);
    g.setColour(active?Theme::green.withAlpha(0.62f):(hover?Theme::muted.withAlpha(0.65f):Theme::border));
    g.drawRoundedRectangle(r,6.0f,1.0f);
  }
  void drawRotarySlider(juce::Graphics& g,int x,int y,int width,int height,float pos,float start,float end,juce::Slider& slider) override {
    const juce::Rectangle<float> r(float(x),float(y),float(width),float(height));
    const float radius=std::max(8.0f,std::min(r.getWidth(),r.getHeight())*0.34f);
    const auto center=r.getCentre();
    const auto accent=slider.getComponentID()=="tension"?Theme::amber:Theme::green;
    g.setColour(Theme::inset);g.fillEllipse(center.x-radius,center.y-radius,2*radius,2*radius);
    g.setColour(Theme::raised.brighter(0.3f));g.drawEllipse(center.x-radius,center.y-radius,2*radius,2*radius,2.0f);
    juce::Path track,arc;
    const float a=start+pos*(end-start);
    track.addCentredArc(center.x,center.y,radius+5,radius+5,0,start,end,true);
    arc.addCentredArc(center.x,center.y,radius+5,radius+5,0,start,a,true);
    g.setColour(Theme::border.brighter(0.30f));g.strokePath(track,juce::PathStrokeType(3.0f,juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
    g.setColour(accent);g.strokePath(arc,juce::PathStrokeType(3.0f,juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
    g.setColour(Theme::text);g.drawLine(center.x,center.y,center.x+std::sin(a)*radius*0.72f,center.y-std::cos(a)*radius*0.72f,2.5f);
    g.setColour(Theme::muted.withAlpha(0.6f));g.fillEllipse(center.x-2,center.y-2,4,4);
  }
  void drawLinearSlider(juce::Graphics& g,int x,int y,int width,int height,float sliderPos,float,float,juce::Slider::SliderStyle style,juce::Slider& s) override {
    if(style!=juce::Slider::LinearHorizontal){juce::LookAndFeel_V4::drawLinearSlider(g,x,y,width,height,sliderPos,sliderPos,sliderPos,style,s);return;}
    const float cy=float(y+height/2);
    g.setColour(Theme::border);g.fillRoundedRectangle(float(x+7),cy-2,float(width-14),4,2);
    g.setColour(s.getComponentID()=="mix"?Theme::cyan:Theme::green);
    g.fillRoundedRectangle(float(x+7),cy-2,std::max(0.0f,sliderPos-float(x+7)),4,2);
    const auto c=s.getComponentID()=="mix"?Theme::cyan:Theme::green;
    g.setColour(Theme::inset);g.fillEllipse(sliderPos-7,cy-7,14,14);
    g.setColour(c);g.fillEllipse(sliderPos-4,cy-4,8,8);
  }
  void drawToggleButton(juce::Graphics& g,juce::ToggleButton& b,bool hover,bool /*down*/) override {
    const bool on=b.getToggleState();
    const auto rect=juce::Rectangle<float>(3.0f,float(b.getHeight()/2)-8.0f,16.0f,16.0f);
    g.setColour(on?Theme::green.withAlpha(0.18f):Theme::inset);g.fillRoundedRectangle(rect,4.0f);
    g.setColour(on?Theme::green:hover?Theme::muted:Theme::border.brighter(0.1f));g.drawRoundedRectangle(rect.reduced(0.5f),4.0f,1.1f);
    if(on){juce::Path mark;mark.startNewSubPath(7.0f,float(b.getHeight()/2));mark.lineTo(10.0f,float(b.getHeight()/2)+3);mark.lineTo(15.0f,float(b.getHeight()/2)-4);g.strokePath(mark,juce::PathStrokeType(1.7f));}
    if(b.getButtonText().isNotEmpty()){
      g.setColour(on?Theme::text:Theme::muted);g.setFont(Theme::font(12.0f,on));
      g.drawFittedText(b.getButtonText(),23,0,b.getWidth()-25,b.getHeight(),juce::Justification::centredLeft,1);
    }
  }
};
}
