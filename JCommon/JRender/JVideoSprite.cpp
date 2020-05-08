#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::RENDER;
using namespace J::GAME;

JVideoSprite::JVideoSprite(): 
mLoop(false), mIsPlaying(false), mFPS(0)
{
	if (!mRenderable)
	{
#ifdef __J_SIMPLE2D__
		mRenderable = new JSpriteSimple2D();
#elif defined(__SFML__)
		mRenderable = new JSpriteSFML();
#elif defined(__SDL__)
		mRenderable = new JVideoSpriteSDL();
#else
		mRenderable = new JRenderable();
#endif
	}
}
JVideoSprite::~JVideoSprite()
{
	delete mRenderable;
	mRenderable = NULL;
}
void JVideoSprite::PlayVideo()
{
	mIsPlaying = true;
}
void JVideoSprite::PauseVideo()
{
	mIsPlaying = false;
}
void JVideoSprite::StopVideo()
{
	mIsPlaying = false;
}
void JVideoSprite::Init(const std::string filepath, const std::string name, JRenderableProperties properties)
{
	Init(name);
	mRenderable->Init(filepath, name + " renderable", properties);
	mFrameTimer.Init(name + " anim timer");
	mFPS = 30;
	mLoop = true;
	float timeSpeed = 1.f / mFPS * 1000;
	mFrameTimer.SetTime((long long)timeSpeed);
	mFrameTimer.SetCallback(std::bind(&JVideoSprite::FrameTimerCallback, this));
	mFrameTimer.StartTimer(true, true);
}
void JVideoSprite::Init(const std::string name)
{
	JBase::Init(name);
}
void JVideoSprite::Clear()
{
	JBase::Clear();
	Deactivate();
	mFrameTimer.Clear();
	mRenderable->Clear();
}
void JVideoSprite::Activate()
{
	JBase::Activate();
	mRenderable->Activate();
	gJRenderManager.GetRenderer()->AddRenderable(mRenderable);
	if (mIsPlaying)
	{
		PlayVideo();
	}
}
void JVideoSprite::FrameTimerCallback()
{
#if defined(__SDL__)
	((JVideoSpriteSDL*)mRenderable)->UpdateVideoFrame();
#endif
}
void JVideoSprite::Update()
{
	JBase::Update();
	mFrameTimer.Update();
}
void JVideoSprite::Deactivate()
{
	JBase::Deactivate();
	gJRenderManager.GetRenderer()->RemoveRenderable(mRenderable);
	mRenderable->Deactivate();
	mFrameTimer.StopTimer();
}