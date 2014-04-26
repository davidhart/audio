#pragma once

#include "IAudioRenderCallback.h"
#include "audio.h"

class SequencePlayer : public IAudioRenderCallback
{
public:
	SequencePlayer(Sequence* sequence);
	void RenderSamples(float* samples, int count);
	void SetSeekPosition(int offset);

private:
	Sequence* sequence;
	int playbackOffset;
};
