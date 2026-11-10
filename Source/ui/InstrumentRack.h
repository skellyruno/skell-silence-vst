#pragma once
#include "InstrumentStrip.h"
#include <array>
#include <memory>
namespace skell::ui {
class InstrumentRack final : public juce::Component {
public:
 explicit InstrumentRack(SkellSilenceAudioProcessor& p){
   for(int i=0;i<7;++i){strips[size_t(i)]=std::make_unique<InstrumentStrip>(p,i);addAndMakeVisible(*strips[size_t(i)]);}
 }
 void paint(juce::Graphics& g) override {
   Theme::panelBackground(g,getLocalBounds().toFloat());
   Theme::title(g,"03  /  GAP INSTRUMENTS",{15,11,245,20});
   g.setColour(Theme::green.withAlpha(0.8f));g.fillEllipse(float(getWidth()-30),15.0f,6,6);
 }
 void resized() override {
   constexpr int top=41;
   constexpr int row=58;
   for(int i=0;i<7;++i)strips[size_t(i)]->setBounds(9,top+i*row,getWidth()-18,row);
 }
private:
 std::array<std::unique_ptr<InstrumentStrip>,7> strips;
};
}
