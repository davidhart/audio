#include "track.hpp"
#include "wavetable.hpp"
#include "buffer_utils.hpp"

Track::Track() :
    _volume(1.0f),
    _length(0),
    _waveTable(NULL)
{
    
}

void Track::SetWaveBank(WaveTable* waveTable)
{
	_waveTable = waveTable;
}

void Track::AddNote(Note note)
{
	_notes.push_back(note);
}

Note* Track::GetNotes()
{
    return _notes.data();
}

unsigned Track::NumNotes()
{
    return (unsigned)_notes.size();
}

void Track::ClearNotes()
{
	_notes.clear();
}

void Track::BlitTrack(float* buffer, unsigned bufferSize, unsigned offset, float tempo)
{
	// TODO: scratch buffer re-write
	float tempBuffer[1024];

	BufferUtils::ZeroBuffer(tempBuffer, 1024);

	for (unsigned i = 0; i < _notes.size(); ++i)
	{
		const Note& note = _notes[i];

		unsigned keyLength = _waveTable->GetKeyLength(note.Key);

		unsigned noteStart = (unsigned)(note.StartOffset * tempo);
		unsigned noteEnd = noteStart + keyLength;

		// Mix the key if it's playback region overlaps the current segment of samples
		if ( noteStart < offset + bufferSize && noteEnd > offset)
		{
			unsigned noteStartSampleInBlock = 0;
			unsigned noteDurationInBlock = bufferSize;

			// TODO: simplify lead in/out logic

			// If note starts after block start
			if ( noteStart > offset )
			{
				unsigned leadIn = noteStart - offset;

				noteStartSampleInBlock += leadIn;
				noteDurationInBlock -= leadIn;

				BufferUtils::ZeroBuffer(tempBuffer, leadIn);
			}

			// If note ends before block end
			if ( noteEnd < offset + bufferSize )
			{
				unsigned leadOut = offset + bufferSize - noteEnd;

				noteDurationInBlock -= leadOut;

				BufferUtils::ZeroBuffer(tempBuffer + bufferSize - leadOut, leadOut);
			}

			_waveTable->BlitKey(tempBuffer + noteStartSampleInBlock, noteDurationInBlock, offset + noteStartSampleInBlock - noteStart, note.Key, note.Volume * _volume);
			
			BufferUtils::MixBuffers(tempBuffer, buffer, bufferSize);
		}
	}
}

void Track::SetLength(unsigned length)
{
    _length = length;
}

unsigned Track::GetLength() const
{
    return _length;
}

void Track::SetVolume(float volume)
{
    _volume = volume;
}