#include "JCommonPch.h"

using namespace J;
using namespace J::BASE;
using namespace J::INPUT;

JInputManager::JInputManager():mJInputKeyboard(NULL), mJInputPointer(NULL)
{
}
JInputManager::~JInputManager()
{
	
}
JInputManager & JInputManager::GetSingleton()
{
	static JInputManager _singleton;
	return _singleton;
}
void JInputManager::Init(const std::string name)
{
	JBase::Init(name);
	if (!mJInputKeyboard)
	{
#ifdef __WINDOWS__
		mJInputKeyboard = new JInputKeyboardWin();
#else
		mJInputKeyboard = new JInputKeyboard();
#endif
		mJInputKeyboard->Init("JInputKeyboard");
	}
	if (!mJInputPointer)
	{
#ifdef __WINDOWS__
		mJInputPointer = new JInputPointerWin();
#else
		mJInputPointer = new JInputPointer();
#endif
		mJInputPointer->Init("JInputPointer");
	}
}
void JInputManager::Clear()
{
	JBase::Clear();
	if (mJInputKeyboard)
	{
		mJInputKeyboard->Clear();
		delete mJInputKeyboard;
		mJInputKeyboard = NULL;
	}
	if (mJInputPointer)
	{
		mJInputPointer->Clear();
		delete mJInputPointer;
		mJInputPointer = NULL;
	}
}
void JInputManager::Update()
{
	mJInputKeyboard->Update();
	mJInputPointer->Update();
}
void JInputManager::Activate()
{
	JBase::Activate();
	mJInputKeyboard->Activate();
	mJInputPointer->Activate();
	LOG_INFO(0, "%s is Activated\n", mName.c_str());
}
void JInputManager::Deactivate()
{
	JBase::Deactivate();
	mJInputKeyboard->Deactivate();
	mJInputPointer->Deactivate();
	LOG_INFO(0, "%s is Deactivated\n", mName.c_str());
}