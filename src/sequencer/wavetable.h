#pragma once

class WaveTable
{

private: 

	float* _sourceBufferData;
	float** _waveTable;

public:

	WaveTable();

	unsigned GetKeyLength(unsigned key);
	void BlitKey(float* buffer, unsigned bufferSize, unsigned offsetm, unsigned key);

};