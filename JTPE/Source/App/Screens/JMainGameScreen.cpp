#include "JAppPch.h"
#include "JMainGameScreen.h"
#include "App/Modules/JYesNoModule.h"
#include "App/Screens/JMainMenuScreen.h"

using namespace J;
using namespace J::GAME;


JMainGameScreen::JMainGameScreen()
{

}
JMainGameScreen::~JMainGameScreen()
{
}
void JMainGameScreen::Init()
{
	JGameScreen::Init(std::string("GUI\\Screens\\MainGameScreen.json"), "MainGameScreen");

	auto backToMainCallback = std::bind(&JMainGameScreen::BackToMainCallback, this, std::placeholders::_1, std::placeholders::_2);
	static_cast<JGameButton*>(GetGameModule("BackToMain_ButtonLink")->GetElement("ButtonLink"))->AddOnReleased(this, backToMainCallback, NULL);
}
void  JMainGameScreen::GoBackToMainMenu()
{
	gJSharedModules.MainMenuScreen = new GAME::JMainMenuScreen();
	((JMainMenuScreen*)gJSharedModules.MainMenuScreen)->Init();
	gJGameManager.SetCurrentScreen(gJSharedModules.MainMenuScreen, true);
}
void JMainGameScreen::BackToMainCallback(JGameButton* caller, json params)
{
	LOG_INFO(0, "BackToMainMenu\n", 0);
	GoBackToMainMenu();
}
void JMainGameScreen::Clear()
{
	JGameScreen::Clear();
}
void JMainGameScreen::Update()
{
	JGameScreen::Update();
}
void JMainGameScreen::Activate()
{
	JGameScreen::Activate();
}
void JMainGameScreen::Deactivate()
{
	JGameScreen::Deactivate();
}