#pragma once
#include "Theme.h"
#include "../PluginProcessor.h"
#include <memory>
#include <functional>
namespace skell::ui {
class HeaderBar final : public juce::Component {
public:
  explicit HeaderBar(SkellSilenceAudioProcessor& p):processor(p),learnAttachment(p.parameters,"learnArmed",learn),lockAttachment(p.parameters,"lockToMap",lock),mixAttachment(p.parameters,"mix",mix) {
    learn.setButtonText("LEARN");lock.setButtonText("LOCK");
    learn.setColour(juce::ToggleButton::tickColourId,Theme::violet);
    lock.setColour(juce::ToggleButton::tickColourId,Theme::amber);
    mix.setSliderStyle(juce::Slider::LinearHorizontal);mix.setTextBoxStyle(juce::Slider::TextBoxRight,false,48,22);
    load.setButtonText("LOAD");save.setButtonText("SAVE");menu.setButtonText("MENU");
    load.onClick=[this]{openPreset(false);};save.onClick=[this]{openPreset(true);};
    menu.onClick=[this]{
      juce::PopupMenu popup;
      popup.addItem(1,"Reset learned gaps");popup.addSeparator();
      popup.addItem(2,"UI 80%");popup.addItem(3,"UI 100%");popup.addItem(4,"UI 125%");popup.addSeparator();
      popup.addItem(5,"About Skell Silence");
      juce::Component::SafePointer<HeaderBar> safeThis(this);
      popup.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(&menu),[safe=safeThis](int result){
        if(safe==nullptr)return;
        if(result==1)safe->processor.requestClearMap();
        if(result>=2&&result<=4 && safe->onScaleChange)safe->onScaleChange(result==2?0.8f:result==3?1.0f:1.25f);
        if(result==5)juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon,"Skell Silence","Gap-aware effects designer. Skell Audio | Version 1.0");
      });
    };
    addAndMakeVisible(learn);addAndMakeVisible(lock);addAndMakeVisible(mix);
    addAndMakeVisible(load);addAndMakeVisible(save);addAndMakeVisible(menu);
  }
  std::function<void(float)> onScaleChange;
  void paint(juce::Graphics& g) override {
    g.setColour(Theme::ink);g.fillAll();
    g.setColour(Theme::border);g.drawHorizontalLine(63,0.0f,1200.0f);
    g.setColour(Theme::text);g.setFont(Theme::font(24.0f,true));g.drawText("SKELL",30,12,104,33,juce::Justification::centredLeft);
    g.setColour(Theme::violet);g.drawText("SILENCE",114,12,146,33,juce::Justification::centredLeft);
    g.setColour(Theme::muted);g.setFont(Theme::font(10.0f));g.drawText("GAP EFFECT DESIGNER",270,21,155,24,juce::Justification::centredLeft);
    g.setColour(Theme::muted);g.drawText("MIX",932,20,33,25,juce::Justification::centredLeft);
  }
  void resized() override {
    const auto set=[](juce::Component& c,int x,int y,int w,int h){c.setBounds(x,y,w,h);};
    set(load,430,17,63,27);set(save,500,17,63,27);
    set(learn,593,17,92,27);set(lock,687,17,77,27);
    set(mix,964,16,132,27);set(menu,1102,17,80,27);
  }
private:
  void openPreset(bool doSave){
    chooser=std::make_unique<juce::FileChooser>(doSave?"Save Skell Silence preset":"Open Skell Silence preset",juce::File{},"*.skellsilence");
    const int flags=doSave?(juce::FileBrowserComponent::saveMode|juce::FileBrowserComponent::canSelectFiles):
                            (juce::FileBrowserComponent::openMode|juce::FileBrowserComponent::canSelectFiles);
    chooser->launchAsync(flags,[safe=juce::Component::SafePointer<HeaderBar>(this),doSave](const juce::FileChooser& dialog){
      if(safe==nullptr)return;
      const auto file=dialog.getResult();if(file==juce::File{})return;
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
