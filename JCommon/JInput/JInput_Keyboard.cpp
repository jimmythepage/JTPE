#include "JCommonPch.h"

using namespace J;
using namespace J::INPUT;

JInputKeyboard::JInputKeyboard(): mKeyCode(Key_None), mKeyState(Key_Idle)
{

}
JInputKeyboard::~JInputKeyboard()
{

}
void JInputKeyboard::Init(const std::string name)
{
	JBase::Init(name);
}
void JInputKeyboard::Clear()
{
}
void JInputKeyboard::Update()
{
}
bool JInputKeyboard::GetKeyHeld(char keyCode)
{
	return (mKeyState == Key_Held && mKeyCode == keyCode);
}
bool JInputKeyboard::GetKeyPressed(char keyCode)
{
	return (mKeyState == Key_Pressed && mKeyCode == keyCode);
}
void JInputKeyboard::HandleStateChange(char keyCode)
{
	if (keyCode == Key_None)
	{
		if (mKeyState == Key_Pressed || mKeyState == Key_Held)//RELEASE
		{
			mKeyCode = keyCode;
			mKeyState = Key_Released;
		}
		else//RESET
		{
			mKeyState = Key_Idle;
		}
	}
	else
	{
		if (mKeyCode == Key_None)//FIRST PRESS
		{
			mKeyCode = keyCode;
			mKeyState = Key_Pressed;
			LOG_INFO(0, "%c is pressed\n", mKeyCode);
		}
		else if (mKeyCode == keyCode)//HELD
		{
			mKeyState = Key_Held;
		}
	}
}
void JInputKeyboard::Activate()
{
}
void JInputKeyboard::Deactivate()
{

}