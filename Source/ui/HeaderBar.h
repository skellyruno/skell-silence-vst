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
    g.fillAll(Theme::ink);
    g.setColour(Theme::border);g.drawHorizontalLine(69,0,1200);
    g.setColour(Theme::green);g.fillRoundedRectangle(24.0f,19.0f,3.0f,30.0f,1.5f);
    g.setColour(Theme::text);g.setFont(Theme::font(25,true));
    g.drawText("SKELL",36,13,98,39,juce::Justification::centredLeft);
    g.setColour(Theme::violet);g.drawText("SILENCE",132,13,143,39,juce::Justification::centredLeft);
    g.setColour(Theme::muted);g.setFont(Theme::font(10,true));
    g.drawText("GAP DESIGNER  /  V1.6",282,18,146,29,juce::Justification::centredLeft);
    g.setColour(Theme::muted);g.setFont(Theme::font(10,true));
    g.drawText("WET MIX",905,22,61,25,juce::Justification::centredLeft);
    const bool running=processor.isPlaying.load();
    Theme::pill(g,{776.0f,22.0f,109.0f,25.0f},running?Theme::green:Theme::muted,running);
    g.setColour(running?Theme::green:Theme::muted);g.fillEllipse(786.0f,31.0f,6,6);
    g.setColour(Theme::text);g.setFont(Theme::font(10,true));
    const bool learning=processor.parameters.getRawParameterValue("learnArmed")->load()>0.5f;
    const bool locked=processor.parameters.getRawParameterValue("lockToMap")->load()>0.5f;
    g.drawText(learning?"LEARNING":locked?"MAP LOCK":running?"ANALYZING":"READY / IDLE",799,22,80,25,juce::Justification::centredLeft);
  }
  void resized() override {
    load.setBounds(447,20,69,29);save.setBounds(524,20,69,29);
    learn.setBounds(609,20,82,29);lock.setBounds(689,20,76,29);
    mix.setBounds(963,18,145,31);menu.setBounds(1113,20,70,29);
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
