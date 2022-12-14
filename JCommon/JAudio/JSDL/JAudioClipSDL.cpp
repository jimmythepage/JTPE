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
	JAudioClipImpl::Init(name, filepath);
	mFilePath = filepath;
	Init(name);
}
void JAudioClipSDL::Init(const std::string name)
{
	JAudioClipImpl::Init(name);
	// Load waveforms
	std::string path = gJEngine.GetSettings()->DataFolder;
	path += mFilePath;
	_clipSample = Mix_LoadWAV(path.c_str());
	if (_clipSample == NULL)
	{
		LOG_INFO(0, "Unable to load wave file: %s\n", path.c_str());
	}
}
void JAudioClipSDL::Clear()
{
	Stop();
	JAudioClipImpl::Clear();
	Mix_FreeChunk(_clipSample);
}
void JAudioClipSDL::Update()
{
	JAudioClipImpl::Update();
}
void JAudioClipSDL::Play()
{
	JAudioClipImpl::Play();
	if (!Mix_Paused(mChannel))
	{
		Mix_PlayChannel(mChannel, _clipSample, mLoop ? -1 : 0);
	}
	else
	{
		Mix_Resume(mChannel);
	}
}
void JAudioClipSDL::Pause()
{
	JAudioClipImpl::Pause();
	Mix_Pause(mChannel);
}
void JAudioClipSDL::Stop()
{
	JAudioClipImpl::Stop();
	Mix_HaltChannel(mChannel);
}
void JAudioClipSDL::SetVolume(int volume)
{
	JAudioClipImpl::SetVolume(volume);
	Mix_Volume(mChannel, volume);
}
int JAudioClipSDL::GetVolume()
{
	return JAudioClipImpl::GetVolume();
}
void JAudioClipSDL::Activate()
{
	JAudioClipImpl::Activate();
}
void JAudioClipSDL::Deactivate()
{
	JAudioClipImpl::Deactivate();
}