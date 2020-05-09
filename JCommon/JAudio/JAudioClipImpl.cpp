#include "JCommonPch.h"

using namespace J;
using namespace J::AUDIO;

JAudioClipImpl::JAudioClipImpl():mIsPlaying (false),mLoop(false)
{
}
JAudioClipImpl::~JAudioClipImpl()
{
}
void  JAudioClipImpl::Init(const std::string name, const std::string filepath)
{
	Init(name);
}
void JAudioClipImpl::Init(const std::string name)
{
	JBase::Init(name);
}
void JAudioClipImpl::Clear()
{
	JBase::Clear();
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