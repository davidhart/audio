#include "buffer_utils.hpp"

void BufferUtils::ZeroBuffer(float* buffer, unsigned bufferSize)
{
	for (unsigned i = 0; i < bufferSize; ++i)
	{
		buffer[i] = 0.0f;
	}
}

void BufferUtils::MixBuffers(float* source, float* dest, unsigned bufferSize)
{
	for (unsigned i = 0; i < bufferSize; ++i)
	{
		dest[i] += source[i];
	}
}

void BufferUtils::RampUp(float* buffer, unsigned bufferSize)
{
    for (unsigned i = 0; i < bufferSize; ++i)
    {
        float vol = i / (float)bufferSize;
        
        buffer[i] *= vol;
    }
}

void BufferUtils::RampDown(float* buffer, unsigned bufferSize)
{
    for (unsigned i = 0; i < bufferSize; ++i)
    {
        float vol = 1.0f - i / (float)bufferSize;
        
        buffer[i] *= vol;
    }
}