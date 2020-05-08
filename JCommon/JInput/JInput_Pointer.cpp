#include "JCommonPch.h"

using namespace J;
using namespace J::INPUT;

JInputPointer::JInputPointer():mMouseCode(Mouse_None), mPointerState(Pointer_Idle)
{

}
JInputPointer::~JInputPointer()
{

}
void JInputPointer::Init(const std::string name)
{
	JBase::Init(name);
}
bool JInputPointer::GetPointerPressed(char keyCode)
{
	return (mPointerState == Pointer_Pressed && mMouseCode == keyCode);
}
bool JInputPointer::GetPointerDown(char keyCode)
{
	return (mPointerState == Pointer_Held && mMouseCode == keyCode);
}
bool JInputPointer::GetPointerReleased(char keyCode)
{
	return (mPointerState == Pointer_Released && mMouseCode == keyCode);
}
void JInputPointer::HandleStateChange(char keyCode)
{
	if (keyCode == Mouse_None)
	{
		if (mPointerState == Pointer_Pressed || mPointerState == Pointer_Held)//RELEASE
		{
			mPointerState = Pointer_Released;
		}
		else//RESET
		{
			mMouseCode = keyCode;
			mPointerState = Pointer_Idle;
		}
	}
	else
	{
		if (mMouseCode == Mouse_None)//FIRST PRESS
		{
			mMouseCode = keyCode;
			mPointerState = Pointer_Pressed;
		}
		else if (mMouseCode == keyCode)//HELD
		{
			mPointerState = Pointer_Held;
		}
	}
}
void JInputPointer::Clear()
{
}
void JInputPointer::Update()
{
}
void JInputPointer::Activate()
{
}
void JInputPointer::Deactivate()
{

}