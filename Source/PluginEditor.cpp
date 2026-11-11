#include "PluginEditor.h"
#include "ui/LayoutGeometry.h"
SkellSilenceAudioProcessorEditor::SkellSilenceAudioProcessorEditor(SkellSilenceAudioProcessor& p)
  : AudioProcessorEditor(&p),processor(p),header(p),timeline(p),detection(p),rack(p),matrix(p),macros(p),quick(p) {
  setLookAndFeel(&look);
  header.setComponentID("header"); timeline.setComponentID("timeline");
  detection.setComponentID("detection"); rack.setComponentID("instruments");
  matrix.setComponentID("rules"); macros.setComponentID("dynamics");
  quick.setComponentID("simple-controls");
  std::array<juce::Component*,7> children{{&header,&timeline,&detection,&rack,&matrix,&macros,&quick}};
  for (auto* c : children) addAndMakeVisible(c);
  header.onModeChange=[this](bool advanced){setAdvancedMode(advanced);};
  header.onShowTutorial=[this]{showGuidedTour(false);};
  quick.setEditCallback([this]{setAdvancedMode(true);});
  constrainer.setSizeLimits(760,481,1800,1140);
  constrainer.setFixedAspectRatio(1200.0/760.0);
  setConstrainer(&constrainer);setResizable(true,true);
  header.onScaleChange=[this](float s){setSize(juce::roundToInt(1200*s),juce::roundToInt(760*s));};
  setAdvancedMode(false);
  setSize(juce::jlimit(760,1800,p.windowW.load()),juce::jlimit(481,1140,p.windowH.load()));
  showGuidedTour(true);
}
SkellSilenceAudioProcessorEditor::~SkellSilenceAudioProcessorEditor(){setLookAndFeel(nullptr);}
void SkellSilenceAudioProcessorEditor::showGuidedTour(bool firstRun){
  std::vector<skellcore::ui::GuidedTourStep> steps;
  steps.emplace_back(&timeline,"HEAR THE GAPS",
      "Play your song. The timeline shows the quiet gaps the detector finds.",
      [this]{setAdvancedMode(false);});
  steps.emplace_back(&quick,"START SIMPLE",
      "Shape the quiet moments using the few main controls.");
  steps.emplace_back(&header,"EXPLORE ADVANCED",
      "Use ADVANCED to reveal detailed detection, effects and timing settings.");
  steps.emplace_back(&detection,"GAP DETECTION",
      "Choose when a gap is detected and refine its response.",
      [this]{setAdvancedMode(true);});
  steps.emplace_back(&rack,"THE EFFECT RACK",
      "Choose which movement effects act on detected quiet moments.");
  steps.emplace_back(&matrix,"LENGTH RULES",
      "Different gap lengths can use different treatment rules.");
  steps.emplace_back(&macros,"ENERGY AND MOVEMENT",
      "Adjust global movement and intensity, then use SIMPLE VIEW to return.");
  guidedTour.setPalette({skell::ui::Theme::green,skell::ui::Theme::ink,
      skell::ui::Theme::text,skell::ui::Theme::muted,juce::Colour(0xd9000000)});
  guidedTour.setSteps(std::move(steps));
  if(firstRun)guidedTour.startIfFirstRun();
  else guidedTour.replay();
}

void SkellSilenceAudioProcessorEditor::setAdvancedMode(bool advanced){
  advancedMode=advanced;
  header.setAdvancedMode(advanced);
  detection.setVisible(advanced);rack.setVisible(advanced);
  matrix.setVisible(advanced);macros.setVisible(advanced);
  quick.setVisible(!advanced);
  resized();
  repaint();
}
void SkellSilenceAudioProcessorEditor::paint(juce::Graphics& g){
  const auto r=getLocalBounds().toFloat();
  g.setGradientFill(juce::ColourGradient(skell::ui::Theme::ink.brighter(0.14f),
    r.getCentreX(),0,skell::ui::Theme::ink.darker(0.24f),r.getCentreX(),r.getBottom(),false));
  g.fillAll();
  const float scale=float(getWidth())/1200.0f;
  g.setColour(skell::ui::Theme::green.withAlpha(0.34f));
  g.fillRect(0.0f,float(getHeight())-2.0f,105.0f*scale,2.0f);
}
void SkellSilenceAudioProcessorEditor::resized(){
  if(getWidth() <= 0) return;
  const float scale=float(getWidth())/1200.0f;
  auto place=[scale](juce::Component& c,int x,int y,int w,int h){
    c.setTransform(juce::AffineTransform());
    c.setBounds(x,y,w,h);
    c.setTransform(juce::AffineTransform::scale(scale));
  };
  place(header,0,0,1200,80);
  if(advancedMode){
    place(timeline,24,86,805,300);
    place(detection,24,402,805,145);
    place(rack,846,86,330,461);
    place(matrix,24,563,805,190);
    place(macros,846,563,330,190);
  } else {
    const auto timelineBounds=skell::ui::Layout::simplePanels[1];
    const auto quickBounds=skell::ui::Layout::simplePanels[2];
    place(timeline,timelineBounds.x,timelineBounds.y,timelineBounds.w,timelineBounds.h);
    place(quick,quickBounds.x,quickBounds.y,quickBounds.w,quickBounds.h);
  }
  processor.windowW.store(getWidth());processor.windowH.store(getHeight());
}
