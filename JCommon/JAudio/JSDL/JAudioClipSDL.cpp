#include "JCommonPch.h"

using namespace J;
using namespace J::AUDIO;

JAudioClipSDL::JAudioClipSDL()
{
}
JAudioClipSDL::~JAudioClipSDL()
{
}
void  JAudioClipSDL::Init(const std::string name, const std::string filepath)
{
	mFilePath = filepath;
	Init(name);
}
static void forwardCallback(void *userdata, Uint8 *stream, int len)
{
	static_cast<JAudioClipSDL*>(userdata)->OnCallback(stream, len);
}
void  JAudioClipSDL::OnCallback(Uint8 *stream, int len)
{
	if (mAudioLen == 0)
		return;

	len = ((unsigned int)len > mAudioLen ? mAudioLen : len);
	//SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	SDL_MixAudio(stream, mAudioPos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	mAudioPos += len;
	mAudioLen -= len;
}
void JAudioClipSDL::Init(const std::string name)
{
	JAudioClipImpl::Init(name);
	// local variables
	Uint32 wav_length; // length of our sample
	Uint8 *wav_buffer; // buffer containing our audio file
	SDL_AudioSpec wav_spec; // the specs of our piece of music
	/* Load the WAV */
	std::string path = gJEngine.GetSettings()->DataFolder;
	path += mFilePath;
	// the specs, length and buffer of our wav are filled
	if (SDL_LoadWAV(path.c_str(), &wav_spec, &wav_buffer, &wav_length) == NULL)
	{
		return;
	}
	// set the callback function
	wav_spec.callback = forwardCallback;
	wav_spec.userdata = this;
	// set our global static variables
	mAudioPos = wav_buffer; // copy sound buffer
	mAudioLen = wav_length; // copy file length
	/* Open the audio device */
	if (SDL_OpenAudio(&wav_spec, NULL) < 0) 
	{
		LOG_WARNING(0, "Couldn't open audio: %s\n", SDL_GetError());
	}
}
void JAudioClipSDL::Clear()
{
	JAudioClipImpl::Clear();
	Stop();
	SDL_CloseAudio();
}
void JAudioClipSDL::Update()
{
	JAudioClipImpl::Update();
}
void JAudioClipSDL::Play()
{
	JAudioClipImpl::Play();
	SDL_PauseAudio(0);
}
void JAudioClipSDL::Pause()
{
	JAudioClipImpl::Pause();
}
void JAudioClipSDL::Stop()
{
	JAudioClipImpl::Stop();
}
void JAudioClipSDL::Activate()
{
	JAudioClipImpl::Activate();
}
void JAudioClipSDL::Deactivate()
{
	JAudioClipImpl::Deactivate();
}