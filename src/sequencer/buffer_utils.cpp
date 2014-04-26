#include "buffer_utils.h"

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