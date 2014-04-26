#pragma once

#include <vector>

#include "voice.h"

class WaveTable;

struct Note
{
	unsigned StartOffset;
	unsigned char Key;
};

class Track
{

private:
	
	std::vector<Note> _notes;

	unsigned _playbackOffset;

	WaveTable* _waveTable;

public:

	void SetWaveBank(WaveTable* waveTable);

	void AddNote(Note note);
	void ClearNotes();

	void BlitTrack(float* buffer, unsigned bufferSize, unsigned offset);

};