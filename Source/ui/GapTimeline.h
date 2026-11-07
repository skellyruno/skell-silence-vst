#pragma once
#include "Theme.h"
#include "../PluginProcessor.h"
#include <array>
#include <algorithm>
namespace skell::ui {
class GapTimeline final : public juce::Component,private juce::Timer {
public:
 explicit GapTimeline(SkellSilenceAudioProcessor& p):processor(p) {
   preview.setButtonText("PREVIEW");
   preview.onClick=[this]{processor.requestPreview(std::max(0,selected));};
   addAndMakeVisible(preview);setWantsKeyboardFocus(true);startTimerHz(30);
 }
 void paint(juce::Graphics& g) override {
   Theme::panelBackground(g,getLocalBounds().toFloat());Theme::title(g,"GAP TIMELINE  /  LAST 8 SEC",{16,12,260,22});
   const auto inner=getLocalBounds().reduced(15).withTrimmedTop(50).withTrimmedBottom(32);
   const float x=float(inner.getX()),y=float(inner.getY()),width=float(inner.getWidth()),height=float(inner.getHeight());
   g.setColour(juce::Colour(0xff0a0f15));g.fillRoundedRectangle(inner.toFloat(),5);
   g.setColour(Theme::border);
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
   g.setColour(Theme::cyan.withAlpha(0.8f));g.strokePath(wave,juce::PathStrokeType(1.4f));
   juce::Path reflection;
   for(int i=0;i<SkellSilenceAudioProcessor::waveformSize;++i){
     const auto slot=size_t((seq+i)%SkellSilenceAudioProcessor::waveformSize);
     const auto amp=processor.waveform[slot].load(std::memory_order_acquire);
     const float wx=x+width*float(i)/float(SkellSilenceAudioProcessor::waveformSize-1);
     if(i==0)reflection.startNewSubPath(wx,center+amp*height*0.42f);
     else reflection.lineTo(wx,center+amp*height*0.42f);
   }
   g.setColour(Theme::cyan.withAlpha(0.35f));g.strokePath(reflection,juce::PathStrokeType(1.2f));
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
     const auto duration=juce::String(1000.0*double(e.end-e.start)/sr,0)+" ms";
     g.setFont(Theme::font(10.0f));g.drawFittedText(duration,int(x1)+3,int(y)+8,std::max(20,int(x2-x1-6)),17,juce::Justification::centredLeft,1);
     for(int layer=0;layer<3;++layer){
       juce::Path curve;
       for(int step=0;step<12;++step){
         const float t=float(step)/11.0f;
         const float yy=y+height*(0.73f+layer*0.07f)-std::sin(t*3.14159f)*height*(0.06f+0.035f*layer);
         if(step==0)curve.startNewSubPath(x1,yy);else curve.lineTo(x1+(x2-x1)*t,yy);
       }
       g.setColour((layer==0?Theme::cyan:layer==1?Theme::amber:Theme::violet).withAlpha(0.65f));
       g.strokePath(curve,juce::PathStrokeType(1.25f));
     }
   }
   // LEARN/LOCK markers follow project PPQ rather than unbounded sample time.
   for(int k=0;k<processor.gapMap.size();++k) {
     const auto item=processor.gapMap.get(k);
     const auto secsFrom=(nowPpq-item.from)*60.0/bpm;
     const auto secsTo=(nowPpq-item.to)*60.0/bpm;
     if(secsFrom<0||secsTo>8.0) continue;
     const float gx1=x+width*float(std::clamp((8-secsFrom)/8.0,0.0,1.0));
     const float gx2=x+width*float(std::clamp((8-secsTo)/8.0,0.0,1.0));
     g.setColour(Theme::violet.withAlpha(k==selectedMap?0.95f:0.52f));
     g.drawRoundedRectangle(gx1,y+2,std::max(2.0f,gx2-gx1),height-4,3.0f,1.5f);
     g.setFont(Theme::font(9.0f,true));g.drawText("L",int(gx1)+3,int(y)+25,16,16,juce::Justification::centredLeft);
   }
   g.setColour(Theme::cyan.withAlpha(0.85f));g.drawVerticalLine(int(x+width-2),y,y+height);
   g.setColour(Theme::muted);g.setFont(Theme::font(11.0f));
   for(int i=0;i<=4;++i)g.drawText(juce::String(-8+i*2)+"s",int(x+width*i/4),int(y+height)+6,35,18,juce::Justification::centredLeft);
   g.drawText("BPM "+juce::String(bpm,1),getWidth()-126,13,100,22,juce::Justification::centredRight);
   if(processor.gapMap.size()>0){g.setColour(Theme::violet);g.drawText("MAP  "+juce::String(processor.gapMap.size())+"  LOCKED EVENTS",20,getHeight()-28,180,22,juce::Justification::centredLeft);}
 }
 void resized() override {preview.setBounds(getWidth()-110,getHeight()-32,90,25);}
 void mouseDown(const juce::MouseEvent& e) override {
   const auto sr=std::max(8000.0,processor.sampleRateAtomic.load());
   const double age=8.0*(1.0-std::clamp((e.position.x-15.0f)/std::max(1.0f,float(getWidth()-30)),0.0f,1.0f));
   const auto clock=processor.totalSamples.load();selected=-1;
   for(int i=0;i<processor.getRecentCount();++i){const auto gap=processor.getRecentGap(i);
     if(gap.start<=clock-int64_t(age*sr) && clock-int64_t(age*sr)<gap.end){selected=i;break;}
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
 void timerCallback() override {repaint();}
 SkellSilenceAudioProcessor& processor;
 juce::TextButton preview;
 int selected=-1,selectedMap=-1;float lastX=0;
};
}
