#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;

JTask::JTask():mIsRunning(false)
{

}
JTask::~JTask()
{
}
void JTask::Init(const std::string name)
{
	JBase::Init(name);
}
void JTask::Clear()
{
}
void JTask::Update()
{
}
void JTask::Activate()
{
	mIsRunning = true;
	mThread = std::thread(&JTask::Update, this);
}
void JTask::Join()
{
	if (mThread.joinable())
	{
		mThread.join();
	}
}
void JTask::Detach()
{
	mThread.detach();
}
void JTask::Deactivate()
{
	mIsRunning = false;
}