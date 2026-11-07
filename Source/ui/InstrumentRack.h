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
 void paint(juce::Graphics& g) override {Theme::panelBackground(g,getLocalBounds().toFloat());Theme::title(g,"GAP INSTRUMENTS",{14,8,getWidth()-30,22});}
 void resized() override {const int top=35;const int room=getHeight()-top-10;
   for(int i=0;i<7;++i)strips[size_t(i)]->setBounds(8,top+i*room/7,getWidth()-16,room/7);
 }
private:std::array<std::unique_ptr<InstrumentStrip>,7> strips;
};
}
