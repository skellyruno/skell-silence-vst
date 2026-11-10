#pragma once
#include "Theme.h"
#include "../PluginProcessor.h"
#include <memory>
#include <functional>
namespace skell::ui {
class HeaderBar final : public juce::Component,private juce::Timer {
public:
  explicit HeaderBar(SkellSilenceAudioProcessor& p)
   :processor(p),learnAttachment(p.parameters,"learnArmed",learn),
    lockAttachment(p.parameters,"lockToMap",lock),mixAttachment(p.parameters,"mix",mix) {
    learn.setButtonText("LEARN"); lock.setButtonText("LOCK");
    learn.setTooltip("Capture detected gaps at project beat positions while the song plays.");
    lock.setTooltip("Trigger from the learned gap map for repeatable playback and bounces.");
    mix.setComponentID("mix");mix.setSliderStyle(juce::Slider::LinearHorizontal);
    mix.setTextBoxStyle(juce::Slider::TextBoxRight,false,55,24);
    mix.setTooltip("Wet effect blend. At 0%, the delayed dry signal is preserved.");
    load.setButtonText("LOAD");save.setButtonText("SAVE");menu.setButtonText("MENU");
    load.setComponentID("preset-load"); save.setComponentID("preset-save"); menu.setComponentID("menu");
    load.onClick=[this]{openPreset(false);};save.onClick=[this]{openPreset(true);};
    menu.onClick=[this]{
      juce::PopupMenu popup;
      popup.addSectionHeader("WORKSPACE");
      popup.addItem(1,"Clear learned gap map");popup.addSeparator();
      popup.addSectionHeader("INTERFACE SIZE");
      popup.addItem(2,"Compact / 76%");popup.addItem(3,"90%");popup.addItem(4,"100%");popup.addItem(5,"125%");
      popup.addSeparator();popup.addItem(6,"About Skell Silence");
      juce::Component::SafePointer<HeaderBar> safeThis(this);
      popup.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(&menu)
        .withParentComponent(findParentComponentOfClass<juce::AudioProcessorEditor>()),
        [safe=safeThis](int result){
        if(safe==nullptr)return;
        if(result==1)safe->processor.requestClearMap();
        if(result>=2&&result<=5&&safe->onScaleChange){const float sizes[]{0.76f,0.9f,1.0f,1.25f};safe->onScaleChange(sizes[result-2]);}
        if(result==6)juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon,"Skell Silence","Gap-aware effect designer | Skell Audio\nSeven instruments | beat-synced rules | LEARN / LOCK");
      });
    };
    for(auto* b:{&load,&save,&menu})addAndMakeVisible(*b);
    addAndMakeVisible(learn);addAndMakeVisible(lock);addAndMakeVisible(mix);
    startTimerHz(6);
  }
  std::function<void(float)> onScaleChange;
  void paint(juce::Graphics& g) override {
    const auto r=getLocalBounds().toFloat();
    g.setGradientFill(juce::ColourGradient(Theme::ink.brighter(0.22f),0,0,
                                          Theme::ink,0,r.getBottom(),false));
    g.fillRect(r);
    g.setColour(Theme::border.withAlpha(0.67f));g.drawHorizontalLine(69,0.0f,1200.0f);
    // Draw the Skell identity as lightweight vector art, not a bitmap or mockup.
    g.setColour(Theme::green.withAlpha(0.11f));g.fillRoundedRectangle(19.0f,14.0f,40.0f,41.0f,9.0f);
    g.setColour(Theme::green.withAlpha(0.72f));g.drawRoundedRectangle(20.0f,15.0f,38.0f,39.0f,9.0f,1.4f);
    g.setColour(Theme::green);g.fillRoundedRectangle(27.0f,21.0f,25.0f,23.0f,9.0f);
    g.fillRoundedRectangle(32.0f,39.0f,15.0f,10.0f,3.0f);
    g.setColour(Theme::ink);g.fillEllipse(32.0f,30.0f,6.5f,6.5f);g.fillEllipse(41.0f,30.0f,6.5f,6.5f);
    g.fillEllipse(38.0f,37.0f,4.0f,4.0f);
    g.setColour(Theme::ink.withAlpha(0.8f));
    g.drawVerticalLine(37,43.0f,47.0f);g.drawVerticalLine(42,43.0f,47.0f);
    g.setFont(Theme::font(27,true));g.setColour(Theme::text);
    g.drawText("SKELL",66,11,104,40,juce::Justification::centredLeft);
    g.setColour(Theme::violet);g.drawText("SILENCE",177,11,130,40,juce::Justification::centredLeft);
    g.setFont(Theme::font(11,true));g.setColour(Theme::muted);
    g.drawText("GAP DESIGN ENGINE",311,15,139,15,juce::Justification::centredLeft);
    g.setColour(Theme::green.withAlpha(0.70f));g.fillRoundedRectangle(311.0f,36.0f,29.0f,2.0f,1.0f);
    g.setColour(Theme::muted);g.setFont(Theme::font(9.5f,true));
    g.drawText("V1.8 / STEREO FX",346,28,100,20,juce::Justification::centredLeft);
    const bool running=processor.isPlaying.load();
    Theme::pill(g,{772.0f,20.0f,122.0f,30.0f},running?Theme::green:Theme::muted,running);
    g.setColour(running?Theme::green:Theme::muted);g.fillEllipse(784.0f,32.0f,7,7);
    g.setColour(Theme::text);g.setFont(Theme::font(11,true));
    const bool learning=processor.parameters.getRawParameterValue("learnArmed")->load()>0.5f;
    const bool locked=processor.parameters.getRawParameterValue("lockToMap")->load()>0.5f;
    g.drawText(learning?"LEARNING":locked?"MAP LOCK":running?"ANALYZING":"READY / IDLE",799,20,94,30,juce::Justification::centredLeft);
    g.setColour(Theme::muted);g.setFont(Theme::font(11,true));
    g.drawText("MIX",906,20,53,30,juce::Justification::centredLeft);
  }
  void resized() override {
    load.setBounds(459,19,69,32);save.setBounds(534,19,69,32);
    learn.setBounds(615,19,80,32);lock.setBounds(698,19,74,32);
    mix.setBounds(961,18,145,34);menu.setBounds(1112,19,70,32);
  }
