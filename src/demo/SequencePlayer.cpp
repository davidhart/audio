#include "SequencePlayer.h"

SequencePlayer::SequencePlayer(Sequence* sequence) :
	playbackOffset(0),
	tempo(1.0f)
{
	this->sequence = sequence;
}

void SequencePlayer::RenderSamples(float* samples, int count)
{
	sequence->BlitSequence(samples, (unsigned)count, (unsigned)playbackOffset, tempo);
	playbackOffset += count;
}

void SequencePlayer::SetSeekPosition(int seekPos)
{
	playbackOffset = seekPos;
}

void SequencePlayer::SetTempo(float tempo)
{
	this->tempo = tempo;
}

float SequencePlayer::GetTempo()
{
	return tempo;
}