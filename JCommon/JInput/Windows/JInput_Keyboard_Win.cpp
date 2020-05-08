#include "JCommonPch.h"
#include "JInput/Windows/JInput_Keyboard_Win.h"

using namespace J;
using namespace J::INPUT;

JInputKeyboardWin::JInputKeyboardWin()
{

}
JInputKeyboardWin::~JInputKeyboardWin()
{

}
void JInputKeyboardWin::Init(const std::string name)
{
	JBase::Init(name);
}
void JInputKeyboardWin::Clear()
{
}
void JInputKeyboardWin::Update()
{
	//TODO MULTIPLE KEYS AT THE SAME TIME IF NEEDED
	char keyCode = Key_None;
#if defined (__SDL__)
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) 
	{
		keyCode = Key_Escape;
	}
	else if (state[SDL_SCANCODE_LSHIFT])
	{
		keyCode = Key_LShift;
	}
	else if (state[SDL_SCANCODE_SPACE])
	{
		keyCode = Key_Space;
	}
	else if (state[SDL_SCANCODE_F])
	{
		keyCode = Key_F;
	}
	else if (state[SDL_SCANCODE_G])
	{
		keyCode = Key_G;
	}
	else if (state[SDL_SCANCODE_H])
	{
		keyCode = Key_H;
	}
	else if (state[SDL_SCANCODE_R])
	{
		keyCode = Key_R;
	}
#else
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		keyCode = Key_Escape;
	}
	else if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
	{
		keyCode = Key_LShift;
	}
	else if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		keyCode = Key_Space;
	}
	else if (GetAsyncKeyState('F') & 0x8000)
	{
		keyCode = Key_F;
	}
	else if (GetAsyncKeyState('G') & 0x8000)
	{
		keyCode = Key_G;
	}
	else if (GetAsyncKeyState('H') & 0x8000)
	{
		keyCode = Key_H;
	}
	else if (GetAsyncKeyState('R') & 0x8000)
	{
		keyCode = Key_R;
	}
#endif
	HandleStateChange(keyCode);
}
void JInputKeyboardWin::Activate()
{
}
void JInputKeyboardWin::Deactivate()
{

}