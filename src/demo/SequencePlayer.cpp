#include "SequencePlayer.h"

SequencePlayer::SequencePlayer(Sequence* sequence) :
	playbackOffset(0)
{
	this->sequence = sequence;
}

void SequencePlayer::RenderSamples(float* samples, int count)
{
	sequence->BlitSequence(samples, (unsigned)count, (unsigned)playbackOffset);
	playbackOffset += count;
}

void SequencePlayer::SetSeekPosition(int seekPos)
{
	playbackOffset = seekPos;
}