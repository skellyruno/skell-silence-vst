#pragma once
#include "Theme.h"
#include <SkellCore/SkellHardwareUI.h>
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
    setColour(juce::PopupMenu::highlightedBackgroundColourId,Theme::green.withAlpha(0.28f));
    setColour(juce::PopupMenu::highlightedTextColourId,Theme::text);
    setColour(juce::Slider::textBoxHighlightColourId,Theme::green.withAlpha(0.32f));
    setColour(juce::TooltipWindow::backgroundColourId,Theme::raised);
    setColour(juce::TooltipWindow::textColourId,Theme::text);
  }
  void drawButtonBackground(juce::Graphics& g,juce::Button& b,const juce::Colour&,bool hover,bool down) override {
    auto r=b.getLocalBounds().toFloat().reduced(0.7f);
    const bool active=b.getToggleState();
    g.setGradientFill(juce::ColourGradient(active?Theme::green.withAlpha(0.13f):
      down?Theme::raised.brighter(0.38f):hover?Theme::raised.brighter(0.27f):Theme::raised.brighter(0.11f),
      r.getX(),r.getY(),active?Theme::green.withAlpha(0.08f):Theme::inset,
      r.getRight(),r.getBottom(),false));
    g.fillRoundedRectangle(r,7.0f);
    g.setColour(juce::Colours::white.withAlpha(0.08f));
    g.drawHorizontalLine(int(r.getY()+1),r.getX()+8,r.getRight()-8);
    g.setColour(active?Theme::green.withAlpha(0.62f):(hover?Theme::muted.withAlpha(0.65f):Theme::border));
    g.drawRoundedRectangle(r,7.0f,1.0f);
    if (b.hasKeyboardFocus(true)) {
      g.setColour(Theme::green.withAlpha(0.85f));
      g.drawRoundedRectangle(r.reduced(1.5f),5.5f,1.2f);
    }
  }
  // Match the native resize grip to the black/neon-green hardware finish.
  // The host still owns the resize behaviour and the fixed aspect ratio.
  void drawCornerResizer(juce::Graphics& g,int width,int height,
                         bool mouseOver,bool mouseDragging) override {
    if(width<9 || height<9)return;
    const float x=float(width),y=float(height);
    for(int i=0;i<3;++i){
      const float offset=4.0f+float(i)*5.0f;
      const float fromX=x-offset,fromY=y-3.0f;
      const float toX=x-3.0f,toY=y-offset;
      g.setColour(juce::Colours::black.withAlpha(0.60f));
      g.drawLine(fromX+0.8f,fromY+0.8f,toX+0.8f,toY+0.8f,2.0f);
      g.setColour(Theme::green.withAlpha(mouseDragging?0.98f:mouseOver?0.85f:0.51f));
      g.drawLine(fromX,fromY,toX,toY,1.15f);
    }
  }
  void drawRotarySlider(juce::Graphics& g,int x,int y,int width,int height,
                        float pos,float start,float end,juce::Slider&) override {
    // One SkellCore hardware renderer shared by all current and future plugins.
    skellcore::ui::drawHardwareKnob(g,
      {float(x),float(y),float(width),float(height)},pos,start,end,
      Theme::green,Theme::raised,Theme::border,Theme::text);
  }
  void drawLinearSlider(juce::Graphics& g,int x,int y,int width,int height,float sliderPos,float,float,juce::Slider::SliderStyle style,juce::Slider& s) override {
    if(style!=juce::Slider::LinearHorizontal){juce::LookAndFeel_V4::drawLinearSlider(g,x,y,width,height,sliderPos,sliderPos,sliderPos,style,s);return;}
    const float cy=float(y+height/2);
    g.setColour(Theme::border);g.fillRoundedRectangle(float(x+7),cy-2,float(width-14),4,2);
    const auto c=Theme::green;
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
    if (b.getButtonText().isEmpty()) {
      // The rules matrix uses real buttons with large, whole-cell hit areas.
      const auto tile=b.getLocalBounds().toFloat().reduced(1.0f,1.6f);
      g.setColour(on?Theme::green.withAlpha(0.25f):Theme::inset);
      g.fillRoundedRectangle(tile,4.0f);
      g.setColour(on?Theme::green:Theme::border.brighter(0.15f));
      g.drawRoundedRectangle(tile.reduced(0.55f),4.0f,on?1.4f:0.9f);
      if (on) {
        juce::Path check;
        const auto m=tile.getCentre();
        check.startNewSubPath(m.x-5.5f,m.y);check.lineTo(m.x-1.4f,m.y+3.4f);
        check.lineTo(m.x+6.1f,m.y-4.5f);
        g.strokePath(check,juce::PathStrokeType(2.0f,juce::PathStrokeType::curved,juce::PathStrokeType::rounded));
      } else {
        g.setColour(Theme::muted.withAlpha(0.30f));
        g.fillRoundedRectangle(tile.getCentreX()-3,tile.getCentreY()-0.8f,6,1.6f,0.8f);
      }
      if(b.hasKeyboardFocus(true)){
        g.setColour(Theme::green.withAlpha(0.8f));
        g.drawRoundedRectangle(tile.reduced(1.0f),3.0f,1.0f);
      }
      return;
    }
    const auto rect=juce::Rectangle<float>(3.0f,float(b.getHeight()/2)-8.0f,16.0f,16.0f);
    g.setColour(on?accent.withAlpha(0.18f):Theme::inset);g.fillRoundedRectangle(rect,4.0f);
    g.setColour(on?accent:hover?Theme::muted:Theme::border.brighter(0.1f));g.drawRoundedRectangle(rect.reduced(0.5f),4.0f,1.1f);
    if(on){juce::Path mark;mark.startNewSubPath(7.0f,float(b.getHeight()/2));mark.lineTo(10.0f,float(b.getHeight()/2)+3);mark.lineTo(15.0f,float(b.getHeight()/2)-4);g.strokePath(mark,juce::PathStrokeType(1.7f));}
    if(b.getButtonText().isNotEmpty()){
      g.setColour(on?Theme::text:Theme::muted);g.setFont(Theme::font(13.5f,on));
      g.drawFittedText(b.getButtonText(),23,0,b.getWidth()-25,b.getHeight(),juce::Justification::centredLeft,1);
    }
  }
};
}
