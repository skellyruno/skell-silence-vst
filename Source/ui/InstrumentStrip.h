#pragma once
#include "Theme.h"
#include "WholePercentSlider.h"
#include "../PluginProcessor.h"
#include <memory>
#include <cstdint>
#include <atomic>
namespace skell::ui {
class InstrumentPopup final : public juce::Component {
public:
  InstrumentPopup(SkellSilenceAudioProcessor& p,int index)
    :instrumentTitle(skell::dsp::instrumentNames[size_t(index)]),
     accent(Theme::instruments[size_t(index)]) {
    const char* names[7][4] = {
      {"stopSpeedCurve","stopTime","stopLowpass",nullptr},
      {"airColor","airShape",nullptr,nullptr},
      {"swellLength","swellReverb",nullptr,nullptr},
      {"noiseType","noiseFadeIn","noiseFadeOut",nullptr},
      {"impactPitch","impactDecay","impactClick",nullptr},
      {"riserStart","riserCurve","riserNoiseMix",nullptr},
      {"stutterDiv","stutterDecay","stutterCount",nullptr}
    };
    for(const auto* id : names[index]) {
      if(id==nullptr) continue;
      auto* label=labels.emplace_back(std::make_unique<juce::Label>()).get();
      juce::String caption(id);
      // Human-readable parameter captions: "stopSpeedCurve" -> "STOP SPEED CURVE".
      for(int j=caption.length()-1;j>0;--j)
        if(caption[j]>='A' && caption[j]<='Z' &&
           caption[j-1]>='a' && caption[j-1]<='z')caption=caption.substring(0,j)+" "+caption.substring(j);
      label->setText(caption.replaceCharacter('_',' ').toUpperCase(),juce::dontSendNotification);
      const auto explanation=parameterHint(juce::String(id));
      label->setTooltip(explanation);
      hints.push_back(explanation);
      label->setColour(juce::Label::textColourId,Theme::text);addAndMakeVisible(*label);
      if(auto* choice=dynamic_cast<juce::AudioParameterChoice*>(p.parameters.getParameter(id))) {
        auto* combo=combos.emplace_back(std::make_unique<juce::ComboBox>()).get();
        combo->addItemList(choice->choices,1);
        combo->setTooltip(explanation);
        addAndMakeVisible(*combo);
        comboAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(p.parameters,id,*combo));
      } else {
        auto* slider=sliders.emplace_back(std::make_unique<WholeNumberSlider>()).get();
        // Show approachable whole-number values without changing APVTS ranges.
        const juce::String key(id);
        if(key=="stopTime" || key=="noiseFadeIn" || key=="noiseFadeOut")
          slider->setReadout(1000.0," ms");
        else if(key=="swellLength") slider->setReadout(1.0," ms");
        else if(key=="stutterCount") slider->setReadout(1.0);
        else slider->setReadout(100.0,"%");
        slider->setSliderStyle(juce::Slider::LinearHorizontal);
        slider->setTextBoxStyle(juce::Slider::TextBoxRight,false,60,24);
        if(auto* parameter=p.parameters.getParameter(id))
          slider->setDoubleClickReturnValue(true,parameter->convertFrom0to1(parameter->getDefaultValue()));
        slider->setTooltip(explanation);
        addAndMakeVisible(*slider);
        sliderAttachments.push_back(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(p.parameters,id,*slider));
      }
      types.push_back(dynamic_cast<juce::AudioParameterChoice*>(p.parameters.getParameter(id))!=nullptr);
    }
    setSize(360,int(72+types.size()*52));
  }
  void resized() override {
    int sliderIndex=0,comboIndex=0;
    for(size_t i=0;i<types.size();++i){
      const int y=58+int(i)*52;
      labels[i]->setBounds(17,y,151,27);
      if(types[i])combos[size_t(comboIndex++)]->setBounds(171,y,170,28);
      else sliders[size_t(sliderIndex++)]->setBounds(171,y,170,28);
    }
  }
  void paint(juce::Graphics& g) override {
    g.setGradientFill(juce::ColourGradient(Theme::raised,0,0,Theme::panel,
                                            float(getWidth()),float(getHeight()),false));
    g.fillAll();
    g.setColour(accent.withAlpha(0.08f));
    g.fillRoundedRectangle(12.0f,10.0f,float(getWidth()-24),35.0f,6.0f);
    g.setColour(accent);g.fillRoundedRectangle(15.0f,17.0f,4.0f,23.0f,2.0f);
    g.setColour(Theme::text);g.setFont(Theme::font(16,true));
    g.drawFittedText(instrumentTitle+"  /  SETTINGS",29,12,getWidth()-44,31,juce::Justification::centredLeft,1);
    g.setColour(Theme::border);g.drawHorizontalLine(47,15.0f,float(getWidth()-15));
    for(size_t i=0;i<types.size();++i) {
      g.setColour(Theme::muted);g.setFont(Theme::font(10.0f));
      g.drawFittedText(hints[i],17,85+int(i)*52,325,17,juce::Justification::centredLeft,1);
      if(i+1<types.size()){
        g.setColour(Theme::border);
        g.drawHorizontalLine(104+int(i)*52,15.0f,float(getWidth()-15));
      }
    }
  }
private:
  static juce::String parameterHint(const juce::String& id) {
    if(id=="stopSpeedCurve")return "Brake shape from smooth to aggressive";
    if(id=="stopTime")return "Time until the tape reaches zero speed";
    if(id=="stopLowpass")return "Tone rolloff as playback decelerates";
    if(id=="airColor")return "Match preceding sound or use pink / white";
    if(id=="airShape")return "Tilt the air spectrum darker or brighter";
    if(id=="swellLength")return "Reverse pre-gap audio into the next hit";
    if(id=="swellReverb")return "Reverb bloom on reverse material";
    if(id=="noiseType")return "Choose the texture filling quiet passages";
    if(id=="noiseFadeIn")return "Fade-in proportion of the gap";
    if(id=="noiseFadeOut")return "Fade-out proportion before the next hit";
    if(id=="impactPitch")return "Sub impact pitch / tonal weight";
    if(id=="impactDecay")return "Tail length of the impact";
    if(id=="impactClick")return "Transient snap at impact onset";
    if(id=="riserStart")return "Initial filter brightness";
    if(id=="riserCurve")return "Acceleration into the next hit";
    if(id=="riserNoiseMix")return "Blend filtered noise and pitched sweep";
    if(id=="stutterDiv")return "Slice duration synced to host tempo";
    if(id=="stutterDecay")return "Gain loss after every repeated slice";
    if(id=="stutterCount")return "Number of repeats in the gap";
    return "Drag to adjust; shift for fine control";
  }
  juce::String instrumentTitle;
  juce::Colour accent;
  std::vector<juce::String> hints;
  std::vector<std::unique_ptr<juce::Label>> labels;
  std::vector<std::unique_ptr<WholeNumberSlider>> sliders;
  std::vector<std::unique_ptr<juce::ComboBox>> combos;
  std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>> sliderAttachments;
  std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment>> comboAttachments;
  std::vector<bool> types;
};
class InstrumentStrip final : public juce::Component {
public:
  InstrumentStrip(SkellSilenceAudioProcessor& p,int i):processor(p),index(i),
    enableAttachment(p.parameters,juce::String(skell::dsp::instrumentIds[size_t(i)])+"On",enabled),
    levelAttachment(p.parameters,juce::String(skell::dsp::instrumentIds[size_t(i)])+"Level",level) {
    // Cache the four APVTS rule switches. The rack LEDs mirror the real
    // automation values; they are not decorative or duplicated state.
    for (int category=0; category<4; ++category)
      ruleParameters[size_t(category)] = p.parameters.getRawParameterValue(
        "rule_" + juce::String(skell::dsp::instrumentIds[size_t(i)]) + "_"
        + juce::String(category));
    enabled.setTooltip("Four bottom indicators: SHORT / MEDIUM / LONG / EXTRA LONG. "
               "Edit the rules in the performance matrix.");
    enabled.setComponentID("instrument-enable-"+juce::String(index));
    level.setComponentID("instrument-level-"+juce::String(index));
    enabled.setButtonText(juce::String(skell::dsp::instrumentNames[size_t(i)]));
    enabled.setColour(juce::ToggleButton::tickColourId,Theme::instruments[size_t(index)]);
    level.setSliderStyle(juce::Slider::LinearHorizontal);
    level.setTextBoxStyle(juce::Slider::NoTextBox,false,0,0);
    level.setColour(juce::Slider::trackColourId,Theme::instruments[size_t(index)]);
    level.setTooltip("Instrument output level. Shift-drag for fine adjustment; double-click to reset.");
    level.setDoubleClickReturnValue(true,0.6);
    level.onValueChange=[this]{repaint(157,34,77,21);};
    settings.setButtonText("...");settings.setTooltip("Open detailed settings for "+juce::String(skell::dsp::instrumentNames[size_t(index)]));
    settings.setComponentID("instrument-settings-"+juce::String(index));
    settings.onClick=[this]{
      auto* editor=findParentComponentOfClass<juce::AudioProcessorEditor>();
      juce::CallOutBox::launchAsynchronously(
        std::make_unique<InstrumentPopup>(processor,index),settings.getScreenBounds(),editor);
    };
    addAndMakeVisible(enabled);addAndMakeVisible(level);addAndMakeVisible(settings);
  }
  // Cheap UI-side fingerprint: only redraw a strip when its rule/level state
  // or the DSP active category changes. No polling of this data on the audio thread.
  std::uint32_t settingsFingerprint() const noexcept {
    std::uint32_t result = enabled.getToggleState() ? 0x10u : 0u;
    for(size_t c=0;c<4;++c)
      if(ruleParameters[c]!=nullptr && ruleParameters[c]->load(std::memory_order_relaxed)>0.5f)
        result |= (1u << c);
    return result | (std::uint32_t(juce::roundToInt(level.getValue()*100.0)) << 8u);
  }
  void paint(juce::Graphics& g) override {
    const bool playing=(processor.activeMask.load(std::memory_order_relaxed)&(1<<index))!=0;
    const bool on=enabled.getToggleState();
    const auto c=Theme::instruments[size_t(index)];
    const auto row=getLocalBounds().toFloat().reduced(2.0f,2.0f);
    g.setGradientFill(juce::ColourGradient(playing?c.withAlpha(0.22f):
        on?Theme::raised.withAlpha(0.74f):Theme::inset.withAlpha(0.45f),
        0.0f,row.getY(),Theme::panel.withAlpha(0.34f),float(getWidth()),row.getBottom(),false));
    g.fillRoundedRectangle(row,7.0f);
    if(playing){g.setColour(c.withAlpha(0.65f));g.drawRoundedRectangle(row.reduced(0.5f),7.0f,1.0f);}
    g.setColour(on?c:Theme::border);
    g.fillRoundedRectangle(4.0f,9.0f,3.0f,40.0f,1.5f);
    g.setColour(on?c.withAlpha(0.19f):Theme::inset);
    g.fillEllipse(11.0f,17.0f,25.0f,25.0f);
    g.setColour(on?c:Theme::muted);g.setFont(Theme::font(11,true));
    g.drawText(juce::String(index+1).paddedLeft('0',2),11,18,25,23,juce::Justification::centred);
    // Individual waveform accent, rather than an identical decorative meter per row.
    const auto graph=juce::Rectangle<float>(float(getWidth()-101),12.0f,65.0f,31.0f);
    g.setColour(Theme::inset.withAlpha(0.68f));g.fillRoundedRectangle(graph,4.0f);
    g.setColour(Theme::border.withAlpha(0.7f));g.drawHorizontalLine(int(graph.getCentreY()),graph.getX()+4,graph.getRight()-4);
    juce::Path env;
    for(int step=0;step<=28;++step){
       const float t=float(step)/28.0f;
       const float ey=graph.getBottom()-5.0f-20.0f*Theme::instrumentEnvelope(index,t);
       const float ex=graph.getX()+4.0f+(graph.getWidth()-8.0f)*t;
       if(step==0)env.startNewSubPath(ex,ey);else env.lineTo(ex,ey);
    }
    g.setColour(on?c.withAlpha(playing?1.0f:0.82f):Theme::border);
    g.strokePath(env,juce::PathStrokeType(playing?2.4f:1.6f,juce::PathStrokeType::curved));
    if(playing){g.setColour(c);g.fillEllipse(graph.getX()-6.0f,graph.getCentreY()-2.5f,5,5);}
    g.setColour(on?Theme::text:Theme::muted);g.setFont(Theme::font(11.5f,true));
    g.drawText(juce::String(juce::roundToInt(level.getValue()*100.0))+"%",151,36,53,15,juce::Justification::centred);
    // Compact four-step rule strip under the actual effect envelope.
    // Highlight the length currently selected by the audio engine.
    const int selected=processor.activeLengthClass.load(std::memory_order_relaxed);
    for(int category=0;category<4;++category){
      const bool assigned=ruleParameters[size_t(category)] != nullptr
        && ruleParameters[size_t(category)]->load(std::memory_order_relaxed)>0.5f;
      const auto marker=juce::Rectangle<float>(graph.getX()+4.0f+category*15.0f,46.0f,11.0f,4.0f);
      g.setColour(on && assigned ? c.withAlpha(selected==category && playing?1.0f:0.72f)
                                 : Theme::border.withAlpha(0.42f));
      g.fillRoundedRectangle(marker,1.3f);
      if(on && assigned && selected==category && playing){
        g.setColour(Theme::text.withAlpha(0.7f));
        g.drawRoundedRectangle(marker.expanded(1.0f),2.0f,0.8f);
      }
    }
  }
  void resized() override {
    enabled.setBounds(35,8,113,40);
    level.setBounds(151,11,53,27);
    settings.setBounds(getWidth()-30,16,25,26);
  }

private:
  SkellSilenceAudioProcessor& processor;int index;
  std::array<std::atomic<float>*,4> ruleParameters{};
  juce::ToggleButton enabled;
  juce::Slider level;
  juce::TextButton settings;
  juce::AudioProcessorValueTreeState::ButtonAttachment enableAttachment;
  juce::AudioProcessorValueTreeState::SliderAttachment levelAttachment;
};
}
