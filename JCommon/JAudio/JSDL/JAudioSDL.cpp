#include "JCommonPch.h"

using namespace J;
using namespace J::AUDIO;

JAudioSDL::JAudioSDL()
{
}
JAudioSDL::~JAudioSDL()
{
}
void JAudioSDL::Init(const std::string name)
{
	JBase::Init(name);
	// Set up the audio stream
	//TODO Expose frequency, channels and chunksize
	int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
	if (result < 0)
	{
		LOG_INFO(0, "Unable to open audio: %s\n", SDL_GetError());
		return;
	}
	result = Mix_AllocateChannels(4);
	if (result < 0)
	{
		LOG_INFO(0, "Unable to allocate mixing channels: %s\n", SDL_GetError());
		return;
	}
}
void JAudioSDL::Clear()
{
	JBase::Clear();
	Mix_CloseAudio();
	Mix_Quit();
}
void JAudioSDL::Update()
{
}
void JAudioSDL::Activate()
{
	JBase::Activate();
}
void JAudioSDL::Deactivate()
{
	JBase::Deactivate();
}