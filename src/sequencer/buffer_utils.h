#pragma once

class BufferUtils
{

public:

	static void ZeroBuffer(float* buffer, unsigned bufferSize);
	static void MixBuffers(float* source, float* dest, unsigned bufferSize);
};
