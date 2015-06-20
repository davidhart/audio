#pragma once

#include <vector>

class WaveTable;

struct Note
{
	unsigned StartOffset;
	unsigned char Key;
    float Volume;
};

class Track
{

private:
	
	std::vector<Note> _notes;

	WaveTable* _waveTable;
    
    unsigned _length;
    
    float _volume;

public:

    Track();
    
    void SetLength(unsigned length);
    unsigned GetLength() const;
    
	void SetWaveBank(WaveTable* waveTable);

	void AddNote(Note note);
    Note* GetNotes();
    unsigned NumNotes();
    
	void ClearNotes();

	void BlitTrack(float* buffer, unsigned bufferSize, unsigned offset, float tempo);
    
    void SetVolume(float volume);
};