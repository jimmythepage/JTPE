#include "JCommonPch.h"

using namespace J;
using namespace J::TWEEN;


JFloatTween::JFloatTween():mStart(0.f), mGoal(0.f)
{

}
JFloatTween::~JFloatTween()
{
}
void JFloatTween::Init(const std::string name, long long time,float value, float goal)
{
	JBaseTween::Init(name,time);
	mGoal = goal;
	mStart = value;
}
void JFloatTween::InvertValues()
{
	JBaseTween::InvertValues();
	float swap = mStart;
	mStart = mGoal;
	mGoal = swap;
}
void JFloatTween::Clear()
{
	JBaseTween::Clear();
}
float JFloatTween::GetValue()
{
	JBaseTween::Update();
	float t = (float)mTimer.GetTime() / (float)mTimer.GetTimeToReach();
	float value= Lerp(mStart, mGoal, t);
	if (value < mStart)
	{
		value = mStart;
	}
	else if (value > mGoal)
	{
		value = mGoal;
	}
	return Lerp(mStart, mGoal, t);
}