#include "JCommonPch.h"

using namespace J;
using namespace J::RENDER;
using namespace J::GAME;


JGameSprite::JGameSprite()
{

}
JGameSprite::~JGameSprite()
{
	if (mSprite)
	{
		delete mSprite;
		mSprite = NULL;
	}
}
void JGameSprite::Init(const std::string name, std::string applink, json sprite)
{
	JGameElement::Init(name,applink);
	ReadGeneralProperties(sprite);
	CalcAbsProperties();
	mSprite = new J::RENDER::JSprite();
	if (!sprite[JsonDefine::TextureJson].is_null())
	{
		mSprite->Init(sprite[JsonDefine::Texture], sprite[JsonDefine::TextureJson], name + " sprite", mAbsProperties);
	}						 
	else					 
	{						 
		mSprite->Init(sprite[JsonDefine::Texture], name + " sprite", mAbsProperties);
	}
	if (!sprite[JsonDefine::Loop].is_null())
	{
		mSprite->SetLoop(sprite[JsonDefine::Loop]);
	}
	if (!sprite[JsonDefine::PlayStyle].is_null())
	{
		std::string playstyle = sprite[JsonDefine::PlayStyle];
		mSprite->SetPlayStyle(playstyle);
	}
	if (!sprite[JsonDefine::Anim].is_null())
	{
		std::string anim = sprite[JsonDefine::Anim];
		mSprite->SetAnim(anim);
	}
	if (!mPhysicsObject)
	{
		mPhysicsObject = new PHYSICS::JPhysicObject();
		mPhysicsObject->Init(mName + " physics object", mAbsProperties, mBodyType);
	}
}
void JGameSprite::Clear()
{
	JGameElement::Clear();
	mSprite->Clear();
}
void JGameSprite::Update()
{
	JGameElement::Update();
	mSprite->Update();
	mSprite->SetProperties(mAbsProperties);
}
void JGameSprite::Activate()
{
	JGameElement::Activate();
	mSprite->Activate();
}
void JGameSprite::Deactivate()
{
	JGameElement::Deactivate();
	mSprite->Deactivate();
}