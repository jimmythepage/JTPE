#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::PHYSICS;
using namespace J::GAME;

JBody::JBody():mBodyType(None), mFriction(1.f),mGravityScale(1.f)
{
	
}
JBody::~JBody()
{

}
void JBody::Init(const std::string name, J::RENDER::JRenderableProperties properties, BodyType type)
{
	JBase::Init(name);
	mBodyType = type;
}
void JBody::Clear()
{
	JBase::Clear();
}
void JBody::Activate()
{
	JBase::Activate();
}
J::RENDER::JRenderableProperties	JBody::GetTransformedProperties(J::RENDER::JRenderableProperties	baseProperties)
{
	return baseProperties;
}
void JBody::Update()
{
	JBase::Update();
}
void JBody::Deactivate()
{
	JBase::Deactivate();
}