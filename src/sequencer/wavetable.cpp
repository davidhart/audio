#include "wavetable.hpp"
#include "config.hpp"

#include <cassert>
#include <cmath>
#include <algorithm>

// TODO: tidy

void WaveTable::BlitKey(float* buffer, unsigned bufferSize, unsigned offset, unsigned key, float volume)
{
	assert( offset + bufferSize <= GetKeyLength(key) );
	assert(key < GetNumNotes());
    
	const float* wave = GetKeyData(key);
    
	for (unsigned int i = 0; i < bufferSize; ++i)
	{
		buffer[i] = wave[offset++] * volume;
	}
}

const float frequencies[] = { 
	/*
	16.35f,
	17.32f,
	18.35f,
	19.45f,
	20.6f,
	21.83f,
	23.12f,
	24.5f,
	25.96f,
	27.5f,
	29.14f,
	30.87f,
	32.7f,
	34.65f,
	36.71f,
	38.89f,
	41.2f,
	43.65f,
	46.25f,
	49.0f,
	51.91f,
	55.0f,
	58.27f,
	61.74f,*/
	65.41f,
	69.3f,
	73.42f,
	77.78f,
	82.41f,
	87.31f,
	92.5f,
	98.0f,
	103.83f,
	110.0f,
	116.54f,
	123.47f,
	130.81f,
	138.59f,
	146.83f,
	155.56f,
	164.81f,
	174.61f,
	185.0f,
	196.0f,
	207.65f,
	220.0f,
	233.08f,
	246.94f,
	261.63f,
	277.18f,
	293.66f,
	311.13f,
	329.63f,
	349.23f,
	369.99f,
	392.0f,
	415.3f,
	440.0f,
	466.16f,
	493.88f,
	523.25f,
	554.37f,
	587.33f,
	622.25f,
	659.25f,
	698.46f,
	739.99f,
	783.99f,
	830.61f,
	880.0f,
	932.33f,
	987.77f,
	1046.5f,
	1108.73f,
	1174.66f,
	1244.51f,
	1318.51f,
	1396.91f,
	1479.98f,
	1567.98f,
	1661.22f,
	1760.0f,
	1864.66f,
	1975.53f,
	2093.0f,
	2217.46f,
	2349.32f,
	2489.02f,
	2637.02f,
	2793.83f,
	2959.96f,
	3135.96f,
	3322.44f,
	3520.0f,
	3729.31f,
	3951.07f,
	4186.01f,
	4434.92f,
	4698.63f,
	4978.03f,
	5274.04f,
	5587.65f,
	5919.91f,
	6271.93f,
	6644.88f,
	7040.0f,
	7458.62f,
	7902.13f
};

const int numNotes = sizeof(frequencies)/sizeof(float);
const float noteDuration = 0.5f; // seconds
const unsigned noteSampleLength = (unsigned)(noteDuration * AUDIO_SAMPLE_RATE);
const unsigned bufferSize = noteSampleLength * numNotes;

WaveTableSine::WaveTableSine()
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

		for (int j = noteSampleLength - 1; j > 0; j--)
		{
			if (std::abs(_waveTable[i][j]) < 0.01f)
				break;

			_waveTable[i][j] = 0.0f;
		}
	}
}

WaveTableSine::~WaveTableSine()
{
    delete [] _sourceBufferData;
    delete [] _waveTable;
}

unsigned WaveTableSine::GetKeyLength(unsigned key)
{
	return noteSampleLength;
}

const float* WaveTableSine::GetKeyData(unsigned key)
{
    return _waveTable[key];
}

unsigned WaveTableSine::GetNumNotes()
{
    return numNotes;
}