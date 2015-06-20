#include "../audio.hpp"
#include "effect_peak_compressor.hpp"

#include <cmath>

// Effect implementation is a direct port of https://github.com/twobigears/tb_peakcomp provided with MIT License 18/04/2015

using namespace std;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

float dbToLinear(float db)
{
    return (float)pow(10, db * 0.05f);
}

EffectPeakCompressor::EffectPeakCompressor()
{
    Enabled = true;
    
    for (int i = 0; i < 2; i++)
    {
        kneeRecursive[i] = 0.f;
        attackRecursive[i] = 0.f;
        releaseRecursive[i] = 0.f;
    }
    
    // Init sample rate
    fFs = AUDIO_SAMPLE_RATE;
    onebyfFS = 1.f / fFs;
    
    // Init Parameters
    attack = 0.000001f;             // duration of attack, 0.000001 or larger for slower attack
    release = 0.004f;            // duration of release, 0.000001 or larger for slower release
    ratio = 1.0f / 10.0f;            // ratio of original signal to clip, should be <= 1.0f & > 0
    threshold = dbToLinear(0.0f);   // db threshold to trigger compression
    knee = 0.0f;                    // smoothness of transition, 0 (hard) to 0.02 (smooth) (probably can be larger)
    makeupGain = dbToLinear(0.0f);  // additional signal gain
    
    // derive params
    kneeCoeffs = expf(0.f - (onebyfFS / knee));
    kneeCoeffsMinus = 1.f - kneeCoeffs;
    attackCoeffs = expf(0.f - (onebyfFS / attack));
    attackCoeffsMinus = 1.f - attackCoeffs;
    releaseCoeff = expf(0.f - (onebyfFS / release));
    releaseCoeffMinus = 1.f - releaseCoeff;
}

void EffectPeakCompressor::Process(float* buffer, unsigned bufferSize, unsigned offset, float tempo)
{
    if (Enabled == false)
    {
        return;
    }
    
    // DSP loop
    for (unsigned i=0; i<bufferSize; i++)
	{
        
        float input = buffer[i];
        
        // L+R sum
        float peakEnv = fabsf(input);
        //release recursive
        releaseRecursive[0] = (releaseCoeffMinus * peakEnv) + (releaseCoeff * MAX(peakEnv, releaseRecursive[1]));
        //attack recursive
        attackRecursive[0] = ((attackCoeffsMinus * releaseRecursive[0]) + (attackCoeffs * attackRecursive[1]));
        //knee smoothening and gain reduction
        kneeRecursive[0] = (kneeCoeffsMinus * MAX(MIN(((threshold + (ratio * (attackRecursive[0] - threshold))) / attackRecursive[0]), 1.f), 0.f)) + (kneeCoeffs * kneeRecursive[1]);
        
        buffer[i] = input * kneeRecursive[0] * makeupGain;
        
        releaseRecursive[1] = releaseRecursive[0];
        attackRecursive[1] = attackRecursive[0];
        kneeRecursive[1] = kneeRecursive[0];
    }
}