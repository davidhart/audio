#include "track.h"
#include "wavetable.h"
#include "buffer_utils.h"
#include <cassert>

void Track::SetWaveBank(WaveTable* waveTable)
{
	_waveTable = waveTable;
}

void Track::AddNote(Note note)
{
	_notes.push_back(note);
}

void Track::ClearNotes()
{
	_notes.clear();
}

void Track::BlitTrack(float* buffer, unsigned bufferSize, unsigned offset)
{
	// TODO: scratch buffer re-write
	float tempBuffer[512];
	assert (bufferSize <= 512);

	BufferUtils::ZeroBuffer(tempBuffer, 512);

	for (unsigned i = 0; i < _notes.size(); ++i)
	{
		const Note& note = _notes[i];

		unsigned keyLength = _waveTable->GetKeyLength(note.Key);

		unsigned noteStart = note.StartOffset;
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

				BufferUtils::ZeroBuffer(buffer, leadIn);
			}

			// If note ends before block end
			if ( noteEnd < offset + bufferSize )
			{
				unsigned leadOut = offset + bufferSize - noteEnd;

				noteDurationInBlock -= leadOut;

				BufferUtils::ZeroBuffer(buffer + bufferSize - leadOut, leadOut);
			}

			_waveTable->BlitKey(tempBuffer + noteStartSampleInBlock, noteDurationInBlock, offset + noteStartSampleInBlock - note.StartOffset, note.Key);
			
			BufferUtils::MixBuffers(tempBuffer, buffer, bufferSize);
		}
	}
}