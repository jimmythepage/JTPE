#include "JCommonPch.h"

using namespace J;
using namespace J::BASE;
using namespace J::AUDIO;


JAudioManager::JAudioManager()
{
}
JAudioManager::~JAudioManager()
{
	
}
JAudioManager & JAudioManager::GetSingleton()
{
	static JAudioManager _singleton;
	return _singleton;
}
void JAudioManager::Init(const std::string name)
{
	for (size_t i = 0; i < MAX_CHANNELS; i++)
	{
		mAudioChannelsPairs[i] = false;
	}
	JBase::Init(name);
	if (!mAudio)
	{
#if defined(__SDL__)
		mAudio = new JAudioSDL();
		mAudio->Init("mAudio SDL");
#else
		mAudio = new JAudio();
		mAudio->Init("mAudio Generic");
#endif
	}
}
int JAudioManager::GetFreeAudioChannel()
{
	int audioChannel = -2;
	for (int i = 0; i < MAX_CHANNELS; i++)
	{
		if (mAudioChannelsPairs[i]==false)
		{
			mAudioChannelsPairs[i] = true;
			audioChannel = i;
			break;
		}
	}
	return audioChannel;
}
void JAudioManager::ReleaseAudioChannel(int channel)
{
	mAudioChannelsPairs[channel] = false;
}
void JAudioManager::Clear()
{
	JBase::Clear();
	if (mAudio)
	{
		mAudio->Clear();
		delete mAudio;
		mAudio = NULL;
	}
}
void JAudioManager::Update()
{
	mAudio->Update();
}
void JAudioManager::Activate()
{
	JBase::Activate();
	mAudio->Activate();
	LOG_INFO(0, "%s is Activated\n", mName.c_str());
}
void JAudioManager::Deactivate()
{
	JBase::Deactivate();
	mAudio->Deactivate();
	LOG_INFO(0, "%s is Deactivated\n", mName.c_str());
}