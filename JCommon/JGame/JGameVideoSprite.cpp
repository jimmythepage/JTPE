#include "JCommonPch.h"

using namespace J;
using namespace J::RENDER;
using namespace J::GAME;


JGameVideoSprite::JGameVideoSprite()
{

}
JGameVideoSprite::~JGameVideoSprite()
{
	if (mSprite)
	{
		delete mSprite;
		mSprite = NULL;
	}
}
void JGameVideoSprite::Init(const std::string name, std::string applink, json sprite)
{
	JGameElement::Init(name,applink);
	ReadGeneralProperties(sprite);
	CalcAbsProperties();
	mSprite = new J::RENDER::JVideoSprite();
	mSprite->Init(sprite[JsonDefine::Texture], name + " sprite", mAbsProperties);
	if (!sprite[JsonDefine::Loop].is_null())
	{
		mSprite->SetLoop(sprite[JsonDefine::Loop]);
	}
	if (!mPhysicsObject)
	{
		mPhysicsObject = new PHYSICS::JPhysicObject();
		mPhysicsObject->Init(mName + " physics object", mAbsProperties, mBodyType);
	}
}
void JGameVideoSprite::Clear()
{
	JGameElement::Clear();
	mSprite->Clear();
}
void JGameVideoSprite::Update()
{
	JGameElement::Update();
	mSprite->Update();
	mSprite->SetProperties(mAbsProperties);
}
void JGameVideoSprite::Activate()
{
	JGameElement::Activate();
	mSprite->Activate();
}
void JGameVideoSprite::Deactivate()
{
	JGameElement::Deactivate();
	mSprite->Deactivate();
}