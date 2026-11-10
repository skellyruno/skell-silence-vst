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
    const juce::Rectangle<float> r{float(x),float(y),float(width),float(height)};
    const float radius=std::max(8.0f,std::min(r.getWidth(),r.getHeight())*0.34f);
    const auto center=r.getCentre();
    const auto accent=slider.getComponentID()=="tension"?Theme::amber:Theme::green;
    // Quiet hardware bezel: graded metal centre, precise ticks and a readable
    // illuminated sweep without high-cost drop shadows or bitmap assets.
    g.setColour(Theme::border.withAlpha(0.75f));
    g.fillEllipse(center.x-radius-2,center.y-radius-2,2*radius+4,2*radius+4);
    g.setGradientFill(juce::ColourGradient(Theme::raised.brighter(0.13f),center.x,center.y-radius,
                                           Theme::inset,center.x,center.y+radius,false));
    g.fillEllipse(center.x-radius,center.y-radius,2*radius,2*radius);
    g.setColour(Theme::raised.brighter(0.45f));
    g.drawEllipse(center.x-radius+2,center.y-radius+2,2*radius-4,2*radius-4,1.0f);
    const float a=start+std::clamp(pos,0.0f,1.0f)*(end-start);
    for(int i=0;i<=10;++i){
      const float angle=start+float(i)/10.0f*(end-start);
      const float inner=radius+8.0f,outer=inner+(i%5==0?4.0f:2.0f);
      g.setColour(Theme::muted.withAlpha(i%5==0?0.55f:0.28f));
      g.drawLine(center.x+std::sin(angle)*inner,center.y-std::cos(angle)*inner,
                 center.x+std::sin(angle)*outer,center.y-std::cos(angle)*outer,1.0f);
    }
    juce::Path track,arc;
    track.addCentredArc(center.x,center.y,radius+5,radius+5,0,start,end,true);
    arc.addCentredArc(center.x,center.y,radius+5,radius+5,0,start,a,true);
    g.setColour(Theme::border.brighter(0.15f));
    g.strokePath(track,juce::PathStrokeType(3.0f,juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
    g.setColour(accent.withAlpha(0.18f));
    g.strokePath(arc,juce::PathStrokeType(5.4f,juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
    g.setColour(accent);
    g.strokePath(arc,juce::PathStrokeType(2.8f,juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
    const float tip=radius*0.72f;
    g.setColour(Theme::text);g.drawLine(center.x,center.y,
                                       center.x+std::sin(a)*tip,center.y-std::cos(a)*tip,2.2f);
    g.setColour(accent.withAlpha(0.85f));g.fillEllipse(center.x-2,center.y-2,4,4);
  }
  void drawLinearSlider(juce::Graphics& g,int x,int y,int width,int height,float sliderPos,float,float,juce::Slider::SliderStyle style,juce::Slider& s) override {
    if(style!=juce::Slider::LinearHorizontal){juce::LookAndFeel_V4::drawLinearSlider(g,x,y,width,height,sliderPos,sliderPos,sliderPos,style,s);return;}
    const float cy=float(y+height/2);
    g.setColour(Theme::border);g.fillRoundedRectangle(float(x+7),cy-2,float(width-14),4,2);
    const auto c=s.getComponentID()=="mix"?Theme::cyan:s.findColour(juce::Slider::trackColourId);
    g.setColour(c.withAlpha(0.18f));
    g.fillRoundedRectangle(float(x+7),cy-3,std::max(0.0f,sliderPos-float(x+7)),6,3);
    g.setColour(c);
    g.fillRoundedRectangle(float(x+7),cy-1.5f,std::max(0.0f,sliderPos-float(x+7)),3,1.5f);
    g.setColour(Theme::inset);g.fillEllipse(sliderPos-7,cy-7,14,14);
    g.setColour(c);g.fillEllipse(sliderPos-4,cy-4,8,8);
  }
  void drawToggleButton(juce::Graphics& g,juce::ToggleButton& b,bool hover,bool /*down*/) override {
    const bool on=b.getToggleState();
    const auto accent=b.findColour(juce::ToggleButton::tickColourId,true);
    const auto rect=juce::Rectangle<float>(3.0f,float(b.getHeight()/2)-8.0f,16.0f,16.0f);
    g.setColour(on?accent.withAlpha(0.18f):Theme::inset);g.fillRoundedRectangle(rect,4.0f);
    g.setColour(on?accent:hover?Theme::muted:Theme::border.brighter(0.1f));g.drawRoundedRectangle(rect.reduced(0.5f),4.0f,1.1f);
    if(on){juce::Path mark;mark.startNewSubPath(7.0f,float(b.getHeight()/2));mark.lineTo(10.0f,float(b.getHeight()/2)+3);mark.lineTo(15.0f,float(b.getHeight()/2)-4);g.strokePath(mark,juce::PathStrokeType(1.7f));}
    if(b.getButtonText().isNotEmpty()){
      g.setColour(on?Theme::text:Theme::muted);g.setFont(Theme::font(12.0f,on));
      g.drawFittedText(b.getButtonText(),23,0,b.getWidth()-25,b.getHeight(),juce::Justification::centredLeft,1);
    }
  }
};
}
