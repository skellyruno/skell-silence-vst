#pragma once
#include "Theme.h"
#include "../PluginProcessor.h"
#include "../dsp/GapClass.h"
#include <array>
#include <algorithm>
namespace skell::ui {
class GapTimeline final : public juce::Component,private juce::Timer {
public:
 explicit GapTimeline(SkellSilenceAudioProcessor& p):processor(p) {
   preview.setButtonText("PREVIEW");preview.setComponentID("preview");
   preview.setTooltip("Select a recent gap, stop the transport, then audition its processing.");
   preview.onClick=[this]{if(selected>=0 && !processor.isPlaying.load())processor.requestPreview(selected);};
   preview.setEnabled(false);
   // Cache the UI's read-only automation pointers once. Repainting a stopped
   // timeline when a rule changes should not depend on the audio waveform.
   for(int ins=0;ins<7;++ins){
     const auto stem=juce::String(dsp::instrumentIds[size_t(ins)]);
     onParameters[size_t(ins)]=p.parameters.getRawParameterValue(stem+"On");
     levelParameters[size_t(ins)]=p.parameters.getRawParameterValue(stem+"Level");
     for(int cl=0;cl<4;++cl)
       ruleParameters[size_t(ins)][size_t(cl)]=p.parameters.getRawParameterValue("rule_"+stem+"_"+juce::String(cl));
   }
   constexpr const char* boundaryIds[]{"classShortMax","classMediumMax","classLongMax"};
   for(size_t i=0;i<3;++i)boundaryParameters[i]=p.parameters.getRawParameterValue(boundaryIds[i]);
   addAndMakeVisible(preview);setWantsKeyboardFocus(true);startTimerHz(30);
 }
 void paint(juce::Graphics& g) override {
   Theme::panelBackground(g,getLocalBounds().toFloat());Theme::title(g,"01  /  LIVE GAP SCOPE",{16,11,291,24});
   Theme::pill(g,{342.0f,14.0f,128.0f,23.0f},Theme::cyan,true);
   g.setColour(Theme::cyan);g.setFont(Theme::font(10.5f,true));
   g.drawText("8 SECOND BUFFER",350,14,119,23,juce::Justification::centredLeft);
   Theme::sectionRule(g,16.0f,46.0f,float(getWidth()-32),Theme::green);
   const auto inner=getLocalBounds().reduced(15).withTrimmedTop(50).withTrimmedBottom(32);
   const float x=float(inner.getX()),y=float(inner.getY()),width=float(inner.getWidth()),height=float(inner.getHeight());
   g.setGradientFill(juce::ColourGradient(Theme::inset.brighter(0.09f),x,y,
       Theme::inset.darker(0.15f),x+width,y+height,false));
   g.fillRoundedRectangle(inner.toFloat(),7);
   g.setColour(Theme::green.withAlpha(0.07f));
   g.fillRoundedRectangle(juce::Rectangle<float>(x,y+height*0.45f,width,height*0.10f),3.0f);
   g.setColour(Theme::border.withAlpha(0.65f));
   for(int j=1;j<=7;++j)g.drawVerticalLine(int(x+width*j/8),y,y+height);
   for(int j=1;j<=3;++j)g.drawHorizontalLine(int(y+height*j/4),x,x+width);
   auto const seq=processor.waveformSequence.load(std::memory_order_acquire);
   juce::Path wave;
   const float center=y+height*0.5f;
   for(int i=0;i<SkellSilenceAudioProcessor::waveformSize;++i) {
     const auto slot=size_t((seq+i)%SkellSilenceAudioProcessor::waveformSize);
     const auto amp=processor.waveform[slot].load(std::memory_order_acquire);
     const float wx=x+width*float(i)/float(SkellSilenceAudioProcessor::waveformSize-1);
     if(i==0)wave.startNewSubPath(wx,center-amp*height*0.42f);
     else wave.lineTo(wx,center-amp*height*0.42f);
   }
   // Use real telemetry; softly tint the area below the observed waveform.
   auto filledWave=wave;
   filledWave.lineTo(x+width,center);
   filledWave.lineTo(x,center);
   filledWave.closeSubPath();
   g.setGradientFill(juce::ColourGradient(Theme::green.withAlpha(0.19f),x,y,
       Theme::green.withAlpha(0.01f),x,y+height,false));
   g.fillPath(filledWave);
   g.setColour(Theme::green.withAlpha(0.32f));g.strokePath(wave,juce::PathStrokeType(3.2f));
   g.setColour(Theme::green.withAlpha(0.96f));g.strokePath(wave,juce::PathStrokeType(1.7f));
   juce::Path reflection;
   for(int i=0;i<SkellSilenceAudioProcessor::waveformSize;++i){
     const auto slot=size_t((seq+i)%SkellSilenceAudioProcessor::waveformSize);
     const auto amp=processor.waveform[slot].load(std::memory_order_acquire);
     const float wx=x+width*float(i)/float(SkellSilenceAudioProcessor::waveformSize-1);
     if(i==0)reflection.startNewSubPath(wx,center+amp*height*0.42f);
     else reflection.lineTo(wx,center+amp*height*0.42f);
   }
   g.setColour(Theme::cyan.withAlpha(0.58f));g.strokePath(reflection,juce::PathStrokeType(1.5f));
   g.setColour(Theme::border.brighter(0.12f));g.drawHorizontalLine(int(center),x+1,x+width-1);
   if(seq<12){
     g.setColour(Theme::muted.withAlpha(0.90f));g.setFont(Theme::font(12.0f,true));
     g.drawText("WAITING FOR AUDIO",inner.withTrimmedBottom(20),juce::Justification::centred);
     g.setColour(Theme::muted.withAlpha(0.60f));g.setFont(Theme::font(10.0f));
     g.drawText("PLAY YOUR TRACK TO MAP THE SILENCE",inner.withTrimmedTop(28),juce::Justification::centred);
   }
   const auto clock=processor.totalSamples.load();
   const auto sr=std::max(8000.0,processor.sampleRateAtomic.load());
   const auto bpm=processor.bpmAtomic.load();
   const auto nowPpq=processor.currentPpqAtomic.load();
   for(int i=processor.getRecentCount()-1;i>=0;--i){
     const auto e=processor.getRecentGap(i);
     if(e.end<=e.start)continue;
     const double ageEnd=(double(clock-e.end)/sr),ageStart=(double(clock-e.start)/sr);
     if(ageEnd>8.0||ageStart<0)continue;
     const float x1=x+width*float(std::clamp((8-ageStart)/8,0.0,1.0));
     const float x2=x+width*float(std::clamp((8-ageEnd)/8,0.0,1.0));
     g.setColour(Theme::violet.withAlpha(i==selected?0.30f:0.16f));
     g.fillRoundedRectangle(x1,y,std::max(2.0f,x2-x1),height,3.0f);
     g.setColour(Theme::violet.withAlpha(i==selected?0.9f:0.45f));
     g.drawVerticalLine(int(x1),y,y+height);
     if(i==selected)g.drawRoundedRectangle(x1+0.5f,y+0.5f,std::max(2.0f,x2-x1)-1.0f,height-1.0f,3.0f,1.0f);
     const auto duration=juce::String(1000.0*double(e.end-e.start)/sr,0)+" ms";
     g.setFont(Theme::font(10.0f));g.drawFittedText(duration,int(x1)+3,int(y)+8,std::max(20,int(x2-x1-6)),17,juce::Justification::centredLeft,1);
     // Reflect the actual enabled length rules, not three decorative curves.
     const int cl=dsp::classifyGapBeats(double(e.end-e.start)/sr*e.bpm/60.0,
                 boundaryParameters[0]->load(),boundaryParameters[1]->load(),boundaryParameters[2]->load());
     for(int ins=0;ins<7;++ins){
       const bool enabled=onParameters[size_t(ins)]->load()>0.5f;
       const bool rule=ruleParameters[size_t(ins)][size_t(cl)]->load()>0.5f;
       if(!enabled || !rule)continue;
       const float level=levelParameters[size_t(ins)]->load();
       const float baseline=y+height*(0.19f+float(ins)*0.095f);
       juce::Path envelope;
       for(int step=0;step<=18;++step){
         const float t=float(step)/18.0f;
         const float heightEnvelope=Theme::instrumentEnvelope(ins,t)*height*0.08f*level;
         const float ex=x1+(x2-x1)*t,ey=baseline-heightEnvelope;
         if(step==0)envelope.startNewSubPath(ex,ey);else envelope.lineTo(ex,ey);
       }
       g.setColour(Theme::instruments[size_t(ins)].withAlpha(i==selected?0.95f:0.68f));
       g.strokePath(envelope,juce::PathStrokeType(1.35f));
     }
   }
   // LEARN/LOCK markers follow project PPQ rather than unbounded sample time.
   for(int k=0;k<processor.gapMap.size();++k) {
     const auto item=processor.gapMap.get(k);
     const auto secsFrom=(nowPpq-item.from)*60.0/bpm;
     const auto secsTo=(nowPpq-item.to)*60.0/bpm;
     if(secsFrom<=0.0 || secsTo>=8.0 || secsFrom<secsTo)continue;
     const float gx1=x+width*float(std::clamp((8-secsFrom)/8.0,0.0,1.0));
     const float gx2=x+width*float(std::clamp((8-secsTo)/8.0,0.0,1.0));
     g.setColour(Theme::violet.withAlpha(k==selectedMap?0.95f:0.52f));
     g.drawRoundedRectangle(gx1,y+2,std::max(2.0f,gx2-gx1),height-4,3.0f,1.5f);
     g.setFont(Theme::font(9.0f,true));g.drawText("M",int(gx1)+3,int(y)+25,16,16,juce::Justification::centredLeft);
   }
   g.setColour(Theme::cyan.withAlpha(0.85f));g.drawVerticalLine(int(x+width-2),y,y+height);
   g.setColour(Theme::muted);g.setFont(Theme::font(11.0f));
   for(int i=0;i<=4;++i)g.drawText(juce::String(-8+i*2)+"s",int(x+width*i/4),int(y+height)+6,35,18,juce::Justification::centredLeft);
   g.setColour(Theme::green);g.setFont(Theme::font(12,true));
   g.drawText("BPM  "+juce::String(bpm,1),getWidth()-145,11,117,25,juce::Justification::centredRight);
   g.setColour(Theme::green);g.fillEllipse(18.0f,float(getHeight()-24),6.0f,6.0f);
   g.setColour(Theme::muted);g.setFont(Theme::font(10.0f));
   g.drawText("SIGNAL",31,getHeight()-30,78,19,juce::Justification::centredLeft);
   g.setColour(Theme::green);g.fillEllipse(101.0f,float(getHeight()-22),5.0f,5.0f);
   g.setColour(Theme::muted);g.drawText("DETECTED GAPS",113,getHeight()-30,155,19,juce::Justification::centredLeft);
   if(processor.gapMap.size()>0){g.setColour(Theme::violet);g.drawText("MAP  "+juce::String(processor.gapMap.size()),271,getHeight()-30,99,19,juce::Justification::centredLeft);}
   // Interactive gap inspector; never overlaps the footer preview button.
   g.setColour(selected>=0?Theme::green:Theme::muted);g.setFont(Theme::font(10,true));
   if(selected>=0){
     const auto item=processor.getRecentGap(selected);
     g.drawFittedText(item.end>item.start?"SELECTED  /  "+juce::String(1000.0*double(item.end-item.start)/sr,0)+" ms":"SELECT A GAP",
                       380,getHeight()-30,getWidth()-505,19,juce::Justification::centredLeft,1);
   }else g.drawFittedText("CLICK A GAP TO PREVIEW",380,getHeight()-30,getWidth()-505,19,juce::Justification::centredLeft,1);
 }
 // Select a real detector-recorded gap; also used by automated JUCE UI tests.
 void selectRecentGap(int index) {
   selected=index>=0 && index<processor.getRecentCount()?index:-1;
   selectedStart=selected>=0?processor.getRecentGap(selected).start:-1;
   preview.setEnabled(selected>=0 && !processor.isPlaying.load());
   repaint();
 }
 void resized() override {preview.setBounds(getWidth()-110,getHeight()-32,90,25);}
 void mouseDown(const juce::MouseEvent& e) override {
   const auto sr=std::max(8000.0,processor.sampleRateAtomic.load());
   const double age=8.0*(1.0-std::clamp((e.position.x-15.0f)/std::max(1.0f,float(getWidth()-30)),0.0f,1.0f));
   const auto clock=processor.totalSamples.load();selected=-1;selectedStart=-1;
   for(int i=0;i<processor.getRecentCount();++i){const auto gap=processor.getRecentGap(i);
     if(gap.start<=clock-int64_t(age*sr) && clock-int64_t(age*sr)<gap.end){selected=i;selectedStart=gap.start;break;}
   }
   const double bpm=processor.bpmAtomic.load();
   const double herePpq=processor.currentPpqAtomic.load()-age*bpm/60.0;
   selectedMap=-1;
   for(int j=0;j<processor.gapMap.size();++j){const auto mapped=processor.gapMap.get(j);
     if(herePpq>=mapped.from && herePpq<mapped.to){selectedMap=j;break;}
   }
   lastX=e.position.x;grabKeyboardFocus();repaint();
 }
 void mouseDrag(const juce::MouseEvent& e) override {
   if(selectedMap>=0 && selectedMap<processor.gapMap.size()) {
     const auto deltaSeconds=8.0*double(e.position.x-lastX)/std::max(1,getWidth()-30);
     const auto deltaPpq=deltaSeconds*processor.bpmAtomic.load()/60.0;
     if(std::abs(deltaPpq)>0.001)processor.requestMapEdit(selectedMap,deltaPpq);
   }
   // Each move is relative to the previous pointer position. Do not reapply
   // the entire drag distance at every mouse callback.
   lastX=e.position.x;
 }
 bool keyPressed(const juce::KeyPress& key) override {
   if(selectedMap>=0 && selectedMap<processor.gapMap.size()) {
     if(key==juce::KeyPress::deleteKey || key==juce::KeyPress::backspaceKey){processor.requestMapEdit(selectedMap,0,true);selectedMap=-1;return true;}
     if(key==juce::KeyPress::leftKey || key==juce::KeyPress::rightKey){processor.requestMapEdit(selectedMap,key==juce::KeyPress::leftKey?-0.01:0.01);return true;}
   }
   return false;
 }
private:
 void timerCallback() override {
   const bool playing=processor.isPlaying.load();
   const bool canPreview=selected>=0 && selected<processor.getRecentCount() && !playing;
   if(preview.isEnabled()!=canPreview)preview.setEnabled(canPreview);
   const auto sequence=processor.waveformSequence.load(std::memory_order_acquire);
   const auto gaps=processor.getRecentCount();
   const auto mapped=processor.gapMap.size();
   const auto ruleState=rulesFingerprint();
   if(selectedStart>=0 && gaps!=lastGapCount){
     selected=-1;
     for(int k=0;k<gaps;++k)
       if(processor.getRecentGap(k).start==selectedStart){selected=k;break;}
     if(selected<0)selectedStart=-1;
   }
   if(sequence!=lastSequence || gaps!=lastGapCount || mapped!=lastMapCount ||
      playing!=lastPlaying || ruleState!=lastRuleState){
     lastSequence=sequence;lastGapCount=gaps;lastMapCount=mapped;lastPlaying=playing;lastRuleState=ruleState;
     repaint();
   }
 }
 uint64_t rulesFingerprint() const noexcept {
   uint64_t digest=1469598103934665603ULL;
   const auto add=[&digest](float v) noexcept {
     digest^=uint64_t(std::lround(double(v)*1000.0));
     digest*=1099511628211ULL;
   };
   for(size_t i=0;i<7;++i){
     add(onParameters[i]->load());add(levelParameters[i]->load());
     for(size_t c=0;c<4;++c)add(ruleParameters[i][c]->load());
   }
   for(auto* p:boundaryParameters)add(p->load());
   return digest;
 }
 SkellSilenceAudioProcessor& processor;
 juce::TextButton preview;
 std::array<std::atomic<float>*,7> onParameters{},levelParameters{};
 std::array<std::array<std::atomic<float>*,4>,7> ruleParameters{};
 std::array<std::atomic<float>*,3> boundaryParameters{};
 int selected=-1,selectedMap=-1;int64_t selectedStart=-1;float lastX=0;
 uint64_t lastSequence=~uint64_t(0),lastRuleState=0;
 int lastGapCount=-1,lastMapCount=-1;bool lastPlaying=false;
};
}
