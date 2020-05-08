#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::PHYSICS;

JPhysics::JPhysics():mScaleFactor(0.01f), mGravity(0.f, 10.f)
{
}
JPhysics::~JPhysics()
{
}
void JPhysics::Init(const std::string name)
{
	JBase::Init(name);
}
void JPhysics::Clear()
{
	JBase::Clear();
}
void JPhysics::PreFrame()
{

}
void JPhysics::Update()
{
}
void JPhysics::PostFrame()
{

}
void JPhysics::Activate()
{
	JBase::Activate();
}
void JPhysics::Deactivate()
{
	JBase::Deactivate();
}