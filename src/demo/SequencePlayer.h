#pragma once

#include "IAudioRenderCallback.h"
#include "audio.hpp"

class SequencePlayer : public IAudioRenderCallback
{
public:
	SequencePlayer(Sequence* sequence);
	void RenderSamples(float* samples, int count);
	void SetSeekPosition(int offset);
	void SetTempo(float tempo);
	float GetTempo();

private:
	Sequence* sequence;
	int playbackOffset;
	float tempo;
};
