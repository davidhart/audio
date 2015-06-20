#include "audio.hpp"
#include "SequencePlayer.h"
#include "XAudio2Player.h"

void OpenConsole();

int main(char** argv, int argc)
{
	XAudio2Player audioPlayer;

	Sequence sequence;
	WaveTableSine wavetable;
	EffectPeakCompressor compressor;
	
	Track* track = sequence.AddTrack("debug");
    track->SetWaveBank(&wavetable);
	track->SetVolume(1.0f);

    for (unsigned i = 0; i < 400; ++i)
    {
		Note n;
        n.Key = i % wavetable.GetNumNotes();
        n.StartOffset = i * AUDIO_SAMPLE_RATE / 4;
		n.Volume = 1.0f;
		track->AddNote(n);
    }

	SequencePlayer sequencePlayer(&sequence);
	sequence.AddEffect(&compressor);
	audioPlayer.SetRenderCallback(&sequencePlayer);
	audioPlayer.Start();

	while ( true ) Sleep(1) ;
	
	return 0;
}