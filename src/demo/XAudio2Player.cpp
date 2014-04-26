#include <Windows.h>
#include "XAudio2Player.h"
#include "IAudioRenderCallback.h"

XAudio2Player::XAudio2Player() :
	renderCallback(nullptr),
	xAudio2(nullptr),
	masteringVoice(nullptr),
	sourceVoice(nullptr)
{
	blitBuffer.resize(512);

	XAUDIO2_DEBUG_CONFIGURATION xdbg;
	xdbg.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS | XAUDIO2_LOG_INFO;
	xdbg.BreakMask = 0;
	xdbg.LogThreadID = false;
	xdbg.LogFileline = false;
	xdbg.LogFunctionName = true;
	xdbg.LogTiming = false;

	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	HRESULT hr = XAudio2Create( &xAudio2,
							    0,
								XAUDIO2_DEFAULT_PROCESSOR );

	xAudio2->SetDebugConfiguration( &xdbg );

	hr = xAudio2->CreateMasteringVoice( &masteringVoice );
	
	WAVEFORMATEX pcmwf;
	pcmwf.cbSize = 0;
	pcmwf.wBitsPerSample = 32;
	pcmwf.nAvgBytesPerSec = 44100*4;
	pcmwf.nBlockAlign = 4;
	pcmwf.nChannels = 1;
	pcmwf.nSamplesPerSec = 44100;
	pcmwf.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;

	xAudio2->CreateSourceVoice( &sourceVoice, (WAVEFORMATEX*)&pcmwf, 0, 2.0F, this );

	xAudio2Buffer.Flags = 0;
	xAudio2Buffer.LoopBegin = 0;
	xAudio2Buffer.PlayBegin = 0;
	xAudio2Buffer.pAudioData = (BYTE*)blitBuffer.data();

	xAudio2Buffer.AudioBytes = 4096;
	xAudio2Buffer.PlayLength = 512;
	xAudio2Buffer.LoopLength = 0;
	xAudio2Buffer.LoopCount = 0;
}

XAudio2Player::~XAudio2Player()
{
	sourceVoice->DestroyVoice();
	masteringVoice->DestroyVoice();
	xAudio2->Release();
	CoUninitialize();
}

void XAudio2Player::Start()
{
	// Get a couple of blocks ahead
	RenderBuffer();
	RenderBuffer();

	sourceVoice->Start();
}

void XAudio2Player::Stop()
{
	sourceVoice->Stop();
}

void XAudio2Player::SetRenderCallback(IAudioRenderCallback* renderCallback)
{
	this->renderCallback = renderCallback;
}

void STDMETHODCALLTYPE XAudio2Player::OnBufferStart(void* pBufferContext)
{
	RenderBuffer();
}

void STDMETHODCALLTYPE XAudio2Player::OnBufferEnd(void* pBufferContext)
{

}

void STDMETHODCALLTYPE XAudio2Player::OnLoopEnd(void* pBufferContext)
{

}

void STDMETHODCALLTYPE XAudio2Player::OnStreamEnd()
{

}

void STDMETHODCALLTYPE XAudio2Player::OnVoiceError(void *pBufferContext, HRESULT error)
{

}


void STDMETHODCALLTYPE XAudio2Player::OnVoiceProcessingPassStart(UINT32 BytesRequired)
{

}

void STDMETHODCALLTYPE XAudio2Player::OnVoiceProcessingPassEnd()
{

}

void XAudio2Player::RenderBuffer()
{
	if ( renderCallback == nullptr )
	{
		sourceVoice->Stop();
		return;
	}

	renderCallback->RenderSamples((float*)&blitBuffer[0], 512);

	sourceVoice->SubmitSourceBuffer(&xAudio2Buffer);
}
