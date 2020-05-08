#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::RENDER;
using namespace J::GAME;

JVideoSprite::JVideoSprite(): 
mLoop(false), mIsPlaying(false)
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
}
void JVideoSprite::Init(const std::string name)
{
	JBase::Init(name);
}
void JVideoSprite::Clear()
{
	JBase::Clear();
	Deactivate();
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
void JVideoSprite::Update()
{
	JBase::Update();
}
void JVideoSprite::Deactivate()
{
	JBase::Deactivate();
	gJRenderManager.GetRenderer()->RemoveRenderable(mRenderable);
	mRenderable->Deactivate();
}