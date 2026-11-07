#include "PluginEditor.h"
SkellSilenceAudioProcessorEditor::SkellSilenceAudioProcessorEditor(SkellSilenceAudioProcessor& p)
 : AudioProcessorEditor(&p),processor(p),header(p),timeline(p),detection(p),rack(p),matrix(p),macros(p) {
  setLookAndFeel(&look);
  addAndMakeVisible(header);addAndMakeVisible(timeline);addAndMakeVisible(detection);
  addAndMakeVisible(rack);addAndMakeVisible(matrix);addAndMakeVisible(macros);
  constrainer.setSizeLimits(720,456,2400,1520);
  constrainer.setFixedAspectRatio(1200.0/760.0);
  setConstrainer(&constrainer);setResizable(true,true);
  header.onScaleChange=[this](float s){setSize(juce::roundToInt(1200*s),juce::roundToInt(760*s));};
  setSize(p.windowW.load(),p.windowH.load());
}
SkellSilenceAudioProcessorEditor::~SkellSilenceAudioProcessorEditor() {
  setLookAndFeel(nullptr);
}
void SkellSilenceAudioProcessorEditor::paint(juce::Graphics& g) {
  g.fillAll(skell::ui::Theme::ink);
  g.setColour(skell::ui::Theme::violet.withAlpha(0.08f));
  g.fillRect(getLocalBounds().withTrimmedTop(getHeight()-3));
}
void SkellSilenceAudioProcessorEditor::resized() {
  // Keep all controls, hit targets, labels, and strokes in 1200x760 design space.
  // Scaling only component bounds previously left fonts & child hit targets unscaled.
  const float scale=float(getWidth())/1200.0f;
  auto place=[scale](juce::Component& c,int x,int y,int w,int h){
    c.setBounds(juce::roundToInt(x*scale),juce::roundToInt(y*scale),w,h);
    c.setTransform(juce::AffineTransform::scale(scale));
  };
  place(header,0,0,1200,64);
  place(timeline,30,84,800,316);
  place(detection,30,420,800,140);
  place(rack,850,84,320,476);
  place(matrix,30,580,800,160);
  place(macros,850,580,320,160);
  processor.windowW.store(getWidth());processor.windowH.store(getHeight());
}
