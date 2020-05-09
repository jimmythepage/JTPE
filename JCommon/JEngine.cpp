#include "JCommonPch.h"

using namespace J;
using namespace J::ENGINE;

JEngine::JEngine() :mIsEngineRunning(false)
{
}
JEngine::~JEngine()
{
}
JEngine & JEngine::GetSingleton()
{
	static JEngine _singleton;
	return _singleton;
}
void JEngine::Init(const std::string name, const std::string absBasePath, const std::string settingsPath, unsigned int options)
{
	JBase::Init(name);

	J::BASE::JFile fileJson;
	fileJson.Init(settingsPath);
	if (!fileJson.Load(settingsPath, false))
	{
		EXIT(1);
	}
	json settings = json::parse(fileJson.GetStringData());
	fileJson.Unload();

	mSettings.ScreenWidth = settings["ScreenWidth"];
	mSettings.ScreenHeight = settings["ScreenHeight"];
	mSettings.LogicalHeight = settings["LogicalHeight"];
	mSettings.FullScreen = settings["FullScreen"];
	mSettings.LogicalWidth = (mSettings.LogicalHeight*mSettings.ScreenWidth) / mSettings.ScreenHeight;
	std::string dataFolder = settings["DataFolder"];
	mSettings.DataFolder = absBasePath + dataFolder + "/";
	mSettings.LogicalRatioX = (float)mSettings.ScreenWidth / (float)mSettings.LogicalWidth;
	mSettings.LogicalRatioY = (float)mSettings.ScreenHeight / (float)mSettings.LogicalHeight;

	//ORDER IS IMPORTANT
	gJTextDB.Init("JTextDB");
	gJFileManager.Init("JFileManager", ((options & USES_BLOB) > 0));
	gJSavingSystem.Init("JSavingSystem");
	gJRenderManager.Init("JRenderManager", name);
	gJInputManager.Init("JInputManager");
	gJAudioManager.Init("JAudioManager");
	NET::NET_PROVIDER provider = NET::NET_PROVIDER::NONE;
	if ((options & USES_BLOB) > 0)
	{
		provider = NET::NET_PROVIDER::STEAM;
	}
	gJNetManager.Init("JNetManager", provider);
	gJGameManager.Init("JGameManager");
	gJPhysicsManager.Init("JPhysicsManager");
	LOG_INFO(0, "Engine %s is initialized\n", mName.c_str());
}
void JEngine::Init(const std::string name, const std::string settingsPath, unsigned int options)
{
	Init(name, "", settingsPath, options);
}
void JEngine::Update()
{
	//ORDER IS IMPORTANT
	gJInputManager.Update();
	gJFileManager.Update();
	gJNetManager.Update();
	gJGameManager.Update();
	gJPhysicsManager.Update();
	gJSavingSystem.Update();
	gJRenderManager.Update();
	gJAudioManager.Update();
}
void JEngine::StopEngine()
{
	mIsEngineRunning = false;
}
bool JEngine::IsReadyToShut()
{
	if (IsEngineRunning())
		return false;
	else
		return true;
}
bool JEngine::IsEngineRunning()
{
	return mIsEngineRunning;
}
void JEngine::Clear()
{
	JBase::Clear();
	//ORDER IS IMPORTANT
	gJPhysicsManager.Clear();
	gJGameManager.Clear();
	gJNetManager.Clear();
	gJInputManager.Clear();
	gJAudioManager.Clear();
	gJRenderManager.Clear();
	gJSavingSystem.Clear();
	gJFileManager.Clear();
	LOG_INFO(0, "Engine %s is Cleared\n", mName.c_str());
}
void JEngine::Activate()
{
	LOG_INFO(0, "Engine %s is Activating\n", mName.c_str());
	mIsEngineRunning = true;
	JBase::Activate();
	//ORDER IS IMPORTANT
	gJInputManager.Activate();
	gJFileManager.Activate();
	gJSavingSystem.Activate();
	gJNetManager.Activate();
	gJGameManager.Activate();
	gJPhysicsManager.Activate();
	gJRenderManager.Activate();
	gJAudioManager.Activate();
}
void JEngine::Deactivate()
{
	JBase::Deactivate();
	//ORDER IS IMPORTANT
	gJInputManager.Deactivate();
	gJGameManager.Deactivate();
	gJPhysicsManager.Deactivate();
	gJNetManager.Deactivate();
	gJAudioManager.Deactivate();
	gJRenderManager.Deactivate();
	gJSavingSystem.Deactivate();
	gJFileManager.Deactivate();
	LOG_INFO(0, "Engine %s is Deactivated\n", mName.c_str());
}