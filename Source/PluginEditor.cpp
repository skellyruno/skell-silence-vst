#include "PluginEditor.h"
#include "ui/LayoutGeometry.h"
SkellSilenceAudioProcessorEditor::SkellSilenceAudioProcessorEditor(SkellSilenceAudioProcessor& p)
  : AudioProcessorEditor(&p),processor(p),header(p),timeline(p),detection(p),rack(p),matrix(p),macros(p) {
  setLookAndFeel(&look);
  header.setComponentID("header"); timeline.setComponentID("timeline");
  detection.setComponentID("detection"); rack.setComponentID("instruments");
  matrix.setComponentID("rules"); macros.setComponentID("dynamics");
  addAndMakeVisible(header);addAndMakeVisible(timeline);addAndMakeVisible(detection);
  addAndMakeVisible(rack);addAndMakeVisible(matrix);addAndMakeVisible(macros);
  constrainer.setSizeLimits(760,481,1800,1140);
  constrainer.setFixedAspectRatio(1200.0/760.0);
  setConstrainer(&constrainer);setResizable(true,true);
  header.onScaleChange=[this](float s){setSize(juce::roundToInt(1200*s),juce::roundToInt(760*s));};
  setSize(juce::jlimit(760,1800,p.windowW.load()),juce::jlimit(481,1140,p.windowH.load()));
}
SkellSilenceAudioProcessorEditor::~SkellSilenceAudioProcessorEditor(){setLookAndFeel(nullptr);}
void SkellSilenceAudioProcessorEditor::paint(juce::Graphics& g){
  const auto r=getLocalBounds().toFloat();
  g.setGradientFill(juce::ColourGradient(skell::ui::Theme::ink.brighter(0.14f),
    r.getCentreX(),0,skell::ui::Theme::ink.darker(0.24f),r.getCentreX(),r.getBottom(),false));
  g.fillAll();
  const float scale=float(getWidth())/1200.0f;
  g.setColour(skell::ui::Theme::green.withAlpha(0.34f));
  g.fillRect(0.0f,float(getHeight())-2.0f,105.0f*scale,2.0f);
  g.setColour(skell::ui::Theme::violet.withAlpha(0.28f));
  g.fillRect(105.0f*scale,float(getHeight())-2.0f,66.0f*scale,2.0f);
}
void SkellSilenceAudioProcessorEditor::resized(){
  // IMPORTANT: transform child content AND its location once, in the same
  // 1200 x 760 coordinate system. The old code pre-scaled positions and then
  // transformed them again, causing panel overlap at reduced window sizes.
  const float scale=float(getWidth())/1200.0f;
  auto place=[scale](juce::Component& c,int x,int y,int w,int h){
    c.setTransform(juce::AffineTransform());
    c.setBounds(x,y,w,h);
    c.setTransform(juce::AffineTransform::scale(scale));
  };
  std::array<juce::Component*,6> components{{&header,&timeline,&detection,&rack,&matrix,&macros}};
  for(size_t i=0;i<components.size();++i){
    const auto r=skell::ui::Layout::panels[i];
    place(*components[i],r.x,r.y,r.w,r.h);
  }
  processor.windowW.store(getWidth());processor.windowH.store(getHeight());
}
