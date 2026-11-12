#pragma once
#include "Theme.h"
#include <SkellCore/SkellHardwareUI.h>
#include "../PluginProcessor.h"
#include <functional>
#include <memory>

namespace skell::ui {
// Always-small header. Advanced controls and preset file operations are
// intentionally progressive disclosures, not part of the first-run surface.
class HeaderBar final : public juce::Component, private juce::Timer {
public:
  explicit HeaderBar(SkellSilenceAudioProcessor& p)
    : processor(p),learnAttachment(p.parameters,"learnArmed",learn),
      lockAttachment(p.parameters,"lockToMap",lock) {
    learn.setButtonText("CAPTURE GAPS");
    lock.setButtonText("REPLAY MAP");
    learn.setComponentID("learn");lock.setComponentID("lock");
    learn.setTooltip("Advanced: remember where gaps occur on the song timeline. Activate while the song plays.");
    lock.setTooltip("Advanced: play the remembered gaps at the same song positions. Requires a captured map.");
    presets.setButtonText("PRESETS");
    presets.setComponentID("menu");
    presets.setTooltip("Open, save or manage sound presets and window size.");
    toggleMode.setButtonText("ADVANCED");
    toggleMode.setComponentID("toggle-advanced");
    toggleMode.setTooltip("Show detailed effect, detector and timing controls.");
    presets.onClick=[this]{showWorkspaceMenu();};
    toggleMode.onClick=[this]{if(onModeChange)onModeChange(!advancedMode);};
    addAndMakeVisible(presets);addAndMakeVisible(toggleMode);
    addAndMakeVisible(learn);addAndMakeVisible(lock);
    setAdvancedMode(false);
    startTimerHz(6);
  }
  std::function<void(float)> onScaleChange;
  std::function<void(bool)> onModeChange;
  void setAdvancedMode(bool advanced) {
    advancedMode=advanced;
    learn.setVisible(advanced);
    lock.setVisible(advanced);
    toggleMode.setButtonText(advanced?"SIMPLE VIEW":"ADVANCED");
    toggleMode.setTooltip(advanced?"Return to the easy three-control view.":"Show every sound-design and timing control.");
    repaint();
  }
  void paint(juce::Graphics& g) override {
    const auto r=getLocalBounds().toFloat();
    g.setGradientFill(juce::ColourGradient(Theme::panel.darker(0.28f),0,0,Theme::ink,0,r.getBottom(),false));
    g.fillRect(r);
    g.setColour(Theme::border.withAlpha(0.75f));g.drawHorizontalLine(76,0.0f,1200.0f);
    drawSkull(g);
    // The name is set as one tight lockup. No large arbitrary gap before SILENCE.
    g.setFont(Theme::font(29,true));
    g.setColour(Theme::text);g.drawText("SKELL",94,11,100,36,juce::Justification::centredLeft);
    g.setColour(Theme::green);g.drawText("SILENCE",187,11,153,36,juce::Justification::centredLeft);
    g.setColour(Theme::muted);g.setFont(Theme::font(13));
    g.drawText("GAP DESIGNER  /  SKELLCORE",95,47,360,20,juce::Justification::centredLeft);
    const bool playing=processor.isPlaying.load(std::memory_order_relaxed);
    const bool locked=processor.parameters.getRawParameterValue("lockToMap")->load()>0.5f;
    const bool learning=processor.parameters.getRawParameterValue("learnArmed")->load()>0.5f;
    const juce::String status=locked?"REPLAYING MAP":learning?"CAPTURING GAPS":
                              playing?"LISTENING FOR GAPS":"READY  /  PRESS PLAY";
    const auto color=locked?Theme::violet:playing?Theme::green:Theme::muted;
    const int px=advancedMode?482:685;
    Theme::pill(g,{float(px),22.0f,232.0f,35.0f},color,playing||locked);
    g.setColour(color);g.fillEllipse(float(px+13),36.0f,7.0f,7.0f);
    g.setFont(Theme::font(13,true));g.setColour(Theme::text);
    g.drawFittedText(status,px+27,24,198,31,juce::Justification::centredLeft,1);
  }
  void resized() override {
    learn.setBounds(724,22,120,34);
    lock.setBounds(849,22,112,34);
    presets.setBounds(970,22,99,34);
    toggleMode.setBounds(1077,22,103,34);
  }
private:
  void drawSkull(juce::Graphics& g) const {
    const juce::Rectangle<float> tile{22.0f,13.0f,56.0f,53.0f};
    g.setColour(Theme::raised.darker(0.18f));g.fillRoundedRectangle(tile,11.0f);
    g.setColour(Theme::green.withAlpha(0.67f));
    g.drawRoundedRectangle(tile.reduced(0.65f),10.5f,1.35f);
    skellcore::ui::drawShushingSkullMark(g,26.0f,16.0f,47.0f,
                                         Theme::text,Theme::inset,Theme::green);
  }
  void timerCallback() override {repaint(465,14,485,54);}
  void showWorkspaceMenu() {
    juce::PopupMenu menu;
    menu.addSectionHeader("SOUND PRESETS");
    menu.addItem(20,"Open preset...");
    menu.addItem(21,"Save current sound...");
    menu.addSeparator();
    menu.addSectionHeader("ADVANCED GAP CAPTURE");
    menu.addItem(1,"Clear captured gap map");
    menu.addSeparator();
    menu.addSectionHeader("WINDOW SIZE");
    menu.addItem(2,"Compact (76%)");menu.addItem(3,"90%");
    menu.addItem(4,"100%");menu.addItem(5,"125%");
    menu.addSeparator();
    menu.addItem(6,"About Skell Silence");
    juce::Component::SafePointer<HeaderBar> safe(this);
    menu.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(&presets)
        .withParentComponent(findParentComponentOfClass<juce::AudioProcessorEditor>()),
      [safe](int result) {
        if(safe==nullptr)return;
        if(result==1)safe->processor.requestClearMap();
        if(result>=2 && result<=5 && safe->onScaleChange){
          constexpr float scales[]{0.76f,0.90f,1.0f,1.25f};
          safe->onScaleChange(scales[result-2]);
        }
        if(result==20 || result==21)safe->openPreset(result==21);
        if(result==6)juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::InfoIcon,
          "Skell Silence", "Play audio to detect quiet gaps. Use Mix, Energy and Space to shape them.\nAdvanced reveals capture, replay, timing and individual effects.");
      });
  }
  void openPreset(bool save) {
    chooser=std::make_unique<juce::FileChooser>(save?"Save Skell Silence preset":"Open Skell Silence preset",
                                                juce::File{},"*.skellsilence");
    const int flags=save?(juce::FileBrowserComponent::saveMode|juce::FileBrowserComponent::canSelectFiles)
                        :(juce::FileBrowserComponent::openMode|juce::FileBrowserComponent::canSelectFiles);
    chooser->launchAsync(flags,[safe=juce::Component::SafePointer<HeaderBar>(this),save](const juce::FileChooser& dialog){
      if(safe==nullptr)return;
      const auto file=dialog.getResult();if(file==juce::File{})return;
      if(save){
        juce::MemoryBlock data;safe->processor.getStateInformation(data);
        file.replaceWithData(data.getData(),data.getSize());
      } else {
        juce::MemoryBlock data;
        if(file.loadFileAsData(data))safe->processor.setStateInformation(data.getData(),int(data.getSize()));
      }
    });
  }
  SkellSilenceAudioProcessor& processor;
  bool advancedMode=false;
  juce::ToggleButton learn,lock;
  juce::TextButton presets,toggleMode;
  juce::AudioProcessorValueTreeState::ButtonAttachment learnAttachment,lockAttachment;
  std::unique_ptr<juce::FileChooser> chooser;
};
}
