#include "JAppPch.h"
#include "JMainMenuScreen.h"
#include "App/Modules/JYesNoModule.h"
#include "App/Screens/JMainGameScreen.h"

using namespace J;
using namespace J::GAME;


JMainMenuScreen::JMainMenuScreen():mYesNoNewGameDialog(NULL)
{

}
JMainMenuScreen::~JMainMenuScreen()
{
	if (mYesNoNewGameDialog)
	{
		delete mYesNoNewGameDialog;
		mYesNoNewGameDialog = NULL;
	}
}
void JMainMenuScreen::Init()
{
	JGameScreen::Init(std::string("GUI\\Screens\\MainMenuScreen.json"), "MainMenuScreen");

	mYesNoNewGameDialog = new JYesNoModule();
	mYesNoNewGameDialog->Init("GUI\\Modules\\YesNoModule.json","YES_ID","NO_ID","NEWGAME_DESC_ID");
	auto yesCallback = std::bind(&JMainMenuScreen::ConfirmNewGameCallback, this, std::placeholders::_1, std::placeholders::_2);
	mYesNoNewGameDialog->OnYesReleased(this,yesCallback,NULL);
	auto noCallback = std::bind(&JMainMenuScreen::CancelNewGameCallback, this, std::placeholders::_1, std::placeholders::_2);
	mYesNoNewGameDialog->OnNoReleased(this, noCallback, NULL);
	
	auto newGameCallback = std::bind(&JMainMenuScreen::NewGameCallback, this, std::placeholders::_1, std::placeholders::_2);
	static_cast<JGameButton*>(GetGameModule("NewGame_ButtonLink")->GetElement("ButtonLink"))->AddOnReleased(this, newGameCallback, NULL);
	
	auto continueCallback = std::bind(&JMainMenuScreen::ContinueCallback, this, std::placeholders::_1, std::placeholders::_2);
	static_cast<JGameButton*>(GetGameModule("Continue_ButtonLink")->GetElement("ButtonLink"))->AddOnReleased(this, continueCallback, NULL);
}
void  JMainMenuScreen::GoToMainGameScreen()
{
	gJSharedModules.MainGameScreen = new GAME::JMainGameScreen();
	((JMainGameScreen*)gJSharedModules.MainGameScreen)->Init();
	gJGameManager.SetCurrentScreen(gJSharedModules.MainGameScreen, true);
}
void JMainMenuScreen::NewGameCallback(JGameButton* caller, json params)
{
	LOG_INFO(0, "NewGameCallback\n", 0);
	if (!gGameEngine.GetGameSaving().mIsPlaying)
	{
		ConfirmNewGameCallback(caller,params);
	}
	else
	{
		mYesNoNewGameDialog->Activate();
	}
}
void JMainMenuScreen::ConfirmNewGameCallback(JGameButton* caller, json params)
{
	LOG_INFO(0, "ConfirmNewGameCallback\n", 0);
	gGameEngine.NewGame();
	GoToMainGameScreen();
}
void JMainMenuScreen::CancelNewGameCallback(JGameButton* caller, json params)
{
	LOG_INFO(0, "CancelNewGameCallback\n", 0);
	mYesNoNewGameDialog->Deactivate();
}
void JMainMenuScreen::ContinueCallback(JGameButton* caller, json params)
{
	LOG_INFO(0, "Continue Callback\n", 0);
	gGameEngine.ContinueGame();
	GoToMainGameScreen();
}
void JMainMenuScreen::Clear()
{
	JGameScreen::Clear();
	mYesNoNewGameDialog->Clear();
}
void JMainMenuScreen::Update()
{
	JGameScreen::Update();
	mYesNoNewGameDialog->Update();
}
void JMainMenuScreen::Activate()
{
	JGameScreen::Activate();
	JGameButton* continueButton = static_cast<JGameButton*>(GetGameModule("Continue_ButtonLink")->GetElement("ButtonLink"));
	if (!gGameEngine.GetGameSaving().mIsPlaying)
	{
		continueButton->SetState(ButtonState::StateDisabled);
	}
	else
	{
		continueButton->SetState(ButtonState::StateNormal);
	}
}
void JMainMenuScreen::Deactivate()
{
	JGameScreen::Deactivate();
	mYesNoNewGameDialog->Deactivate();
}