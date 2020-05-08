#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::TWEEN;


JBaseTween::JBaseTween() :mStarted(false), mPlayStyle(FORWARD), mLoop(false), mRoundCount(0), mPlayCurve(LINEAR)
{

}
JBaseTween::~JBaseTween()
{
}
void JBaseTween::Init(const std::string name, long long time)
{
	JBase::Init(name);
	mTimer.Init(name + " timer");
	auto fn = std::bind(&JBaseTween::TimerCallback, this);
	mTimer.SetCallback(fn);
	mTimer.SetTime(time);
	mStarted = false;
	mRoundCount = 0;
}
void JBaseTween::Clear()
{
	JBase::Clear();
	mRoundCount = 0;
	mStarted = false;
	mLoop = false;
	StopTween();
	mTimer.Clear();
	mPlayStyle = FORWARD;
}
void JBaseTween::Update()
{
	JBase::Update();
	mTimer.Update();
}
void JBaseTween::SetPlayStyle(PlayStyle style)
{ 
	mPlayStyle = style; 
	if (mPlayStyle == BACKWARD)
	{
		InvertValues();
	}
}
void JBaseTween::TimerCallback()
{
	if (mLoop)
	{
		if (mPlayStyle == FORWARD)
		{
			RestartTween();
		}
		else if (mPlayStyle == BACKWARD)
		{
			RestartTween();
		}
		else if (mPlayStyle == PINGPONG)
		{
			InvertValues();
			RestartTween();
		}
	}
	else
	{
		if (mPlayStyle == PINGPONG && mRoundCount == 0)
		{
			InvertValues();
			RestartTween();
		}
	}
	mRoundCount++;
}
void JBaseTween::InvertValues()
{

}
void JBaseTween::RestartTween()
{
	StartTween();
}
void JBaseTween::StartTween()
{
	mTimer.StartTimer(true);
	mStarted = true;
}
void JBaseTween::StopTween()
{
	mTimer.StopTimer();
	mStarted = false;
}
float JBaseTween::Lerp(float a, float b, float f)
{
	return a + f * (b - a);
}