#include "JCommonPch.h"
#include "JPhysicsBox2D.h"


using namespace J;
using namespace J::TASK;
using namespace J::PHYSICS;

JPhysicsBox2D::JPhysicsBox2D()
{
}
JPhysicsBox2D::~JPhysicsBox2D()
{
}
void JPhysicsBox2D::Init(const std::string name)
{
	JPhysics::Init(name);
	mTimeStep = 1.0f / 60.0f;
	mVelocityIterations = 6;
	mPositionIterations = 2;
	mGravityb2 = b2Vec2(mGravity.x, mGravity.y);
	mWorld = new b2World(mGravityb2);
}
void JPhysicsBox2D::Clear()
{
	JPhysics::Clear();
	if (mWorld)
	{
		delete mWorld;
		mWorld = NULL;
	}
}
void JPhysicsBox2D::Activate()
{
}
void JPhysicsBox2D::Deactivate()
{
}
void JPhysicsBox2D::PreFrame()
{
}
void JPhysicsBox2D::Update()
{
	mWorld->Step(mTimeStep, mVelocityIterations, mPositionIterations);
}
void JPhysicsBox2D::PostFrame()
{
	
}
