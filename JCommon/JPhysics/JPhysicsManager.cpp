#include "JCommonPch.h"

using namespace J;
using namespace J::BASE;
using namespace J::PHYSICS;

JPhysicsManager::JPhysicsManager():mPhysics(NULL)
{
}
JPhysicsManager::~JPhysicsManager()
{
}
JPhysicsManager & JPhysicsManager::GetSingleton()
{
	static JPhysicsManager _singleton;
	return _singleton;
}
void JPhysicsManager::Init(const std::string name)
{
	JBase::Init(name);
	if (!mPhysics)
	{
#if defined(__BOX2D__)
		mPhysics = new JPhysicsBox2D();
		mPhysics->Init("mPhysics Box2D");
#else
		mPhysics = new JPhysics();
		mPhysics->Init("mPhysics Generic");
#endif
	}
}
void JPhysicsManager::Clear()
{
	JBase::Clear();
	if (mPhysics)
	{
		mPhysics->Clear();
		delete mPhysics;
		mPhysics = NULL;
	}
}
void JPhysicsManager::Update()
{
	mPhysics->PreFrame();
	mPhysics->Update();
	mPhysics->PostFrame();
}
void JPhysicsManager::Activate()
{
	JBase::Activate();
	mPhysics->Activate();
	LOG_INFO(0, "%s is Activated\n", mName.c_str());
}
void JPhysicsManager::Deactivate()
{
	JBase::Deactivate();
	mPhysics->Deactivate();
	LOG_INFO(0, "%s is Deactivated\n", mName.c_str());
}