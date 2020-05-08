#include "JCommonPch.h"

using namespace J;
using namespace J::GAME;


JGameElement::JGameElement() : mAppLink(""), mParent(NULL), mCamera(NULL), mBodyType(PHYSICS::BodyType::None), mPhysicsObject(NULL)
{

}
JGameElement::~JGameElement()
{

}
void JGameElement::Init(const std::string name, std::string applink)
{
	JBase::Init(name);
	mAppLink = applink;
	CalcAbsProperties();
	mOldAbsProperties = mAbsProperties;
}
void JGameElement::Clear()
{
	JBase::Clear();
	if (mPhysicsObject)
	{
		mPhysicsObject->Clear();
		delete mPhysicsObject;
		mPhysicsObject = NULL;
	}
	mBodyType = PHYSICS::BodyType::None;
	for (JGameElement* element : mChilds)
	{
		element->Clear();
		delete element;
		element = 0;
	}
	mChilds.clear();
	mAppLink = "";
	mParent = NULL;
	mCamera = NULL;
}
void JGameElement::Update()
{
	JBase::Update();
	CalcAbsProperties();
	for (JGameElement* element : mChilds)
	{
		element->Update();
	}
	if (mPhysicsObject)
	{
		mPhysicsObject->Update();
		mAbsProperties = mPhysicsObject->GetBody()->GetTransformedProperties(mAbsProperties);
	}
	mOldAbsProperties = mAbsProperties;
}
void JGameElement::Activate()
{
	JBase::Activate();
	for (JGameElement* element : mChilds)
	{
		element->Activate();
	}
	if (mPhysicsObject)
	{
		mPhysicsObject->Activate();
	}
}
void JGameElement::Deactivate()
{
	JBase::Deactivate();
	for (JGameElement* element : mChilds)
	{
		element->Deactivate();
	}
	if (mPhysicsObject)
	{
		mPhysicsObject->Deactivate();
	}
}
bool JGameElement::IsInside(float x, float y)
{
	if (!mIsActive || !GetAbsProperties().Visible)
	{
		return false;
	}
	float currentWidth = (float)mAbsProperties.Size.x*mAbsProperties.Scale.x;
	float currentHeight = (float)mAbsProperties.Size.y*mAbsProperties.Scale.y;

	float offsetX = currentWidth * mAbsProperties.Origin.x;
	float offsetY = currentHeight * mAbsProperties.Origin.y;
	float leftX = mAbsProperties.Position.x - offsetX;
	float leftY = mAbsProperties.Position.y - offsetY;

	return (x >= leftX && x <= leftX + currentWidth
		&& y >= leftY && y <= leftY + currentHeight);//INSIDE
}
void JGameElement::SetCamera(JGameCamera* camera)
{
	mCamera = camera;
	for (JGameElement* element : mChilds)
	{
		element->SetCamera(mCamera);
	}
}
void JGameElement::SetRelProperties(J::RENDER::JRenderableProperties& properties)
{
	mRelProperties = properties;
}
void JGameElement::CalcAbsProperties()
{
	mAbsProperties = mRelProperties;
	if (mParent)
	{
		mAbsProperties.Position.x = mRelProperties.Position.x + mParent->GetAbsProperties().Position.x;
		mAbsProperties.Position.y = mRelProperties.Position.y + mParent->GetAbsProperties().Position.y;
		mAbsProperties.Rot = mRelProperties.Rot + mParent->GetAbsProperties().Rot;
		mAbsProperties.Scale.x = mRelProperties.Scale.x*mParent->GetAbsProperties().Scale.x;
		mAbsProperties.Scale.y = mRelProperties.Scale.y*mParent->GetAbsProperties().Scale.y;
		mAbsProperties.Visible = (mParent->GetAbsProperties().Visible && mRelProperties.Visible);
		//ALPHA MULTIPLY MODE
		mAbsProperties.A = mRelProperties.A* mParent->GetAbsProperties().A;
	}
	if (mCamera)
	{
		mAbsProperties.Scale.x /= mCamera->GetAbsProperties().Scale.x;
		mAbsProperties.Scale.y /= mCamera->GetAbsProperties().Scale.y;
		mAbsProperties.Position.x -= mCamera->GetAbsProperties().Position.x;
		mAbsProperties.Position.y -= mCamera->GetAbsProperties().Position.y;
	}
}
void JGameElement::ReadGeneralProperties(json properties)
{
	if (!properties[JsonDefine::Visible].is_null())
	{
		mRelProperties.Visible = properties[JsonDefine::Visible];
	}
	if (!properties[JsonDefine::Z].is_null())
	{
		mRelProperties.Z = properties[JsonDefine::Z];
	}
	if (!properties[JsonDefine::ZAdd].is_null())
	{
		mRelProperties.ZAdd = properties[JsonDefine::ZAdd];
	}
	if (!properties[JsonDefine::Position].is_null())
	{
		auto position = properties[JsonDefine::Position];
		mRelProperties.Position.x = position[0];
		mRelProperties.Position.y = position[1];
	}
	if (!properties[JsonDefine::Size].is_null())
	{
		auto size = properties[JsonDefine::Size];
		mRelProperties.Size.x = size[0];
		mRelProperties.Size.y = size[1];
	}
	if (!properties[JsonDefine::Rot].is_null())
	{
		mRelProperties.Rot = properties[JsonDefine::Rot];
	}
	if (!properties[JsonDefine::Scale].is_null())
	{
		auto scale = properties[JsonDefine::Scale];
		mRelProperties.Scale.x = scale[0];
		mRelProperties.Scale.y = scale[1];
	}
	if (!properties[JsonDefine::Origin].is_null())
	{
		auto origin = properties[JsonDefine::Origin];
		mRelProperties.Origin.x = origin[0];
		mRelProperties.Origin.y = origin[1];
	}
	if (!properties[JsonDefine::Color].is_null())
	{
		auto color = properties[JsonDefine::Color];
		mRelProperties.R = color[0];
		mRelProperties.G = color[1];
		mRelProperties.B = color[2];
		mRelProperties.A = color[3];
	}
	if (!properties[JsonDefine::CollisionType].is_null())
	{
		std::string type = properties[JsonDefine::CollisionType];
		if (type == JsonDefine::CollisionNone)
		{
			mBodyType = PHYSICS::BodyType::None;
		}
		else if (type == JsonDefine::CollisionTrigger)
		{
			mBodyType = PHYSICS::BodyType::Trigger;
		}
		else if (type == JsonDefine::CollisionMovable)
		{
			mBodyType = PHYSICS::BodyType::Dynamic;
		}
		else if (type == JsonDefine::CollisionStatic)
		{
			mBodyType = PHYSICS::BodyType::Static;
		}
	}
}
void JGameElement::SetParent(JGameElement* parent,bool retain)
{
	mParent = parent;
	if (!mParent)
	{
		mRelProperties = mAbsProperties;
	}
	else if(mParent && retain)
	{
		mRelProperties.Position.x= mAbsProperties.Position.x - mParent->GetAbsProperties().Position.x;
		mRelProperties.Position.y = mAbsProperties.Position.y - mParent->GetAbsProperties().Position.y;
		mRelProperties.Rot = mAbsProperties.Rot - mParent->GetAbsProperties().Rot;
		mRelProperties.Scale.x = mAbsProperties.Scale.x/mParent->GetAbsProperties().Scale.y;
		mRelProperties.Scale.y = mAbsProperties.Scale.y / mParent->GetAbsProperties().Scale.y;
	}
	CalcAbsProperties();
}
JGameElement* JGameElement::GetParent()
{
	return mParent;
}
void JGameElement::AddChild(JGameElement* child)
{
	mChilds.push_back(child);
	child->SetParent(this,false);
}
JGameElement* JGameElement::GetChild(std::string appLink)
{
	for (JGameElement* element : mChilds)
	{
		if (appLink == element->GetAppLink())
		{
			return element;
		}
	}
	return NULL;
}
std::list<JGameElement*> JGameElement::GetChilds(std::string appLink)
{
	std::list<JGameElement*> childs;
	for (JGameElement* element : mChilds)
	{
		if (appLink == element->GetAppLink())
		{
			childs.push_back(element);
		}
		std::list<JGameElement*> granChilds=element->GetChilds(appLink);
		childs.merge(granChilds);
	}
	return childs;
}
void JGameElement::RemoveChild(JGameElement* child)
{
	mChilds.remove(child);
	child->SetParent(NULL,false);
}