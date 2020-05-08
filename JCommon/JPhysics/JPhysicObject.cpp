#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::PHYSICS;
using namespace J::GAME;

JPhysicObject::JPhysicObject()
{
	if (!mBody)
	{
#ifdef __BOX2D__
		mBody = new JBodyBox2D();
#else
		mBody = new JBody();
#endif
	}
}
JPhysicObject::~JPhysicObject()
{
	delete mBody;
	mBody = NULL;
}
void JPhysicObject::Init(const std::string name, J::RENDER::JRenderableProperties properties, BodyType type)
{
	JBase::Init(name);
	mBody->Init(name + " body", properties, type);
}
void JPhysicObject::Clear()
{
	JBase::Clear();
	mBody->Clear();
}
void JPhysicObject::Activate()
{
	JBase::Activate();
	mBody->Activate();
}
void JPhysicObject::Update()
{
	JBase::Update();
	mBody->Update();
}
void JPhysicObject::Deactivate()
{
	JBase::Deactivate();
	mBody->Deactivate();
}