#include "JCommonPch.h"

using namespace J;
using namespace J::GAME;

JGameManager::JGameManager():mCurrentScreen(NULL),mPrevScreen(NULL), mDebugLoggerState(None), mCurrentExploredButton(NULL),
mLoadCached(true), mCurrentLevel(NULL), mPrevLevel(NULL), mCurrentCamera(NULL), mNeedCleaning(false)
{
}
JGameManager::~JGameManager()
{
	delete mDebugLogger;
	mDebugLogger = NULL;
	mCurrentScreen = NULL;
	mPrevScreen = NULL;
	mCurrentLevel = NULL;
	mPrevLevel = NULL;
	mCurrentCamera = NULL;
}
void JGameManager::ClearUnusedElements()
{
	for (JBase* object : mToDelete)
	{
		if (object)
		{
			object->Clear();
			delete object;
			object = NULL;
		}
	}
	mToDelete.clear();
}
JGameManager & JGameManager::GetSingleton()
{
	static JGameManager _singleton;
	return _singleton;
}
void JGameManager::Init(const std::string name)
{
	JBase::Init(name);
	LOG_INFO(0, "%s is initialized\n", mName.c_str());
	mToDelete.clear();
	mDebugLogger = new J::RENDER::JText();
	J::RENDER::JRenderableProperties debugLoggerProperties;
	int size = 25;
	debugLoggerProperties.Position.x = 0;
	debugLoggerProperties.Position.y = (float)gJEngine.GetSettings()->LogicalHeight / 2.f-size;
	debugLoggerProperties.Origin.x = 0.5;
	debugLoggerProperties.Origin.y = 0.5;
	debugLoggerProperties.Z = 10000;
	debugLoggerProperties.ZAdd = 10000;
	debugLoggerProperties.FontSize = size;
	mDebugLogger->Init("GUI\\Fonts\\arial.ttf", "Debug Logger", debugLoggerProperties);
	mDebugLogger->SetText("Debug Logger");
}
void JGameManager::Clear()
{
	JBase::Clear();
	ClearUnusedElements();
	mCurrentExploredButton = NULL;
	if (mDebugLogger)
	{
		mDebugLogger->Clear();
		delete mDebugLogger;
		mDebugLogger = NULL;
	}
	if (mCurrentScreen)
	{
		mCurrentScreen->Clear();
		mCurrentScreen = NULL;
	}
	if (mCurrentLevel)
	{
		mCurrentLevel->Clear();
		mCurrentLevel = NULL;
	}
	mJsonScreens.clear();
	mJsonModules.clear();
}
void JGameManager::Update()
{
	JBase::Update();
	if (mCurrentScreen)
	{
		mCurrentScreen->Update();
	}
	if (mCurrentLevel)
	{
		mCurrentLevel->Update();
	}
	if (mCurrentCamera)
	{
		mCurrentCamera->Update();
	}
	switch (mDebugLoggerState)
	{
	case J::GAME::None:
		mDebugLogger->SetText("");
		break;
	case J::GAME::FPS:
	{
		std::string sFps = std::string("FPS:");
		clock_t  diff = clock() - mLastTime;
		unsigned int fps = (unsigned int)(1.f / (((float)diff) / CLOCKS_PER_SEC));
		sFps += std::to_string(fps);
		mLastTime = clock();
		mDebugLogger->SetText(sFps);
		break;
	}
	default:
		break;
	}
	if (mNeedCleaning)
	{
		ClearUnusedElements();
		mNeedCleaning = false;
	}
}
void JGameManager::LoadGameModule(JGameModule* module, json gameModule)
{
	J::RENDER::JRenderableProperties properties;
	if (!gameModule[JsonDefine::ZAdd].is_null())
	{
		properties.ZAdd = gameModule[JsonDefine::ZAdd];
	}
	if (!gameModule[JsonDefine::Scale].is_null())
	{
		auto scale = gameModule[JsonDefine::Scale];
		properties.Scale.x = scale[0];
		properties.Scale.y = scale[1];
	}
	if (!gameModule[JsonDefine::Color].is_null())
	{
		auto color = gameModule[JsonDefine::Color];
		properties.R = color[0];
		properties.G = color[1];
		properties.B = color[2];
		properties.A = color[3];
	}
	if (!gameModule[JsonDefine::Position].is_null())
	{
		auto position = gameModule[JsonDefine::Position];
		properties.Position.x = position[0];
		properties.Position.y = position[1];
	}
	if (!gameModule[JsonDefine::Rot].is_null())
	{
		properties.Rot = gameModule[JsonDefine::Rot];
	}
	if (!gameModule[JsonDefine::Visible].is_null())
	{
		properties.Visible = gameModule[JsonDefine::Visible];
	}
	module->Init(gameModule[JsonDefine::ModulePath], properties, gameModule);
}
void JGameManager::SetCurrentScreen(JGameScreen* screen, bool cleanPrevious)
{
	mCurrentExploredButton = NULL;
	if (mCurrentScreen)
	{
		mCurrentScreen->Deactivate();
		if (cleanPrevious)
		{
			mPrevScreen = NULL;
			mToDelete.push_back(mCurrentScreen);
		}
		else
		{
			mPrevScreen = mCurrentScreen;
		}
	}
	mCurrentScreen = screen;
	if (mCurrentScreen)
	{
		mCurrentScreen->Activate();
	}
	mNeedCleaning = true;
}
void JGameManager::SetCurrentCamera(JGameCamera* camera)
{
	mCurrentCamera = camera;
}
void JGameManager::SetCurrentLevel(JGameLevel* level)
{
	mCurrentExploredButton = NULL;
	if (mCurrentLevel)
	{
		mCurrentLevel->Deactivate();
		mPrevLevel = mCurrentLevel;
	}
	mCurrentLevel = level;
	if (mCurrentLevel)
	{
		mCurrentLevel->Activate();
	}
}
json JGameManager::GetJsonModule(std::string filepath)
{
	if (!mLoadCached)
	{
		mJsonModules.clear();
	}
	json module = mJsonModules[filepath];
	if (module.is_null())
	{
		module = LoadJson(filepath);
		if (!module.is_null())
		{
			mJsonModules[filepath] = module;
		}
	}
	return module;
}
json JGameManager::GetJsonScreen(std::string filepath)
{
	if (!mLoadCached)
	{
		mJsonScreens.clear();
	}
	json screen=mJsonScreens[filepath];
	if (screen.is_null())
	{
		screen = LoadJson(filepath);
		if (!screen.is_null())
		{
			mJsonScreens[filepath] = screen;
		}
	}
	return screen;
}
json JGameManager::LoadJson(std::string filepath)
{
	J::BASE::JFile fileJson;
	fileJson.Init(filepath);
	if (!fileJson.Load(filepath, false))
	{
		return json();
	}
	auto module = json::parse(fileJson.GetStringData());
	fileJson.Unload();
	return module;
}
void JGameManager::Activate()
{
	JBase::Activate();
#ifdef _JDEBUG_
	mDebugLogger->Activate();
#endif // _JDEBUG_
	LOG_INFO(0, "%s is Activated\n", mName.c_str());
}
void JGameManager::Deactivate()
{
	JBase::Deactivate();
#ifdef _JDEBUG_
	mDebugLogger->Deactivate();
#endif // _JDEBUG_
	if (mCurrentScreen)
	{
		mCurrentScreen->Deactivate();
	}
	if (mCurrentLevel)
	{
		mCurrentLevel->Deactivate();
	}
	LOG_INFO(0, "%s is Deactivated\n", mName.c_str());
}