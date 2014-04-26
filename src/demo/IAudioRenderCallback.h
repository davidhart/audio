#pragma once

class IAudioRenderCallback
{
public:

	virtual void RenderSamples(float* samples, int count) = 0;

};
