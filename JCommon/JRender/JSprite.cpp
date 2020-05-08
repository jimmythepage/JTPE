#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::RENDER;
using namespace J::GAME;

JSprite::JSprite(): mAnimated(false), mPlayStyle (NONE), mCurrentFrame(0), mFPS(0), 
mLoop(false), mCurrentAnim(""), mForward(true), mIsPlaying(false)
{
	if (!mRenderable)
	{
#ifdef __J_SIMPLE2D__
		mRenderable = new JSpriteSimple2D();
#elif defined(__SFML__)
		mRenderable = new JSpriteSFML();
#elif defined(__SDL__)
		mRenderable = new JSpriteSDL();
#else
		mRenderable = new JRenderable();
#endif
	}
}
JSprite::~JSprite()
{
	delete mRenderable;
	mRenderable = NULL;
	mSpriteSheet.clear();
}
void JSprite::Init(const std::string filepath, const std::string spritesheet, const std::string name, JRenderableProperties properties)
{
	BASE::JFile jsonFile;
	std::string path = gJEngine.GetSettings()->DataFolder;
	path += spritesheet;
	jsonFile.Init(spritesheet);
	jsonFile.Load(path, false);
	json jsonModule = json::parse(jsonFile.GetStringData());
	jsonFile.Unload();
	auto sprites = jsonModule["Sprites"];
	JRenderableProperties initial;
	for (unsigned int i = 0; i < sprites.size(); i++)
	{
		auto sprite = sprites[i];
		JRenderableProperties rect;
		rect.Position.x = sprite["x"];
		rect.Position.y = sprite["y"];
		rect.Size.x= sprite["width"];
		rect.Size.y = sprite["height"];
		mSpriteSheet[sprite["name"]] = rect;
		if (i == 0)
		{
			initial = rect;
		}
	}
	Init(filepath, name, properties, initial);
	if (!jsonModule[GAME::JsonDefine::Animated].is_null())
	{
		mAnimated = jsonModule[GAME::JsonDefine::Animated];
	}
	if (mAnimated)
	{
		if (jsonModule[JsonDefine::PlayStyle] == JsonDefine::Forward)
		{
			mCurrentFrame = 0;
			mPlayStyle = FORWARD;
			mForward = true;
		}
		else if (jsonModule[JsonDefine::PlayStyle] == JsonDefine::Backward)
		{
			mPlayStyle = BACKWARD;
			mForward = false;
		}
		else if (jsonModule[JsonDefine::PlayStyle] == JsonDefine::PingPong)
		{
			mCurrentFrame = 0;
			mPlayStyle = PINGPONG;
			mForward = true;
		}
		mFPS = jsonModule[JsonDefine::FPS];
		mLoop = jsonModule[JsonDefine::Loop];
		mFrameTimer.Init(name + " anim timer");
		float timeSpeed = 1.f / mFPS * 1000;
		mFrameTimer.SetTime((long long)timeSpeed);
		mFrameTimer.SetCallback(std::bind(&JSprite::FrameTimerCallback, this));

		auto anims = jsonModule[JsonDefine::Anims];
		for (unsigned int i = 0; i < anims.size(); i++)
		{
			std::vector<std::string> t;
			auto anim = anims[i];
			auto frames = anim[JsonDefine::Frames];
			if (jsonModule[JsonDefine::PlayStyle] == JsonDefine::Backward)
			{
				mCurrentFrame = (int)frames.size() - 1;
			}
			for (unsigned int j = 0; j < frames.size(); j++)
			{
				t.push_back(frames[j]);
			}
			mAnims[anim[JsonDefine::Name]] = t;
			if (i == 0)
			{
				std::string currentAnim= anim[JsonDefine::Name];
				mCurrentAnim = currentAnim;
			}
		}
		PlayAnim();
	}
}
void  JSprite::SetPlayStyle(PlayStyle style)
{
	mPlayStyle = style;
	if (mPlayStyle == FORWARD)
	{
		mForward = true;
	}
	else if (mPlayStyle == BACKWARD)
	{
		mForward = false;
	}
}
void JSprite::SetPlayStyle(std::string playstyle)
{
	if (playstyle == JsonDefine::Forward)
	{
		mPlayStyle = FORWARD;
		mForward = true;
	}
	else if (playstyle == JsonDefine::Backward)
	{
		mPlayStyle = BACKWARD;
		mForward = false;
	}
	else if (playstyle == JsonDefine::PingPong)
	{
		mPlayStyle = PINGPONG;
	}
}
void JSprite::PlayAnim()
{
	mFrameTimer.StartTimer(true,true);
	mIsPlaying = true;
}
void JSprite::StopAnim()
{
	mFrameTimer.StopTimer();
	mIsPlaying = false;
}
void JSprite::FrameTimerCallback()
{
	SetSpriteClip(mAnims[mCurrentAnim][mCurrentFrame]);
	if (mForward)
	{
		mCurrentFrame++;
		if ((unsigned int)mCurrentFrame >= mAnims[mCurrentAnim].size())
		{
			if (mPlayStyle == FORWARD)
			{
				if (mLoop)
				{
					mCurrentFrame = 0;
				}
				else
				{
					mFrameTimer.StopTimer();
				}
			}
			else if (mPlayStyle == PINGPONG)
			{
				mForward = false;
				mCurrentFrame--;
			}
		}
	}
	else
	{
		mCurrentFrame--;
		if (mCurrentFrame <0)
		{
			if (mPlayStyle == BACKWARD)
			{
				if (mLoop)
				{
					mCurrentFrame = (int)mAnims[mCurrentAnim].size()-1;
				}
				else
				{
					mFrameTimer.StopTimer();
				}
			}
			else if (mPlayStyle == PINGPONG)
			{
				if (mLoop)
				{
					mForward = true;
					mCurrentFrame = 0;
				}
				else
				{
					mCurrentFrame = 0;
					mFrameTimer.StopTimer();
				}
			}
		}
	}
	
}
void JSprite::SetSpriteClip(std::string sprite)
{
	mRenderable->SetSpriteClip(mSpriteSheet[sprite]);
}
void JSprite::Init(const std::string filepath, const std::string name, JRenderableProperties properties)
{
	Init(name);
	mRenderable->Init(filepath, name + " renderable", properties);
}
void JSprite::Init(const std::string filepath, const std::string name, JRenderableProperties properties, JRenderableProperties clip)
{
	Init(name);
	mRenderable->Init(filepath, name + " renderable", properties,clip);
}
void JSprite::Init(const std::string name)
{
	JBase::Init(name);
}
void JSprite::Clear()
{
	JBase::Clear();
	mAnims.clear();
	Deactivate();
	mFrameTimer.Clear();
	mRenderable->Clear();
	mSpriteSheet.clear();
}
void JSprite::Activate()
{
	JBase::Activate();
	mRenderable->Activate();
	gJRenderManager.GetRenderer()->AddRenderable(mRenderable);
	if (mIsPlaying)
	{
		PlayAnim();
	}
}
void JSprite::Update()
{
	JBase::Update();
	mFrameTimer.Update();
}
void JSprite::Deactivate()
{
	JBase::Deactivate();
	gJRenderManager.GetRenderer()->RemoveRenderable(mRenderable);
	mRenderable->Deactivate();
	mFrameTimer.StopTimer();
}