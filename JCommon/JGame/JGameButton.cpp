#include "JCommonPch.h"

using namespace J;
using namespace J::RENDER;
using namespace J::GAME;


JGameButton::JGameButton():mState(StateNone), mCanBeOverriden(true), mTimeForLongPress(1500)
{

}
JGameButton::~JGameButton()
{

}
void JGameButton::Init(const std::string name, std::string applink, json button)
{
	mjsonStatedElements = button;
	JGameElement::Init(name, applink);
	mLongPressTimer.Init(name + " long press timer");
	auto fn = std::bind(&JGameButton::LongPressTimerCallback, this);
	mLongPressTimer.SetCallback(fn);
	ReadGeneralProperties(button);
	CalcAbsProperties();
}
void JGameButton::InitButtonText()
{
	if (!mjsonStatedElements[JsonDefine::TextAppLink].is_null())
	{
		for (auto const& i : mChilds)
		{
			JGameText* text = dynamic_cast<JGameText*>(i);
			if (text)
			{
				text->SetText(gJTextDB.GetTextEntry(mjsonStatedElements[JsonDefine::TextAppLink]));
			}
		}
	}
}
void JGameButton::FillStatedElements()
{
	mStatedElements.clear();
	if (!mjsonStatedElements[JsonDefine::ButtonStates].is_null())
	{
		auto states = mjsonStatedElements[JsonDefine::ButtonStates];
		ReadChildsForState(StateNormal, states[JsonDefine::Normal]);
		ReadChildsForState(StateDisabled, states[JsonDefine::Disabled]);
		ReadChildsForState(StateHover, states[JsonDefine::Hover]);
		ReadChildsForState(StatePressed, states[JsonDefine::Pressed]);
		ReadChildsForState(StateReleased, states[JsonDefine::Released]);
	}
}
void JGameButton::ReadChildsForState(ButtonState state, json childs)
{
	JGameElement* element = NULL;
	if (!childs.is_null())
	{
		auto normal = childs;
		for (unsigned int i = 0; i < normal.size(); i++)
		{
			element = GetChild(normal[i]);
			if (element)
			{
				if (mStatedElements.find(element) == mStatedElements.end())
				{
					std::vector<ButtonState> v;
					v.push_back(state);
					mStatedElements.insert(std::pair<JGameElement*, std::vector<ButtonState>>(element, v));
				}
				else
				{
					mStatedElements[element].push_back(state);
				}
			}
		}
	}
}
void JGameButton::SetState(ButtonState state)
{
	if (mState == state)
	{
		return;
	}
	mState = state;
	mLongPressTimer.StopTimer();
	for (std::map<JGameElement* , std::vector<ButtonState>>::iterator it = mStatedElements.begin(); it != mStatedElements.end(); it++)
	{
		JGameElement* element = (*it).first;
		J::RENDER::JRenderableProperties properties = element->GetRelProperties();
		properties.Visible = false;
		std::vector<ButtonState> v = (*it).second;
		for (unsigned int i = 0; i < v.size(); i++)
		{
			if (v[i] == state)
			{
				properties.Visible = true;
				break;
			}
		}
		element->SetRelProperties(properties);
	}
}
void JGameButton::Clear()
{
	JGameElement::Clear();
	mLongPressTimer.StopTimer();
	mOnReleased.clear();
	mOnHover.clear();
	mOnPressed.clear();
	mOnLongPress.clear();
	mStatedElements.clear();
}
void JGameButton::Update()
{
	JGameElement::Update();
	if (!IsActive())
	{
		return;
	}
	if (mState == StateDisabled)
	{
		return;
	}
	JGameButton* exploredButton = gJGameManager.GetCurrentExploredButton();
	if (exploredButton && exploredButton != this && !exploredButton->CanBeOverriden())
	{
		SetState(StateNormal);
		return;
	}

	float pointerX = gJInputManager.GetInputPointer()->GetPointerX();
	float pointerY = gJInputManager.GetInputPointer()->GetPointerY();

	if (IsInside(pointerX,pointerY))//INSIDE
	{
		if (exploredButton && exploredButton != this)
		{
			if ((mAbsProperties.Z + mAbsProperties.ZAdd) < (exploredButton->GetAbsProperties().Z + exploredButton->GetAbsProperties().ZAdd))
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
			}
		}
		else if (GetState() == StatePressed)
		{
			if (gJInputManager.GetInputPointer()->GetPointerReleased(Mouse_Left))
			{
				//LOG_INFO(0, "StateReleased\n", 0);
				SetState(StateReleased);
				for (std::map< J::BASE::JBase*, ButtonCallack>::iterator it = mOnReleased.begin(); it != mOnReleased.end(); it++)
				{
					(*it).second.Function(this, (*it).second.Params);
				}
			}
		}
	}
	else
	{
		if (exploredButton && exploredButton == this)
		{
			gJGameManager.SetCurrentExploredButton(NULL);
		}
		SetState(StateNormal);
	}
	mLongPressTimer.Update();
}
void JGameButton::LongPressTimerCallback()
{
	for (std::map< J::BASE::JBase*, ButtonCallack>::iterator it = mOnLongPress.begin(); it != mOnLongPress.end(); it++)
	{
		(*it).second.Function(this, (*it).second.Params);
	}
}
void JGameButton::AddCallback(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params,
	std::map< J::BASE::JBase*, ButtonCallack>* map)
{
	ButtonCallack callback;
	callback.Function = function;
	callback.Params = params;
	std::pair<J::BASE::JBase*, ButtonCallack > pair(caller, callback);
	map->insert(pair);
}
void JGameButton::RemoveCallback(J::BASE::JBase* caller, std::map< J::BASE::JBase*, ButtonCallack>* map)
{
	map->erase(caller);
}
void JGameButton::AddOnReleased(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params)
{
	AddCallback(caller,function, params, &mOnReleased);
}
void JGameButton::RemoveOnReleased(J::BASE::JBase* caller)
{
	RemoveCallback(caller,&mOnReleased);
}
void JGameButton::AddOnHover(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params)
{
	AddCallback(caller, function, params, &mOnHover);
}
void JGameButton::RemoveOnHover(J::BASE::JBase* caller)
{
	RemoveCallback(caller, &mOnHover);
}
void JGameButton::AddOnPressed(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params)
{
	AddCallback(caller, function, params, &mOnPressed);
}
void JGameButton::RemoveOnPressed(J::BASE::JBase* caller)
{
	RemoveCallback(caller, &mOnPressed);
}
void JGameButton::AddOnLongPress(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params)
{
	AddCallback(caller, function, params, &mOnLongPress);
}
void JGameButton::RemoveOnLongPress(J::BASE::JBase* caller)
{
	RemoveCallback(caller, &mOnLongPress);
}
void JGameButton::Activate()
{
	JGameElement::Activate();
	FillStatedElements();
	if (!mjsonStatedElements[JsonDefine::State].is_null())
	{
		auto state = mjsonStatedElements[JsonDefine::State];
		if (state == JsonDefine::Normal)
		{
			SetState(StateNormal);
		}
		else if (state == JsonDefine::Hover)
		{
			SetState(StateHover);
		}
		else if (state == JsonDefine::Disabled)
		{
			SetState(StateDisabled);
		}
		else if (state == JsonDefine::Pressed)
		{
			SetState(StatePressed);
		}
		else if (state == JsonDefine::Released)
		{
			SetState(StateReleased);
		}
	}
}
void JGameButton::Deactivate()
{
	JGameElement::Deactivate();
	JGameButton* exploredButton = gJGameManager.GetCurrentExploredButton();
	if (exploredButton && exploredButton == this)
	{
		gJGameManager.SetCurrentExploredButton(NULL);
	}
}