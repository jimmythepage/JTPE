#include "JCommonPch.h"

using namespace J;
using namespace J::BASE;


JTimer::JTimer():mTime(0), mTimeToReach(0), mRepeat(false), mTimerCallback(NULL)
{
}
JTimer::~JTimer()
{

}
void JTimer::Init(const std::string name)
{
	JBase::Init(name);
}
void JTimer::Clear()
{
	JBase::Clear();
	mTimerCallback = NULL;
}
void JTimer::SetTime(__int64 time)
{
	mTimeToReach = time;
}
void JTimer::StartTimer(bool restart,bool repeat)
{
	Deactivate();
	mRepeat= repeat;
	mTime = 0;
	mStartTime = std::chrono::high_resolution_clock::now();
	Activate();
}
void JTimer::StopTimer()
{
	Deactivate();
}
void JTimer::Update()
{
	if (!mIsActive)
	{
		return;
	}
	if (DoTick())//TIMER ARRIVED TO DESTINATION
	{
		if (!mRepeat)
		{
			Deactivate();
		}
		else
		{
			StartTimer(true,true);
		}
		if (mTimerCallback)
		{
			mTimerCallback();
		}
	}
}
bool JTimer::DoTick()
{
	using namespace std;
	using namespace std::chrono;
	high_resolution_clock::time_point currentTime = high_resolution_clock::now();
	mTime = duration_cast<milliseconds>(currentTime - mStartTime).count();
	if (mTime >= mTimeToReach)
	{
		return true;
	}
	return false;
}
void JTimer::Activate()
{
	JBase::Activate();
}
void JTimer::Deactivate()
{
	JBase::Deactivate();
}