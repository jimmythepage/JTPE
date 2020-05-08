#include "JCommonPch.h"

using namespace J;
using namespace J::RENDER;
using namespace J::GAME;


JGameCamera::JGameCamera():mToFollow(NULL), mFollowSpeedX(0), mFollowSpeedY(0)
{

}
JGameCamera::~JGameCamera()
{
	
}
void JGameCamera::Init(const std::string name, std::string filepath)
{
	std::string path = gJEngine.GetSettings()->DataFolder + filepath;
	json module = gJGameManager.GetJsonScreen(path);
	JGameElement::Init(name, module[J::GAME::JsonDefine::AppLink]);
	ReadGeneralProperties(module);
	CalcAbsProperties();
	if (!module[JsonDefine::FollowSpeed].is_null())
	{
		auto speed = module[JsonDefine::FollowSpeed];
		mFollowSpeedX = speed[0];
		mFollowSpeedY = speed[1];
	}
}
void JGameCamera::Clear()
{
	JGameElement::Clear();
	mToFollow = NULL;
}
void JGameCamera::Update()
{
	JGameElement::Update();
	if (mToFollow)
	{
		//LOG_INFO(0, "Cam posX:%f, Char posX:%f\n", mRelProperties.X, mToFollow->GetAbsProperties().X);
		J::RENDER::JRenderableProperties	followProperties= mToFollow->GetAbsProperties();
		float diffX = followProperties.Position.x-mRelProperties.Position.x;
		float checkFactor = 2.5f;
		if (abs(diffX) > mFollowSpeedX*checkFactor)
		{
			if (diffX < 0)
			{
				mRelProperties.Position.x -= mFollowSpeedX;
			}
			else
			{
				mRelProperties.Position.x += mFollowSpeedX;
			}
		}
		float diffY = followProperties.Position.y - mRelProperties.Position.y;
		if (abs(diffY) > mFollowSpeedY*checkFactor)
		{
			if (diffY < 0)
			{
				mRelProperties.Position.y -= mFollowSpeedY;
			}
			else
			{
				mRelProperties.Position.y= mFollowSpeedY;
			}
		}
		//mAbsProperties.Y = mToFollow->GetAbsProperties().Y;
	}
}
void JGameCamera::Activate()
{
	JGameElement::Activate();
}
void JGameCamera::Deactivate()
{
	JGameElement::Deactivate();
}