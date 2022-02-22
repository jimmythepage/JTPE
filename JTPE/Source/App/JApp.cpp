#include "JAppPch.h"
#include "JApp.h"
#include "App\Screens\JBootScreen.h"
#include "App\Screens\JSharedModules.h"

using namespace J;
using namespace J::APP;


JApp::JApp()
{

}
JApp::~JApp()
{
	
}
void JApp::Init(const std::string name)
{
	JBase::Init(name);
	gJEngine.Init(name,"./JData/Settings.json", /*ENGINE::EngineOptions::USES_BLOB|*/ENGINE::USES_STEAM);
	gJTextDB.SetLanguage(J::BASE::Language::ENG);
	gGameEngine.Init("GameEngine");
	GAME::JBootScreen* bootScreen = new GAME::JBootScreen();
	bootScreen->Init();
	gJGameManager.SetCurrentScreen(bootScreen);
}
void JApp::Clear()
{
	JBase::Clear();
	gGameEngine.Clear();
	gJEngine.Clear();
}
void JApp::StopApp()
{
	gJEngine.StopEngine();
}
bool JApp::IsReadyToShut()
{
	return gJEngine.IsReadyToShut();
}
void JApp::Update()
{
	JBase::Update();
	gJEngine.Update();
	gGameEngine.Update();
}
void JApp::Activate()
{
	JBase::Activate();
	gJEngine.Activate();
	gGameEngine.Activate();
}
void JApp::Deactivate()
{
	JBase::Deactivate();
	gJEngine.Deactivate();
	gGameEngine.Deactivate();
}