#pragma once
#include "InstrumentContext.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
namespace skell::dsp {
class Impact {
public:
 void setChannel(int channel) noexcept {
   initialSeed=channel==0?0x673892abu:0x2c1b3c6du;
   seed=initialSeed;
 }
 void prepare(double sampleRate) noexcept {
   sr=std::max(8000.0,sampleRate);
   glideRate=std::exp(float(-1.0/(sr*0.045)));
   clickRate=std::exp(float(-110.0/sr));
   cachedDecay=-1.0f;
   reset();
 }
 void reset() noexcept {
   phase=0.0f; glide=bodyEnvelope=clickEnvelope=1.0f;
   lastAge=-1.0; seed=initialSeed;
 }
 float process(const GapContext& c,float pitch,float decay,float click) noexcept {
   const double age=c.time;
   if(age<0.0 || age>c.sampleRate*2.0) return 0.0f;
   // The sub pitch drop and exponential envelopes are recursive rather than
   // evaluated using three exp() calls for every sample. Restart after seeks.
   if(lastAge<0.0 || age<lastAge || age-lastAge>1.5) {
     phase=0.0f;glide=bodyEnvelope=clickEnvelope=1.0f;
   }
   lastAge=age;
   if(decay!=cachedDecay) {
     cachedDecay=decay;
     bodyRate=std::exp(float(-(2.0+double(decay)*10.0)/sr));
   }
   const float f=35.0f+std::clamp(pitch,0.0f,1.0f)*150.0f*glide;
   phase+=float(6.2831853071795864769*f/sr);
   if(phase>6.2831853071795864769f)phase-=6.2831853071795864769f;
   const float out=0.48f*std::sin(phase)*bodyEnvelope +
                   0.08f*noise(seed)*clickEnvelope*std::clamp(click,0.0f,1.0f);
   glide*=glideRate;
   bodyEnvelope*=bodyRate;
   clickEnvelope*=clickRate;
   return out;
 }
private:
 double sr=48000.0,lastAge=-1.0;
 float phase=0.0f,glide=1.0f,bodyEnvelope=1.0f,clickEnvelope=1.0f;
 float glideRate=0.9995f,bodyRate=0.9999f,clickRate=0.997f,cachedDecay=-1.0f;
 uint32_t seed=0x673892abu,initialSeed=0x673892abu;
};
}
