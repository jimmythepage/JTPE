#include "JCommonPch.h"

using namespace J;
using namespace J::RENDER;
using namespace J::GAME;


JGameDraggable::JGameDraggable(): mOldXOffset(0), mOldYOffset(0), mCanLandFreely(true), mLandingX(0), mLandingY(0), mLongPressThreshold(3.f),
mForceRelease(false)
{

}
JGameDraggable::~JGameDraggable()
{

}
void JGameDraggable::Init(const std::string name, std::string applink, json button)
{
	JGameButton::Init(name, applink,button);
	mLandingElements.clear();
	mCanLandFreely = (button[JsonDefine::LandingApplink].is_null());
	mCanBeOverriden = false;
	mLandingX = mRelProperties.Position.x;
	mLandingY = mRelProperties.Position.y;
}
void JGameDraggable::Clear()
{
	JGameButton::Clear();
	mLandingElements.clear();
}
void JGameDraggable::Update()
{
	JGameElement::Update();
	if (mState == StateDisabled)
	{
		return;
	}
	mLongPressTimer.Update();
	JGameButton* exploredButton = gJGameManager.GetCurrentExploredButton();
	if (exploredButton && exploredButton != this && !exploredButton->CanBeOverriden())
	{
		return;
	}

	float pointerX = gJInputManager.GetInputPointer()->GetPointerX();
	float pointerY = gJInputManager.GetInputPointer()->GetPointerY();

	if (GetState() == StatePressed)
	{
		float diffX = pointerX- mOldXOffset;
		float diffY = pointerY - mOldYOffset;
		mRelProperties.Position.x += diffX;
		mRelProperties.Position.y += diffY;
		float movementX = abs(mRelProperties.Position.x - mLandingX);
		float movementY = abs(mRelProperties.Position.x - mLandingY);
		if (movementX > mLongPressThreshold ||
			movementY > mLongPressThreshold)
		{
			mLongPressTimer.StopTimer();
		}
		mOldXOffset = pointerX;
		mOldYOffset = pointerY;
		if (gJInputManager.GetInputPointer()->GetPointerReleased(Mouse_Left) || mForceRelease)
		{
			mForceRelease = false;
			//LOG_INFO(0, "StateReleased\n", 0);
			if (!mCanLandFreely)
			{
				if (mLandingElements.size() == 0)
				{
					auto landingAppLinks = mjsonStatedElements[JsonDefine::LandingApplink];
					for (unsigned int i = 0; i < landingAppLinks.size(); i++)
					{
						std::list<JGameElement*> elements = gJGameManager.GetCurrentScreen()->GetChilds(landingAppLinks[i]);
						mLandingElements.merge(elements);
					}
				}
				for (JGameElement* element : mLandingElements)
				{
					if (element->IsInside(mAbsProperties.Position.x, mAbsProperties.Position.y))
					{
						mLandingX = element->GetAbsProperties().Position.x;
						mLandingY = element->GetAbsProperties().Position.y;
						break;
					}
				}
				mRelProperties.Position.x = mLandingX;
				mRelProperties.Position.y = mLandingY;
			}
			else
			{
				mLandingX = mRelProperties.Position.x;
				mLandingY = mRelProperties.Position.y;
			}
			SetState(StateReleased);
			for (std::map< J::BASE::JBase*, ButtonCallack>::iterator it = mOnReleased.begin(); it != mOnReleased.end(); it++)
			{
				(*it).second.Function(this, (*it).second.Params);
			}
		}
		return;
	}

	if (IsInside(pointerX,pointerY))//INSIDE
	{
		if (exploredButton && exploredButton != this)
		{
			if ((mRelProperties.Z + mRelProperties.ZAdd) < (exploredButton->GetRelProperties().Z + exploredButton->GetRelProperties().ZAdd))
			{
				SetState(StateNormal);
				return;
			}
			else
			{
				exploredButton->SetState(StateNormal);
			}
		}
		if (GetState() == StateNormal || GetState() == StateReleased)
		{
			//LOG_INFO(0, "StateHover\n", 0);
			SetState(StateHover);
			gJGameManager.SetCurrentExploredButton(this);
			for (std::map< J::BASE::JBase*, ButtonCallack>::iterator it = mOnHover.begin(); it != mOnHover.end(); it++)
			{
				(*it).second.Function(this, (*it).second.Params);
			}
		}
		else if (GetState() == StateHover)
		{
			if (gJInputManager.GetInputPointer()->GetPointerPressed(Mouse_Left))
			{
				//LOG_INFO(0, "StatePressed\n", 0);
				for (std::map< J::BASE::JBase*, ButtonCallack>::iterator it = mOnPressed.begin(); it != mOnPressed.end(); it++)
				{
					(*it).second.Function(this, (*it).second.Params);
				}
				SetState(StatePressed);
				mLongPressTimer.SetTime(mTimeForLongPress);
				mLongPressTimer.StartTimer(true, false);
				mOldXOffset = pointerX;
				mOldYOffset = pointerY;
			}
		}
	}
	else
	{
		SetState(StateNormal);
		gJGameManager.SetCurrentExploredButton(NULL);
	}
}
void JGameDraggable::LongPressTimerCallback()
{
	JGameButton::LongPressTimerCallback();
	mForceRelease = true;
}
void JGameDraggable::Activate()
{
	JGameButton::Activate();
}
void JGameDraggable::Deactivate()
{
	JGameButton::Deactivate();
}