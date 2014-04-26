#pragma once

class Voice
{

private:
	
	const float*			_sampleSource;
	unsigned				_sampleLength;

	float					_playbackStoppingVolume;

public:

	Voice(const float* sample, unsigned length);

	void StopPlayback();
	bool IsFinished();

	void BlitVoice(float* buffer, unsigned bufferSize, unsigned offset);

private:

	Voice();
	
	void CopySamples(float* buffer, unsigned bufferSize);
	void Voice::CopySamplesDecay(float* buffer, unsigned bufferSize);

};