private:
  void timerCallback() override {repaint(770,17,121,35);}
  void openPreset(bool doSave){
    chooser=std::make_unique<juce::FileChooser>(doSave?"Save Skell Silence preset":"Open Skell Silence preset",juce::File{},"*.skellsilence");
    const int flags=doSave?(juce::FileBrowserComponent::saveMode|juce::FileBrowserComponent::canSelectFiles):
                            (juce::FileBrowserComponent::openMode|juce::FileBrowserComponent::canSelectFiles);
    chooser->launchAsync(flags,[safe=juce::Component::SafePointer<HeaderBar>(this),doSave](const juce::FileChooser& dialog){
      if(safe==nullptr)return;const auto file=dialog.getResult();if(file==juce::File{})return;
      if(doSave){juce::MemoryBlock data;safe->processor.getStateInformation(data);file.replaceWithData(data.getData(),data.getSize());}
      else {juce::MemoryBlock data;if(file.loadFileAsData(data))safe->processor.setStateInformation(data.getData(),int(data.getSize()));}
    });
  }
  SkellSilenceAudioProcessor& processor;
  juce::ToggleButton learn,lock;
  juce::Slider mix;
  juce::TextButton load,save,menu;
  juce::AudioProcessorValueTreeState::ButtonAttachment learnAttachment,lockAttachment;
  juce::AudioProcessorValueTreeState::SliderAttachment mixAttachment;
  std::unique_ptr<juce::FileChooser> chooser;
};
}
