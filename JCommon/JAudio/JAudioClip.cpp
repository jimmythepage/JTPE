#include "JCommonPch.h"

using namespace J;
using namespace J::AUDIO;

JAudioClip::JAudioClip()
{
}
JAudioClip::~JAudioClip()
{
}
void  JAudioClip::Init(const std::string name, const std::string filepath)
{
	Init(name);
	if (!mAudioClipImpl)
	{
#ifdef __SDL__
		mAudioClipImpl = new JAudioClipSDL();
#else
		mAudioClipImpl = new JAudioClipImpl();
#endif
		mAudioClipImpl->Init(name,filepath);
	}
}
void JAudioClip::Init(const std::string name)
{
	JBase::Init(name);
}
void JAudioClip::Clear()
{
	JBase::Clear();
	if (mAudioClipImpl)
	{
		mAudioClipImpl->Clear();
		delete mAudioClipImpl;
		mAudioClipImpl = NULL;
	}
}
int JAudioClip::GetVolume()
{
	return mAudioClipImpl->GetVolume();
}
void  JAudioClip::SetVolume(int volume)
{
	mAudioClipImpl->SetVolume(volume);
}
void JAudioClip::SetLoop(bool loop)
{
	mAudioClipImpl->SetLoop(loop);
}
bool JAudioClip::GetLoop()
{
	return mAudioClipImpl->GetLoop();
}
bool JAudioClip::IsPlaying()
{
	return mAudioClipImpl->IsPlaying();
}
void JAudioClip::Play()
{
	mAudioClipImpl->Play();
}
void JAudioClip::Pause()
{
	mAudioClipImpl->Pause();
}
void JAudioClip::Stop()
{
	mAudioClipImpl->Stop();
}
void JAudioClip::Update()
{
	mAudioClipImpl->Update();
}
void JAudioClip::Activate()
{
	JBase::Activate();
	mAudioClipImpl->Activate();
}
void JAudioClip::Deactivate()
{
	JBase::Deactivate();
	mAudioClipImpl->Deactivate();
}