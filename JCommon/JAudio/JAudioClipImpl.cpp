#include "JCommonPch.h"

using namespace J;
using namespace J::AUDIO;

JAudioClipImpl::JAudioClipImpl():mIsPlaying (false),mLoop(false), mChannel(-2), mVolume(128)
{
}
JAudioClipImpl::~JAudioClipImpl()
{
}
void  JAudioClipImpl::Init(const std::string name, const std::string filepath)
{
	Init(name);
	mChannel=gJAudioManager.GetFreeAudioChannel();
}
void JAudioClipImpl::Init(const std::string name)
{
	JBase::Init(name);
}
void JAudioClipImpl::Clear()
{
	JBase::Clear();
	gJAudioManager.ReleaseAudioChannel(mChannel);
	mChannel = -2;
}
void JAudioClipImpl::Play()
{
	mIsPlaying = true;
}
void JAudioClipImpl::Pause()
{
	mIsPlaying = false;
}
void JAudioClipImpl::Stop()
{
	mIsPlaying = false;
}
void JAudioClipImpl::SetVolume(int volume)
{
	mVolume = volume;
}
int JAudioClipImpl::GetVolume()
{
	return mVolume;
}
void JAudioClipImpl::Update()
{
}
void JAudioClipImpl::Activate()
{
	JBase::Activate();
}
void JAudioClipImpl::Deactivate()
{
	JBase::Deactivate();
}