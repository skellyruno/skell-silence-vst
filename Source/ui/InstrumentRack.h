#pragma once
#include "InstrumentStrip.h"
#include <array>
#include <memory>
namespace skell::ui {
class InstrumentRack final : public juce::Component,private juce::Timer {
public:
 explicit InstrumentRack(SkellSilenceAudioProcessor& p):processor(p){
   for(int i=0;i<7;++i){
     strips[size_t(i)]=std::make_unique<InstrumentStrip>(p,i);
     addAndMakeVisible(*strips[size_t(i)]);
   }
   startTimerHz(15); // Refresh activity only, not the whole editor.
 }
 void paint(juce::Graphics& g) override {
   Theme::panelBackground(g,getLocalBounds().toFloat());
   Theme::title(g,"03  /  GAP INSTRUMENTS",{15,10,245,20});
   const int active=processor.activeMask.load(std::memory_order_relaxed);
   g.setColour(active?Theme::green:Theme::muted);
   g.fillEllipse(float(getWidth()-87),17.0f,6.0f,6.0f);
   g.setFont(Theme::font(10,true));
   g.drawText(active?"PLAYING":"ARMED",getWidth()-78,9,68,23,juce::Justification::centredLeft);
 }
 void resized() override {
   constexpr int top=41,row=58;
   for(int i=0;i<7;++i)strips[size_t(i)]->setBounds(9,top+i*row,getWidth()-18,row);
 }
private:
 void timerCallback() override {
   const int mask=processor.activeMask.load(std::memory_order_relaxed);
   if(mask==lastMask)return;
   lastMask=mask;
   repaint(getWidth()-95,7,88,30);
   for(auto& strip:strips)strip->repaint();
 }
 SkellSilenceAudioProcessor& processor;
 std::array<std::unique_ptr<InstrumentStrip>,7> strips;
 int lastMask=-1;
};
}
