#include "wavetable.h"
#include "config.h"

#include <cassert>
#include <cmath>

// TODO: tidy
const int numNotes = 7;
const float frequencies[numNotes] = { 261.63f, 293.66f, 329.63f, 349.23f, 392.00f, 415.30f, 440.0f };
const float noteDuration = 0.5f; // seconds
const unsigned noteSampleLength = (unsigned)(noteDuration * AUDIO_SAMPLE_RATE);
const unsigned bufferSize = noteSampleLength * numNotes;

WaveTable::WaveTable()
{	
	_sourceBufferData = new float[bufferSize];
	_waveTable = new float*[numNotes];
	
	for (unsigned i = 0; i < numNotes; ++i)
	{
		_waveTable[i] = _sourceBufferData + i * noteSampleLength;
	}

	const float freuencyToSampleRateRatio =  AUDIO_SAMPLE_RATE / (2.0f * PI);

	for (unsigned int i = 0; i < numNotes; ++i)
	{
		const float sampleToAngle = frequencies[i] / freuencyToSampleRateRatio;

		for (unsigned j = 0; j < noteSampleLength; ++j)
		{
			_waveTable[i][j] = sin(j * sampleToAngle);
		}
	}
}

void WaveTable::BlitKey(float* buffer, unsigned bufferSize, unsigned offset, unsigned key)
{
	assert( offset + bufferSize <= noteSampleLength );
	assert(key < numNotes);

	float* wave = _waveTable[key];

	// TODO: copy util function
	for (unsigned int i = 0; i < bufferSize; ++i)
	{
		buffer[i] = wave[offset++];
	}
}

unsigned WaveTable::GetKeyLength(unsigned key)
{
	return noteSampleLength;
}