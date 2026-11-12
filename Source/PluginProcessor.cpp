#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "dsp/GapClass.h"
#include <cmath>
#include <algorithm>

using APVTS=juce::AudioProcessorValueTreeState;
using namespace skell::dsp;
namespace {
  juce::ParameterID id(const juce::String& name) {return {name,1};}
  void addFloat(APVTS::ParameterLayout& l,const juce::String& name,float lo,float hi,float initial,float step=0.001f) {
    l.add(std::make_unique<juce::AudioParameterFloat>(id(name),name,juce::NormalisableRange<float>(lo,hi,step),initial));
  }
  void addBool(APVTS::ParameterLayout& l,const juce::String& name,bool initial) {
    l.add(std::make_unique<juce::AudioParameterBool>(id(name),name,initial));
  }
  void addChoice(APVTS::ParameterLayout& l,const juce::String& name,juce::StringArray choices,int index) {
    l.add(std::make_unique<juce::AudioParameterChoice>(id(name),name,choices,index));
  }
  float protect(float sample) noexcept {
    const auto amplitude=std::abs(sample);
    return amplitude<=0.98f?sample:std::copysign(0.98f+0.02f*std::tanh((amplitude-0.98f)*50.0f),sample);
  }
}
SkellSilenceAudioProcessor::SkellSilenceAudioProcessor()
 : AudioProcessor(BusesProperties()
     .withInput("Input",juce::AudioChannelSet::stereo(),true)
     .withInput("Sidechain",juce::AudioChannelSet::stereo(),false)
     .withOutput("Output",juce::AudioChannelSet::stereo(),true)),
   parameters(*this,nullptr,"PARAMETERS",createLayout()) {
  for(auto& v:waveform) v.store(0);
  for(auto& v:recentStarts) v.store(0);
  for(auto& v:recentEnds) v.store(0);
  for(auto& v:recentBpms) v.store(120);
  cacheParameters();
}
APVTS::ParameterLayout SkellSilenceAudioProcessor::createLayout() {
  APVTS::ParameterLayout l;
  addFloat(l,"mix",0,1,0.0f);
  addFloat(l,"tension",0,1,0.0f);addFloat(l,"space",0,1,0.0f);
  addFloat(l,"duckAfter",0,1,0.0f);
  addChoice(l,"lookahead",{"OFF","250 ms","500 ms","1 beat","1 bar"},1);
  addChoice(l,"triggerSource",{"AUTO","SIDECHAIN","GRID","MIDI"},0);
  addChoice(l,"gridDivision",{"1/4","1/8","1/16","1/32"},1);
  addFloat(l,"gridOffset",0,1,0.0f);
  addFloat(l,"threshold",3,40,18,0.1f);
  addFloat(l,"minGap",10,2000,90,1);
  addFloat(l,"maxGap",500,30000,6000,10);
  addFloat(l,"hold",0,300,45,1);
  addFloat(l,"tailSensitivity",0,1,0.6f);
  addFloat(l,"armTime",0,10,0.4f,0.01f);
  addFloat(l,"classShortMax",0.25f,1,0.5f,0.125f);
  addFloat(l,"classMediumMax",1,4,2,0.25f);
  addFloat(l,"classLongMax",2.5f,16,4,0.5f);
  for(size_t i=0;i<instrumentIds.size();++i){
    const auto name=juce::String(instrumentIds[i]);
    addBool(l,name+"On",true);addFloat(l,name+"Level",0,1,0.6f);
    for(int c=0;c<4;++c){
      const bool defaults[7][4]={{true,false,false,false},{false,true,false,false},{false,false,true,true},
                                 {false,true,true,false},{false,false,false,true},{false,false,false,true},{true,false,false,false}};
      addBool(l,"rule_"+name+"_"+juce::String(c),defaults[i][c]);
    }
  }
  addFloat(l,"stopSpeedCurve",0,1,0.4f);addFloat(l,"stopTime",0.05f,2,0.45f,0.01f);
  addFloat(l,"stopLowpass",0,1,0.7f);
  addChoice(l,"airColor",{"FOLLOW","PINK","WHITE"},0);addFloat(l,"airShape",0,1,0.5f);
  addFloat(l,"swellLength",80,2000,500,10);addFloat(l,"swellReverb",0,1,0.6f);
  addChoice(l,"noiseType",{"WHITE","PINK","VINYL","ROOM"},1);
  addFloat(l,"noiseFadeIn",0.01f,0.9f,0.18f);addFloat(l,"noiseFadeOut",0.01f,0.9f,0.18f);
  addFloat(l,"impactPitch",0,1,0.35f);addFloat(l,"impactDecay",0,1,0.5f);addFloat(l,"impactClick",0,1,0.4f);
  addFloat(l,"riserStart",0,1,0.25f);addFloat(l,"riserCurve",0,1,0.5f);addFloat(l,"riserNoiseMix",0,1,0.8f);
  addChoice(l,"stutterDiv",{"1/4","1/8","1/16","1/32","1/64"},2);
  addFloat(l,"stutterDecay",0,0.95f,0.2f);addFloat(l,"stutterCount",1,32,6,1);
  addBool(l,"learnArmed",false);addBool(l,"lockToMap",false);
  // Added after every existing APVTS ID: old project automation stays stable.
  addBool(l,"pluginEnabled",true);
  return l;
}
namespace {
  constexpr std::array<const char*,39> namedIds={
     "mix","tension","space","duckAfter","lookahead","triggerSource","gridDivision","gridOffset",
     "threshold","minGap","maxGap","hold","tailSensitivity","armTime",
     "classShortMax","classMediumMax","classLongMax",
     "stopSpeedCurve","stopTime","stopLowpass","airColor","airShape",
     "swellLength","swellReverb","noiseType","noiseFadeIn","noiseFadeOut",
     "impactPitch","impactDecay","impactClick","riserStart","riserCurve","riserNoiseMix",
     "stutterDiv","stutterDecay","stutterCount","learnArmed","lockToMap","pluginEnabled"
  };
}
void SkellSilenceAudioProcessor::cacheParameters() {
  for(size_t i=0;i<namedParams.size();++i)namedParams[i]=parameters.getRawParameterValue(namedIds[i]);
  for(size_t i=0;i<instrumentIds.size();++i){
    const juce::String stem(instrumentIds[i]);
    onParams[i]=parameters.getRawParameterValue(stem+"On");
    levelParams[i]=parameters.getRawParameterValue(stem+"Level");
    for(int c=0;c<4;++c)ruleParams[i][size_t(c)]=parameters.getRawParameterValue("rule_"+stem+"_"+juce::String(c));
  }
}
float SkellSilenceAudioProcessor::param(const char* name) const noexcept {
  for(size_t i=0;i<namedIds.size();++i)if(std::strcmp(name,namedIds[i])==0)
     return namedParams[i]->load(std::memory_order_relaxed);
  return 0;
}
void SkellSilenceAudioProcessor::snapshotSettings(InstrumentSettings& s) const noexcept {
  for(size_t i=0;i<instrumentIds.size();++i){
    s.enabled[i]=onParams[i]->load(std::memory_order_relaxed)>=0.5f;
    s.levels[i]=levelParams[i]->load(std::memory_order_relaxed);
    for(int c=0;c<4;++c) s.rules[i][size_t(c)]=ruleParams[i][size_t(c)]->load(std::memory_order_relaxed)>=0.5f;
  }
  s.stopSpeedCurve=param("stopSpeedCurve");s.stopTime=param("stopTime");s.stopLowpass=param("stopLowpass");
  s.airColor=int(param("airColor"));s.airShape=param("airShape");
  s.swellLength=param("swellLength");s.swellReverb=param("swellReverb");
  s.noiseType=int(param("noiseType"));s.noiseFadeIn=param("noiseFadeIn");s.noiseFadeOut=param("noiseFadeOut");
  s.impactPitch=param("impactPitch");s.impactDecay=param("impactDecay");s.impactClick=param("impactClick");
  s.riserStart=param("riserStart");s.riserCurve=param("riserCurve");s.riserNoiseMix=param("riserNoiseMix");
  s.stutterDiv=int(param("stutterDiv"));s.stutterDecay=param("stutterDecay");s.stutterCount=int(param("stutterCount"));
}
bool SkellSilenceAudioProcessor::isBusesLayoutSupported(const BusesLayout& l) const {
  const auto main=l.getMainInputChannelSet();
  if(main!=juce::AudioChannelSet::mono() && main!=juce::AudioChannelSet::stereo()) return false;
  if(main!=l.getMainOutputChannelSet()) return false;
  const auto side=l.getChannelSet(true,1);
  return side.isDisabled() || side==juce::AudioChannelSet::mono() || side==juce::AudioChannelSet::stereo();
}
void SkellSilenceAudioProcessor::prepareToPlay(double rate,int /*blockSize*/) {
  sr=std::max(8000.0,rate);sampleRateAtomic.store(sr);
  delay.prepare(sr);
  for(size_t ch=0;ch<2;++ch){histories[ch].prepare(sr);instruments[ch].prepare(sr,int(ch));}
  detector.prepare(sr);wetTransition.prepare(sr);
  smoothMix.reset(sr,0.012);smoothTension.reset(sr,0.020);smoothSpace.reset(sr,0.020);
  smoothMix.setCurrentAndTargetValue(param("mix"));smoothTension.setCurrentAndTargetValue(param("tension"));smoothSpace.setCurrentAndTargetValue(param("space"));
  clearRuntime();
  bypassActive=false;lastTransport=false;
  activeLatency=latencyFor(lastBpm);
  latencyRequested.store(activeLatency);
  // prepareToPlay is not the realtime callback: report the starting delay
  // synchronously so the host can compensate the very first audio block.
  setLatencySamples(activeLatency);
  triggerAsyncUpdate();
}
void SkellSilenceAudioProcessor::clearRuntime(bool preserveHistory) noexcept {
  detector.reset();delay.reset();
  for(size_t ch=0;ch<2;++ch){if(!preserveHistory)histories[ch].reset(samples);instruments[ch].reset();}
  readEvents=writtenEvents=0;pendingLearnEvent=-1;previewRemaining=0;gridInGap=false;wasFxActive=false;
  gapClassLatch.reset();wetTransition.reset();midiGate.reset();
  lastTriggerSource=-1;lastLockToMap=false;
  wetTailRemaining=0;lastGapSample=-1000000000LL;
  peak=0;peakSamples=0;activeMask.store(0);activeLengthClass.store(-1);
}
int SkellSilenceAudioProcessor::latencyFor(double bpm) const noexcept {
  const int mode=int(param("lookahead"));
  if(mode==0) return 0;
  if(mode==1) return int(sr*0.250);
  if(mode==2) return int(sr*0.500);
  return int(std::clamp((mode==3?1.0:4.0)*60.0/std::max(20.0,bpm),0.0,16.0)*sr);
}
void SkellSilenceAudioProcessor::handleAsyncUpdate() {
  const auto requested=latencyRequested.load();
  if(getLatencySamples()!=requested) setLatencySamples(requested);
}
void SkellSilenceAudioProcessor::addEvent(int64_t start,double bpm) noexcept {
  auto& e=events[size_t(writtenEvents%events.size())];
  e.start=start;e.end=-1;e.bpm=bpm;
  for(size_t ch=0;ch<2;++ch)e.spectrum[ch]=instruments[ch].snapshotSpectrum();
  ++writtenEvents;
  if(writtenEvents-readEvents>events.size())readEvents=writtenEvents-events.size();
}
void SkellSilenceAudioProcessor::closeEvent(int64_t end) noexcept {
  if(writtenEvents==0) return;
  auto& e=events[size_t((writtenEvents-1)%events.size())];
  if(e.end>=0) return;
  e.end=std::max(e.start+1,end);
  const int r=recentCount.fetch_add(1,std::memory_order_relaxed)%32;
  recentStarts[size_t(r)].store(e.start,std::memory_order_release);
  recentEnds[size_t(r)].store(e.end,std::memory_order_release);
  recentBpms[size_t(r)].store(e.bpm,std::memory_order_release);
  lastGapSample=e.end;
}
SkellSilenceAudioProcessor::RecentGap SkellSilenceAudioProcessor::getRecentGap(int index) const noexcept {
  const int count=recentCount.load(std::memory_order_acquire);
  if(index<0 || index>=std::min(32,count)) return {};
  const int idx=(count-1-index+32*2048)%32;
  return {recentStarts[size_t(idx)].load(),recentEnds[size_t(idx)].load(),recentBpms[size_t(idx)].load()};
}
void SkellSilenceAudioProcessor::requestMapEdit(int index,double deltaPpq,bool remove) noexcept {
  editDelta.store(deltaPpq);editRemove.store(remove);editIndex.store(index);
}
// Run requests exclusively on the audio thread, even while global power or
// the host bypass is active. A cleared map must not reappear in a saved preset.
void SkellSilenceAudioProcessor::applyMapRequests() noexcept {
  if(clearMapRequested.exchange(false)) gapMap.clear();
  if(const int idx=editIndex.exchange(-1);idx>=0){
    if(editRemove.exchange(false))gapMap.erase(idx);
    else {
      const auto g=gapMap.get(idx), d=editDelta.load();
      gapMap.replace(idx,{std::max(0.0,g.from+d),std::max(0.001,g.to+d)});
    }
  }
}
// Keep the eight-second input history live on both the active and dry paths.
// Neither skipped effects nor a host bypass should freeze waveform feedback.
void SkellSilenceAudioProcessor::collectWaveform(float inL,float inR) noexcept {
  peak=std::max(peak,std::max(std::abs(inL),std::abs(inR)));
  if(++peakSamples>=size_t(sr/72)){
    const auto index=waveformSequence.fetch_add(1)%waveformSize;
    waveform[size_t(index)].store(std::min(1.0f,peak),std::memory_order_release);
    peakSamples=0;peak=0;
  }
}
// Host bypass uses the SAME delay ring and declared PDC as active processing.
// Never reset the dry delay when toggling bypass: that would create a dropout.
void SkellSilenceAudioProcessor::processBlockBypassed(juce::AudioBuffer<float>& buffer,
                                                     juce::MidiBuffer&) {
  juce::ScopedNoDenormals noDenormals;
  auto main=getBusBuffer(buffer,false,0);
  if(main.getNumChannels()==0)return;
  applyMapRequests();
  const auto* playhead=getPlayHead();
  const auto pos=playhead?playhead->getPosition():
      std::optional<juce::AudioPlayHead::PositionInfo>{};
  const bool transportPlaying=pos?pos->getIsPlaying():true;
  const double bpm=pos?std::clamp(pos->getBpm().orFallback(120.0),20.0,300.0):120.0;
  const double blockPpq=pos?pos->getPpqPosition().orFallback(lastExpectedPpq):lastExpectedPpq;
  // Match active processing's latency policy: adopt changed tempo/lookahead
  // only on transport start or while stopped, never in the middle of playback.
  if(!transportPlaying || !lastTransport){
    const int requested=latencyFor(bpm);
    if(requested!=activeLatency) {
      activeLatency=requested;
      if(latencyRequested.exchange(requested)!=requested)triggerAsyncUpdate();
    }
  }
  lastTransport=transportPlaying;lastBpm=bpm;
  bpmAtomic.store(bpm,std::memory_order_relaxed);
  isPlaying.store(transportPlaying,std::memory_order_release);
  const int channels=main.getNumChannels();
  auto* left=main.getWritePointer(0);
  auto* right=channels>1?main.getWritePointer(1):nullptr;
  if(!bypassActive){
    bypassActive=true;
    detector.reset();midiGate.reset();gapClassLatch.reset();wetTransition.reset();
    readEvents=writtenEvents=0;
    gridInGap=false;wasFxActive=false;
    lastTriggerSource=-1;lastLockToMap=false;
    previewRemaining=0;wetTailRemaining=0;
    fastMeter.store(0.0f);slowMeter.store(0.0f);thresholdMeter.store(0.0f);
    detectorState.store(0,std::memory_order_release);
    for(auto& instrument:instruments)instrument.reset();
    activeMask.store(0,std::memory_order_release);
    activeLengthClass.store(-1,std::memory_order_release);
  }
  inputChannels.store(channels,std::memory_order_relaxed);
  for(int i=0;i<main.getNumSamples();++i){
    const float inL=left[i],inR=right?right[i]:inL;
    delay.push(0,inL);delay.push(1,inR);
    histories[0].push(inL);histories[1].push(inR);
    instruments[0].observeInput(inL);instruments[1].observeInput(inR);
    collectWaveform(inL,inR);
    left[i]=delay.delayed(0,activeLatency);
    if(right)right[i]=delay.delayed(1,activeLatency);
    delay.next();
    ++samples;
  }
  const double step=bpm/(60.0*sr);
  lastExpectedPpq=blockPpq+double(main.getNumSamples())*step;
  currentPpqAtomic.store(lastExpectedPpq,std::memory_order_release);
  totalSamples.store(samples,std::memory_order_release);
}
void SkellSilenceAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer,juce::MidiBuffer& midi) {
  juce::ScopedNoDenormals guard;
  // The front-panel power reuses the PDC-preserving host bypass pathway.
  if(param("pluginEnabled")<0.5f) {
    processBlockBypassed(buffer,midi);
    return;
  }
  bypassActive=false;
  auto main=getBusBuffer(buffer,false,0);
  if(main.getNumChannels()==0) return;
  const auto side=getBusBuffer(buffer,true,1);
  const int n=main.getNumSamples(),nc=main.getNumChannels();
  inputChannels.store(nc,std::memory_order_relaxed);
  auto* left=main.getWritePointer(0);
  auto* right=nc==2?main.getWritePointer(1):nullptr;
  const auto* sideL=side.getNumChannels()>0?side.getReadPointer(0):nullptr;
  const auto* sideR=side.getNumChannels()>1?side.getReadPointer(1):nullptr;

  applyMapRequests();
  auto* playhead=getPlayHead();
  const auto pos=playhead?playhead->getPosition():std::optional<juce::AudioPlayHead::PositionInfo>{};
  const bool transportPlaying=pos?pos->getIsPlaying():true;
  const double bpm=pos?std::clamp(pos->getBpm().orFallback(120.0),20.0,300.0):120.0;
  const double blockPpq=pos?pos->getPpqPosition().orFallback(lastExpectedPpq):lastExpectedPpq;
  const bool jumped=lastTransport && transportPlaying && std::abs(blockPpq-lastExpectedPpq)>0.15;
  if(jumped || (lastTransport && !transportPlaying)) clearRuntime(!jumped && !transportPlaying);
  const bool wasPlaying=lastTransport;
  isPlaying.store(transportPlaying);lastTransport=transportPlaying;lastBpm=bpm;bpmAtomic.store(bpm);
  const bool lock=param("lockToMap")>0.5f;
  // Never toggle PDC to zero when LOCK is enabled. A stable latency contract is
  // essential for hosts that cannot reconfigure compensation mid-playback.
  // Keep audio delay and host PDC consistent through an entire transport pass.
  // Tempo/choice changes are adopted when stopped or when playback begins.
  if(!transportPlaying || !wasPlaying) activeLatency=latencyFor(bpm);
  const int latency=activeLatency;
  if(latencyRequested.exchange(latency)!=latency) triggerAsyncUpdate();
  smoothMix.setTargetValue(param("mix"));smoothTension.setTargetValue(param("tension"));smoothSpace.setTargetValue(param("space"));
  const float duck=param("duckAfter"),shortMax=param("classShortMax"),mediumMax=param("classMediumMax"),longMax=param("classLongMax");
  const int source=int(param("triggerSource"));
  if(source!=lastTriggerSource || lock!=lastLockToMap){
    // Change trigger mode without flushing delay or effect histories. An old
    // held MIDI key or open detector event must never survive re-entry into
    // MIDI/GRID/LOCK mode and silently keep the next gap open.
    if(lastTriggerSource>=0)closeEvent(samples);
    midiGate.reset();gridInGap=false;detector.reset();
    lastTriggerSource=source;lastLockToMap=lock;
  }
  constexpr double gridBeats[4]={1.0,0.5,0.25,0.125};
  const double gridDivision=gridBeats[std::clamp(int(param("gridDivision")),0,3)];
  const double gridOffset=param("gridOffset");
  const bool learn=param("learnArmed")>0.5f;
  DetectorSettings d;
  d.thresholdDb=param("threshold");d.minGapMs=param("minGap");d.maxGapMs=param("maxGap");
  d.holdMs=param("hold");d.tailSensitivity=param("tailSensitivity");d.armTimeSeconds=param("armTime");
  InstrumentSettings inst;snapshotSettings(inst);
  const double ppqPerSample=bpm/(60.0*sr);
  // Maintain grid phase by addition: avoid fmod() per sample and support
  // negative PPQ positions without a large artificial offset.
  double gridPhase=std::fmod(blockPpq-gridOffset*gridDivision,gridDivision);
  if(gridPhase<0.0)gridPhase+=gridDivision;
  const int previewIndex=previewRequested.exchange(-1);
  if(previewIndex>=0 && !transportPlaying && getRecentCount()>0) {
    previewStartSample=samples;
    const auto gap=getRecentGap(std::min(previewIndex,getRecentCount()-1));
    previewSourceStart=gap.start;
    previewTotal=previewRemaining=std::max<int64_t>(1,std::min<int64_t>(int64_t(sr*0.75),gap.end-gap.start));
  }
  // JUCE 8's zero-allocation MidiBufferIterator replaces deprecated Iterator.
  // Keep sample offsets intact so MIDI gap starts/ends remain sample-accurate.
  auto midiIterator=midi.cbegin();
  const auto midiEnd=midi.cend();
  // Publish activity at block boundaries, not tens of thousands of atomic
  // writes per second. The UI refreshes independently at 12-30 Hz.
  int blockActiveClass=-1,blockActiveMask=0;
  for(int i=0;i<n;++i) {
    const auto clock=samples++;
    const float inL=left[i],inR=right?right[i]:inL;
    // Stereo detection uses power, not (L+R)/2, to protect anti-phase material.
    delay.push(0,inL);delay.push(1,inR);
    histories[0].push(inL);
    histories[1].push(inR);
    instruments[0].observeInput(inL);
    instruments[1].observeInput(inR); // Independent pre-gap spectra per channel.
    const double ppq=blockPpq+i*ppqPerSample;
    DetectionResult detected;
    bool begin=false,end=false;
    int64_t eventStart=clock,eventEnd=clock;
    if(transportPlaying && !lock) {
      if(source==0 || source==1) {
        if(source==1 && sideL!=nullptr)
          detected=detector.processStereo(sideL[i],sideR?sideR[i]:sideL[i],clock,d);
        else detected=detector.processStereo(inL,inR,clock,d);
        begin=detected.began;end=detected.ended;
        if(begin) eventStart=detected.start;
        if(end) eventEnd=detected.end;
      } else if(source==2){
        const bool inGap=gridPhase>=gridDivision*0.75;
        begin=inGap && !gridInGap;end=!inGap && gridInGap;
        gridInGap=inGap;
      } else if(source==3){
        while(midiIterator!=midiEnd && (*midiIterator).samplePosition<=i){
          // Interpret raw note bytes with a fixed-capacity channel-aware gate.
          // One overlapping note-off must not end the gap while another note
          // is held, and repeated note-on messages must not retrigger it.
          const auto event=*midiIterator;
          if(event.numBytes>=3){
            const auto edge=midiGate.processRaw(event.data[0],event.data[1],event.data[2]);
            if(edge==MidiNoteGate::Edge::opened){begin=true;eventStart=clock;}
            if(edge==MidiNoteGate::Edge::closed){end=true;eventEnd=clock;}
          }
          ++midiIterator;
        }
      }
      if(source==3 && !end && writtenEvents>0) {
        auto& last=events[size_t((writtenEvents-1)%events.size())];
        if(last.end<0 && clock-last.start>=int64_t(d.maxGapMs*sr/1000.0)){
          end=true;eventEnd=clock;midiGate.reset();
        }
      }
      if(end){closeEvent(eventEnd);if(learn && ppq>openGapPpq)gapMap.append(openGapPpq,ppq);}
      if(begin){ addEvent(eventStart,bpm);openGapPpq=ppq-double(clock-eventStart)*ppqPerSample; }
    }
    collectWaveform(inL,inR);
    const auto dryL=delay.delayed(0,latency),dryR=delay.delayed(1,latency);
    const auto delayedClock=clock-latency;
    const double delayedPpq=ppq-latency*ppqPerSample;
    const float wetMix=smoothMix.getNextValue(),tension=smoothTension.getNextValue(),space=smoothSpace.getNextValue();
    double gapStart=0,gapLen=0;
    bool active=false,gapEndKnown=true;
    if(transportPlaying && lock){
      // Map is bounded and only read once per ~32 samples; interpolation below uses PPQ.
      if(i%32==0){
        pendingLearnEvent=-1;
        for(int k=0;k<gapMap.size();++k){const auto g=gapMap.get(k);
          if(delayedPpq>=g.from && delayedPpq<g.to){pendingLearnEvent=k;break;}
          if(g.from>delayedPpq && g.from<delayedPpq+32*ppqPerSample){pendingLearnEvent=k;break;}
        }
      }
      if(pendingLearnEvent>=0){const auto g=gapMap.get(pendingLearnEvent);
        active=delayedPpq>=g.from && delayedPpq<g.to;
        gapStart=double(delayedClock)-(delayedPpq-g.from)/ppqPerSample;
        gapLen=(g.to-g.from)/ppqPerSample;
      }
    } else if(transportPlaying){
      while(readEvents<writtenEvents) {
        const auto& e=events[size_t(readEvents%events.size())];
        if(e.end>=0 && delayedClock>=e.end){++readEvents;continue;}
        if(delayedClock>=e.start && (e.end<0 || delayedClock<e.end)) {
          active=true;gapStart=double(e.start);gapEndKnown=e.end>=0;
          gapLen=e.end>=0?double(e.end-e.start):std::max(sr*60.0/bpm,double(delayedClock-e.start)+sr*0.1);
        }
        break;
      }
    } else if(previewRemaining>0){
      active=true;gapStart=double(previewSourceStart);
      gapLen=double(previewTotal);
      --previewRemaining;
    }
    float wetL=0.0f,wetR=0.0f;
    if(active && !wasFxActive) {
      // The preceding spectral profile is captured at the detector event, not
      // 250ms/one-beat later when the delayed render reaches that gap.
      for(size_t ch=0;ch<2;++ch) {
        if(transportPlaying && !lock && readEvents<writtenEvents)
          instruments[ch].beginGap(&events[size_t(readEvents%events.size())].spectrum[ch]);
        else instruments[ch].beginGap();
      }
    }
    if(wasFxActive && !active && transportPlaying) {
      // Renderer-clock transition, not detector-clock: works identically for
      // AUTO, SIDECHAIN, GRID, MIDI and learned-map playback.
      lastGapSample=delayedClock;
    }
    wasFxActive=active;
    if(active && gapLen>1) {
      const double renderTime=transportPlaying?double(delayedClock)-gapStart:double(clock-previewStartSample);
      const float progress=std::clamp(float(renderTime/gapLen),0.0f,1.0f);
      const int cl=gapClassLatch.advance(true,gapLen/sr*bpm/60.0,shortMax,mediumMax,longMax);
      const GapContext contextL{histories[0],sr,bpm,gapStart,gapLen,renderTime,progress,tension,space,gapEndKnown};
      wetL=instruments[0].process(contextL,inst,cl);
      if(right){
        const GapContext contextR{histories[1],sr,bpm,gapStart,gapLen,renderTime,progress,tension,space,gapEndKnown};
        wetR=instruments[1].process(contextR,inst,cl);
      }
      wetTailRemaining=std::max<int64_t>(1,int64_t(sr*2));
      blockActiveClass=cl;
      int mask=0;for(int ins=0;ins<7;++ins)if(inst.enabled[size_t(ins)] && inst.rules[size_t(ins)][size_t(cl)])mask|=1<<ins;
      blockActiveMask=mask;
    } else {
      gapClassLatch.reset();
      blockActiveMask=0;blockActiveClass=-1;
      if (wetTailRemaining>0 && transportPlaying) {
        const float fade=std::min(1.0f,float(wetTailRemaining)/(float(sr)*0.5f));
        wetL=instruments[0].tail(space)*fade;
        if(right)wetR=instruments[1].tail(space)*fade;
        --wetTailRemaining;
      }
    }
    // Ramp wet processing at the *rendered* boundary. Lookahead OFF can
    // confirm a gap after its actual onset, so the instrument's analytical
    // 5ms edge alone is not sufficient to avoid an abrupt entry.
    const auto transitioned=wetTransition.process(active && gapLen>1.0,
                                                   active?wetL:0.0f,
                                                   active?wetR:0.0f);
    if(active){wetL=transitioned[0];wetR=transitioned[1];}
    else {wetL+=transitioned[0];wetR+=transitioned[1];}
    // At MIX 0 preserve the original signal bit-for-bit (including high peaks).
    const double postGap=double(delayedClock-lastGapSample)/sr;
    const float lift=(!active && postGap>=0.0 && postGap<0.055)
      ? duck*0.18f*wetMix*std::sin(float(3.14159265358979323846*postGap/0.055)) : 0.0f;
    const float outL=dryL*(1.0f+lift)+wetL*wetMix;
    const float outR=dryR*(1.0f+lift)+wetR*wetMix;
    // Do not clamp the unprocessed dry track while an effect is inactive.
    // In particular this must hold even when MIX is non-zero.
    // Protect only channels containing added material; dry samples are
    // bit-exact even if the other stereo channel carries an effect.
    left[i]=(wetMix<=0.0f && lift<=0.0f) || (std::abs(wetL)<1.0e-9f && lift<=0.0f)
              ?dryL:protect(outL);
    if(right)right[i]=(wetMix<=0.0f && lift<=0.0f) || (std::abs(wetR)<1.0e-9f && lift<=0.0f)
              ?dryR:protect(outR);
    if(i==n-1){
      const bool followsAudio=!lock && (source==0 || source==1);
      fastMeter.store(followsAudio ? detected.fast : 0.0f,std::memory_order_relaxed);
      slowMeter.store(followsAudio ? detected.slow : 0.0f,std::memory_order_relaxed);
      thresholdMeter.store(followsAudio ? detected.threshold : 0.0f,std::memory_order_relaxed);
      const int status=!transportPlaying ? 0 : lock ? (active?2:0)
        : source==3 ? (midiGate.activeCount()>0?2:0)
        : source==2 ? (gridInGap?2:0) : int(detector.getState());
      detectorState.store(status,std::memory_order_release);
    }
    delay.next();
    if(source==2) {
      gridPhase+=ppqPerSample;
      if(gridPhase>=gridDivision)gridPhase-=gridDivision;
    }
  }
  activeMask.store(blockActiveMask,std::memory_order_release);
  activeLengthClass.store(blockActiveClass,std::memory_order_release);
  lastExpectedPpq=blockPpq+n*ppqPerSample;currentPpqAtomic.store(lastExpectedPpq);
  totalSamples.store(samples);
  int count=0;
  for(int k=0;k<getRecentCount();++k)if(samples-getRecentGap(k).end<sr*60.0)++count;
  gapsLastMinute.store(count);
}
juce::AudioProcessorEditor* SkellSilenceAudioProcessor::createEditor(){return new SkellSilenceAudioProcessorEditor(*this);}
void SkellSilenceAudioProcessor::getStateInformation(juce::MemoryBlock& dest) {
  auto state=parameters.copyState();
  juce::ValueTree ui("SKELL_UI");ui.setProperty("width",windowW.load(),nullptr);ui.setProperty("height",windowH.load(),nullptr);
  juce::ValueTree map("GAPS");
  for(int i=0;i<gapMap.size();++i){const auto g=gapMap.get(i);
    juce::ValueTree item("GAP");item.setProperty("from",g.from,nullptr);item.setProperty("to",g.to,nullptr);map.addChild(item,-1,nullptr);
  }
  ui.addChild(map,-1,nullptr);state.addChild(ui,-1,nullptr);
  if(auto xml=state.createXml())copyXmlToBinary(*xml,dest);
}
void SkellSilenceAudioProcessor::setStateInformation(const void* data,int size) {
  if(const auto xml=getXmlFromBinary(data,size))if(xml->hasTagName(parameters.state.getType())){
    auto state=juce::ValueTree::fromXml(*xml);
    const auto ui=state.getChildWithName("SKELL_UI");
    if(ui.isValid()){
      windowW.store(juce::jlimit(760,1800,int(ui.getProperty("width",912))));
      windowH.store(juce::jlimit(481,1140,int(ui.getProperty("height",578))));
      gapMap.clear();const auto map=ui.getChildWithName("GAPS");
      for(const auto& item:map)gapMap.append(double(item.getProperty("from",0.0)),double(item.getProperty("to",0.0)));
      state.removeChild(ui,nullptr);
    }
    parameters.replaceState(state);
  }
}
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(){return new SkellSilenceAudioProcessor();}
