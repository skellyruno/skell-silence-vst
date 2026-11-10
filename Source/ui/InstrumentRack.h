#pragma once
#include "InstrumentStrip.h"
#include <array>
#include <cstdint>
#include <memory>
namespace skell::ui {
class InstrumentRack final : public juce::Component,private juce::Timer {
public:
 explicit InstrumentRack(SkellSilenceAudioProcessor& p):processor(p){
   lastStripSettings.fill(~std::uint32_t(0));
   for(int i=0;i<7;++i){
     strips[size_t(i)]=std::make_unique<InstrumentStrip>(p,i);
     addAndMakeVisible(*strips[size_t(i)]);
   }
   startTimerHz(15); // Refresh activity only, not the whole editor.
 }
 void paint(juce::Graphics& g) override {
   Theme::panelBackground(g,getLocalBounds().toFloat());
   Theme::title(g,"03  /  INSTRUMENT DECK",{15,9,239,23});
   Theme::sectionRule(g,15.0f,37.0f,float(getWidth()-30),Theme::amber);
   const int active=processor.activeMask.load(std::memory_order_relaxed);
   g.setColour(active?Theme::green:Theme::muted);
   g.fillEllipse(float(getWidth()-86),17.0f,7.0f,7.0f);
   g.setFont(Theme::font(11,true));
   g.drawText(active?"PLAYING":"ARMED",getWidth()-78,9,68,23,juce::Justification::centredLeft);
   g.setColour(Theme::muted.withAlpha(0.78f));g.setFont(Theme::font(9,true));
   g.drawText(processor.inputChannels.load(std::memory_order_relaxed)>1?"2 CH / STEREO":"1 CH / MONO",getWidth()-193,10,96,21,juce::Justification::centredRight);
 }
 void resized() override {
   constexpr int top=43,row=58;
   for(int i=0;i<7;++i)strips[size_t(i)]->setBounds(9,top+i*row,getWidth()-18,row);
 }
private:
 void timerCallback() override {
   const int mask=processor.activeMask.load(std::memory_order_relaxed);
   const int channels=processor.inputChannels.load(std::memory_order_relaxed);
   const int activeClass=processor.activeLengthClass.load(std::memory_order_relaxed);
   if(mask!=lastMask || channels!=lastChannels)
     repaint(getWidth()-195,7,185,30);
   for(size_t i=0;i<strips.size();++i){
     const auto fingerprint=strips[i]->settingsFingerprint();
     if(fingerprint!=lastStripSettings[i] || activeClass!=lastActiveClass
        || ((mask ^ lastMask) & (1 << int(i))) != 0){
       lastStripSettings[i]=fingerprint;
       strips[i]->repaint();
     }
   }
   lastMask=mask;lastChannels=channels;lastActiveClass=activeClass;
 }
 SkellSilenceAudioProcessor& processor;
 std::array<std::unique_ptr<InstrumentStrip>,7> strips;
 std::array<std::uint32_t,7> lastStripSettings{};
 int lastMask=-1,lastChannels=-1,lastActiveClass=-2;
};
}
