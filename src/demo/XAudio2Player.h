#pragma once

#include <xaudio2.h>
#include <vector>

class IAudioRenderCallback;

class XAudio2Player : public IXAudio2VoiceCallback 
{
public: 
	XAudio2Player();
	~XAudio2Player();

	void SetRenderCallback(IAudioRenderCallback* callback);
	void Start();
	void Stop();

private:

	IAudioRenderCallback* renderCallback;
	IXAudio2* xAudio2;
	IXAudio2MasteringVoice* masteringVoice;
	IXAudio2SourceVoice* sourceVoice;

	XAUDIO2_BUFFER xAudio2Buffer;
	std::vector<float> blitBuffer;

	void STDMETHODCALLTYPE OnBufferStart(void* pBufferContext);
	void STDMETHODCALLTYPE OnBufferEnd(void* pBufferContext);
	void STDMETHODCALLTYPE OnLoopEnd(void* pBufferContext);
	void STDMETHODCALLTYPE OnStreamEnd();
	void STDMETHODCALLTYPE OnVoiceError(void *pBufferContext, HRESULT error);
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 BytesRequired);
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd();

	void RenderBuffer();

};
