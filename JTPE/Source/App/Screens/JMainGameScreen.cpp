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

	auto playCallaback = std::bind(&JMainGameScreen::PlayResumeAudioClip, this, std::placeholders::_1, std::placeholders::_2);
	static_cast<JGameButton*>(GetGameModule("PlayResume_ButtonLink")->GetElement("ButtonLink"))->AddOnReleased(this, playCallaback, NULL);

	auto stopCallaback = std::bind(&JMainGameScreen::StopAudioClip, this, std::placeholders::_1, std::placeholders::_2);
	static_cast<JGameButton*>(GetGameModule("Stop_ButtonLink")->GetElement("ButtonLink"))->AddOnReleased(this, stopCallaback, NULL);

	mBGMusic.Init("BGGameMusic", "Audio\\sample.wav");
	mBGMusic.SetLoop(true);
	mBGMusic.Play();

	mVolumeFadeIn.Init("BootAlphaTween", 3000, 0.f, 128.f);
	mVolumeFadeIn.SetPlayStyle(FORWARD);
	mVolumeFadeIn.SetLoop(false);
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
void  JMainGameScreen::PlayResumeAudioClip(JGameButton* caller, json params)
{
	LOG_INFO(0, "PlayResumeAudioClip\n", 0);
	if (mBGMusic.IsPlaying())
	{
		mBGMusic.Pause();
	}
	else
	{
		mBGMusic.Play();
	}
}
void  JMainGameScreen::StopAudioClip(JGameButton* caller, json params)
{
	LOG_INFO(0, "StopAudioClip\n", 0);
	mBGMusic.Stop();
}
void JMainGameScreen::Clear()
{
	JGameScreen::Clear();
	mBGMusic.Clear();
	mVolumeFadeIn.Clear();
}
void JMainGameScreen::Update()
{
	JGameScreen::Update();
	mVolumeFadeIn.Update();
	if (mVolumeFadeIn.IsTweening())
	{
		mBGMusic.SetVolume((int)mVolumeFadeIn.GetValue());
	}
}
void JMainGameScreen::Activate()
{
	JGameScreen::Activate();
	mVolumeFadeIn.StartTween();
}
void JMainGameScreen::Deactivate()
{
	JGameScreen::Deactivate();
}