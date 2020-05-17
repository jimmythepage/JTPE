#include "JAppPch.h"
#include "JBootScreen.h"
#include "App/Modules/JOkModule.h"
#include "JMainMenuScreen.h"

using namespace J;
using namespace J::GAME;


JBootScreen::JBootScreen():mBootModule(NULL), mOkNetDialog(NULL)
{

}
JBootScreen::~JBootScreen()
{
	if (mOkNetDialog)
	{
		delete mOkNetDialog;
		mOkNetDialog = NULL;
	}
}
void JBootScreen::Init()
{
	JGameScreen::Init(std::string("GUI\\Screens\\BootScreen.json"), "BootScreen");

	mAlphaTween.Init("BootAlphaTween", 3000, 0.f, 1.f);
	mAlphaTween.SetPlayStyle(PINGPONG);
	mAlphaTween.SetLoop(false);
	mBootModule = GetGameModule("BootLogoLink");
	std::string netError = "";
	bool loaded = gJNetManager.StartNetProvider(netError);
	if (!loaded)
	{
		mOkNetDialog = new JOkModule();
		mOkNetDialog->Init("GUI\\Modules\\OkModule.json", "OK_ID", netError);
		auto okCallback = std::bind(&JBootScreen::OkNetCallback, this, std::placeholders::_1, std::placeholders::_2);
		mOkNetDialog->OnOkReleased(this, okCallback, NULL);
		LOG_INFO(0, "Net Start error:%s \n", netError.c_str());
	}
	else
	{
		LOG_INFO(0, "Net start success \n", 0);
	}
	mTestRequest.Init("TestGetRequest");
	mTestRequest.Request("http://httpbin.org/response-headers?key=eee");
}
void JBootScreen::OkNetCallback(JGameButton* caller, json params)
{
	gJEngine.StopEngine();
}
void JBootScreen::Clear()
{
	JGameScreen::Clear();
	if (mOkNetDialog)
	{
		mOkNetDialog->Clear();
	}
	mAlphaTween.Clear();
}
void JBootScreen::Update()
{
	JGameScreen::Update();
	if (mOkNetDialog)
	{
		mOkNetDialog->Update();
	}
	mAlphaTween.Update();
	if (mAlphaTween.IsTweening())
	{
		J::RENDER::JRenderableProperties bootModuleProperties = mBootModule->GetRelProperties();
		bootModuleProperties.A = mAlphaTween.GetValue();
		mBootModule->SetRelProperties(bootModuleProperties);
	}
	bool skip = false;
#ifdef _JDEBUG_
	skip = gJInputManager.GetInputPointer()->GetPointerReleased(Mouse_Left);
#endif // _JDEBUG_

	if (mAlphaTween.IsFinished() 
		|| skip)//ALpha is finished, we can now go to Main Menu
	{
		if (mOkNetDialog && !mOkNetDialog->IsActive())
		{
			mOkNetDialog->Activate();
		}
		else if(!mOkNetDialog)
		{
			GoToMain();
		}
	}
}
void  JBootScreen::GoToMain()
{
	gJSharedModules.MainMenuScreen = new GAME::JMainMenuScreen();
	((JMainMenuScreen*)gJSharedModules.MainMenuScreen)->Init();
	gJGameManager.SetCurrentScreen(gJSharedModules.MainMenuScreen, true);
}
void JBootScreen::Activate()
{
	JGameScreen::Activate();
	mAlphaTween.StartTween();
}
void JBootScreen::Deactivate()
{
	JGameScreen::Deactivate();
	if (mOkNetDialog)
	{
		mOkNetDialog->Deactivate();
	}
}