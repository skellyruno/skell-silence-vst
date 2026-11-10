#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>

namespace skell::dsp {
struct DetectorSettings {
  float thresholdDb=18.0f, minGapMs=80.0f, maxGapMs=6000.0f;
  float holdMs=45.0f, tailSensitivity=0.5f, armTimeSeconds=0.35f;
};
struct DetectionResult { bool began=false, ended=false, inGap=false; int64_t start=0, end=0; float fast=0, slow=0, threshold=0; };
class GapDetector {
public:
  enum State { Sound=0, Pending, Gap, Recovering };
  void prepare(double sampleRate) noexcept {
    sr=std::max(8000.0,sampleRate);
    fastCoefficient=std::exp(-1.0f/(float(sr)*0.010f));
    slowCoefficient=std::exp(-1.0f/(float(sr)*1.50f));
    cachedThresholdDb=cachedMinGapMs=cachedMaxGapMs=cachedHoldMs=cachedArmTime=-1000.0f;
    reset();
  }
  void reset() noexcept { fastPower=slowPower=previousFast=0; age=0; pending=0; recover=0; armedSamples=0; state=Sound; activeStart=0; }
  State getState() const noexcept { return state; }
  DetectionResult process(float input, int64_t sample, const DetectorSettings& p) noexcept {
    const float squared=input*input;
    fastPower=fastCoefficient*fastPower+(1.0f-fastCoefficient)*squared;
    slowPower=slowCoefficient*slowPower+(1.0f-slowCoefficient)*squared;
    const float fast=std::sqrt(fastPower+1.0e-15f), slow=std::sqrt(slowPower+1.0e-15f);
    // The threshold value usually stays constant for many blocks. Cache the decibel conversion.
    if (p.thresholdDb != cachedThresholdDb) {
      cachedThresholdDb=p.thresholdDb;
      thresholdRatio=std::pow(10.0f,-cachedThresholdDb/20.0f);
    }
    // Make TAIL SENSITIVITY useful: falling tails can enter a gap a little earlier,
    // while rising transients cannot open one. No FFT, locks, or per-sample exp/pow.
    const float decay=std::clamp((previousFast-fast)/std::max(0.0001f,previousFast)*80.0f,0.0f,1.0f);
    const float thresh=std::max(0.000025f,slow*thresholdRatio*(1.0f+0.35f*p.tailSensitivity*decay));
    previousFast=fast;
    // Convert time parameters only when they change, not for every sample.
    if (p.minGapMs!=cachedMinGapMs) {cachedMinGapMs=p.minGapMs;minSamples=std::max<int64_t>(1,int64_t(p.minGapMs*sr/1000.0));}
    if (p.holdMs!=cachedHoldMs) {cachedHoldMs=p.holdMs;holdSamples=std::max<int64_t>(1,int64_t(p.holdMs*sr/1000.0));}
    if (p.maxGapMs!=cachedMaxGapMs || maxSamples<minSamples) {
      cachedMaxGapMs=p.maxGapMs;maxSamples=std::max<int64_t>(minSamples,int64_t(p.maxGapMs*sr/1000.0));
    }
    if (p.armTimeSeconds!=cachedArmTime) {cachedArmTime=p.armTimeSeconds;armSamples=std::max<int64_t>(0,int64_t(sr*p.armTimeSeconds));}
    const bool below=fast<thresh && fast<0.15f;
    const bool hasSignal=slow>0.00020f;
    if (hasSignal && !below) ++armedSamples;
    if (!hasSignal && state==Sound) armedSamples=0;
    const bool canArm=armedSamples>=armSamples;
    DetectionResult r; r.fast=fast; r.slow=slow; r.threshold=thresh;
    switch(state) {
      case Sound:
        if (below && canArm) { state=Pending; pending=1; }
        break;
      case Pending:
        if (!below) { state=Sound; pending=0; }
        else if (++pending>=minSamples) { state=Gap; activeStart=sample-pending+1; age=pending; r.began=true; r.start=activeStart; }
        break;
      case Gap:
        ++age;
        if (age>=maxSamples) { r.ended=true; r.end=sample; r.start=activeStart; state=Sound; armedSamples=0; }
        else if (!below) { state=Recovering; recover=1; }
        break;
      case Recovering:
        ++age;
        if (below) { state=Gap; recover=0; }
        else if (++recover>=holdSamples || age>=maxSamples) { r.ended=true; r.end=sample-recover+1; r.start=activeStart; state=Sound; pending=0; }
        break;
    }
    r.inGap=state==Gap || state==Recovering;
    if (r.inGap) r.start=activeStart;
    return r;
  }
private:
  double sr=44100.0;
  float fastPower=0, slowPower=0, previousFast=0;
  float fastCoefficient=0.998f, slowCoefficient=0.99999f;
  float cachedThresholdDb=-1000.0f,thresholdRatio=0.15f;
  float cachedMinGapMs=-1000.0f,cachedMaxGapMs=-1000.0f,cachedHoldMs=-1000.0f,cachedArmTime=-1000.0f;
  int64_t minSamples=1,holdSamples=1,maxSamples=1,armSamples=0;
  int64_t age=0,pending=0,recover=0,armedSamples=0,activeStart=0;
  State state=Sound;
};
}
