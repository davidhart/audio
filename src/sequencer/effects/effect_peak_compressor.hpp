#pragma once

#include "../effect.hpp"

class EffectPeakCompressor : public Effect
{
public:
    EffectPeakCompressor();
    virtual void Process(float* buffer, unsigned bufferSize, unsigned offset, float tempo);
    
    bool Enabled;
    
private:
    float		fFs;				// Sample rate
    float 		onebyfFS;           // One over sample rate
    
    // Arrays for delay lines
    float 		kneeRecursive[2];
    float 		attackRecursive[2];
    float 		releaseRecursive[2];
    
    // Values
    float 		attack;
    float 		release;
    float 		ratio;
    float 		threshold;
    float 		knee;
    float 		makeupGain;
    
    float 		kneeCoeffs;
    float 		kneeCoeffsMinus;
    float 		attackCoeffs;
    float 		attackCoeffsMinus;
    float 		releaseCoeff;
    float 		releaseCoeffMinus;
};