#ifndef JINPUTDEFINES
#define JINPUTDEFINES

enum JKeyboardCode
{
	Key_None = 0,
	Key_Escape,
	Key_LShift,
	Key_Space,
	Key_F,
	Key_G,
	Key_H,
	Key_R
};

enum JKeyState
{
	Key_Idle=0,
	Key_Pressed,
	Key_Held,
	Key_Released
};

enum JMouseCode
{
	Mouse_None=0,
	Mouse_Left,
	Mouse_Right,
	Mouse_Middle
};
enum JPointerState
{
	Pointer_Idle=0,
	Pointer_Pressed,
	Pointer_Held,
	Pointer_Released
};


#endif // !JINPUTDEFINES
