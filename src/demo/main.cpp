#include "audio.h"
#include "SequencePlayer.h"
#include "XAudio2Player.h"

void OpenConsole();

int main(char** argv, int argc)
{
	XAudio2Player audioPlayer;

	Sequence sequence;
	WaveTable wavetable;
	
	Track* track = sequence.AddTrack();
    track->SetWaveBank(&wavetable);

    for (unsigned i = 0; i < 400; ++i)
    {
		Note n;
        n.Key = i % 7;
        n.StartOffset = i * AUDIO_SAMPLE_RATE / 2;

        track->AddNote(n);
    }

	SequencePlayer sequencePlayer(&sequence);
	audioPlayer.SetRenderCallback(&sequencePlayer);
	audioPlayer.Start();

	while ( true ) Sleep(1) ;
	
	return 0;
}