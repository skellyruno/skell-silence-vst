#pragma once
#include <JuceHeader.h>
#include "dsp/GapDetector.h"
#include "dsp/GapMap.h"
#include "dsp/LookaheadBuffer.h"
#include "dsp/InstrumentMixer.h"
#include "dsp/GapClass.h"
#include "dsp/GapTransition.h"
#include "dsp/MidiNoteGate.h"
#include <array>
#include <atomic>

class SkellSilenceAudioProcessor final : public juce::AudioProcessor, private juce::AsyncUpdater {
public:
  SkellSilenceAudioProcessor();
  ~SkellSilenceAudioProcessor() override {cancelPendingUpdate();}
  void prepareToPlay(double,int) override;
  void releaseResources() override {}
  bool isBusesLayoutSupported(const BusesLayout&) const override;
  void processBlock(juce::AudioBuffer<float>&,juce::MidiBuffer&) override;
  void processBlockBypassed(juce::AudioBuffer<float>&,juce::MidiBuffer&) override;
  juce::AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override {return true;}
  const juce::String getName() const override {return "Skell Silence";}
  bool acceptsMidi() const override {return true;}
  bool producesMidi() const override {return false;}
  bool isMidiEffect() const override {return false;}
  double getTailLengthSeconds() const override {return 2.0;}
  int getNumPrograms() override {return 1;}
  int getCurrentProgram() override {return 0;}
  void setCurrentProgram(int) override {}
  const juce::String getProgramName(int) override {return "Default";}
  void changeProgramName(int,const juce::String&) override {}
  void getStateInformation(juce::MemoryBlock&) override;
  void setStateInformation(const void*,int) override;
  static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();
  juce::AudioProcessorValueTreeState parameters;

  struct RecentGap {int64_t start=0,end=0;double bpm=120;};
  static constexpr int waveformSize=576;
  std::array<std::atomic<float>,waveformSize> waveform{};
  std::atomic<uint64_t> waveformSequence{0};
  std::atomic<float> fastMeter{0},slowMeter{0},thresholdMeter{0};
  std::atomic<int> detectorState{0},gapsLastMinute{0},activeLengthClass{-1},activeMask{0};
  std::atomic<int64_t> totalSamples{0};
  std::atomic<double> sampleRateAtomic{44100.0},bpmAtomic{120.0},currentPpqAtomic{0.0};
  std::atomic<int> latencyRequested{0}, inputChannels{2};
  std::atomic<bool> isPlaying{false};
  std::atomic<int> windowW{912},windowH{578};
  skell::dsp::GapMap gapMap;
  void requestClearMap() noexcept {clearMapRequested.store(true);}
  void requestMapEdit(int index,double deltaPpq,bool remove=false) noexcept;
  void requestPreview(int selectedIndex) noexcept {previewRequested.store(selectedIndex);}
  RecentGap getRecentGap(int index) const noexcept;
  int getRecentCount() const noexcept {return std::min(32,recentCount.load());}
private:
  void handleAsyncUpdate() override;
  void snapshotSettings(skell::dsp::InstrumentSettings&) const noexcept;
  void cacheParameters();
  void applyMapRequests() noexcept;
  void collectWaveform(float left,float right) noexcept;
  float param(const char*) const noexcept;
  int latencyFor(double bpm) const noexcept;
  int activeLatency=0;
  void addEvent(int64_t start,double bpm) noexcept;
  void closeEvent(int64_t end) noexcept;
  void clearRuntime(bool preserveHistory=false) noexcept;
  struct Event {
    int64_t start=0,end=-1;
    double bpm=120;
    std::array<skell::dsp::AirNoise::Spectrum,2> spectrum{};
  };
  std::array<Event,256> events{};
  uint64_t writtenEvents=0,readEvents=0;
  int64_t samples=0;
  double sr=44100, lastPpq=0,lastExpectedPpq=0, lastBpm=120;
  bool lastTransport=false;
  bool bypassActive=false;
  int pendingLearnEvent=-1;
  bool gridInGap=false,wasFxActive=false;
  int lastTriggerSource=-1;
  bool lastLockToMap=false;
  double openGapPpq=0;
  std::array<std::atomic<float>*,7> onParams{},levelParams{};
  std::array<std::array<std::atomic<float>*,4>,7> ruleParams{};
  static constexpr int namedCount=39;
  std::array<std::atomic<float>*,namedCount> namedParams{};
  skell::dsp::GapDetector detector;
  skell::dsp::MidiNoteGate midiGate;
  skell::dsp::GapClassLatch gapClassLatch;
  skell::dsp::GapTransition wetTransition;
  skell::dsp::LookaheadBuffer delay;
  std::array<skell::dsp::HistoryBuffer,2> histories;
  std::array<skell::dsp::InstrumentMixer,2> instruments;
  juce::SmoothedValue<float,juce::ValueSmoothingTypes::Linear> smoothMix,smoothTension,smoothSpace;
  std::array<std::atomic<int64_t>,32> recentStarts{},recentEnds{};
  std::array<std::atomic<double>,32> recentBpms{};
  std::atomic<int> recentCount{0};
  int64_t lastGapSample=-1000000000LL;
  int64_t wetTailRemaining=0;
  std::atomic<bool> clearMapRequested{false};
  std::atomic<int> editIndex{-1};
  std::atomic<double> editDelta{0};
  std::atomic<bool> editRemove{false};
  std::atomic<int> previewRequested{-1};
  int64_t previewRemaining=0, previewTotal=0, previewStartSample=0, previewSourceStart=0;
  size_t peakSamples=0;
  float peak=0;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SkellSilenceAudioProcessor)
};
