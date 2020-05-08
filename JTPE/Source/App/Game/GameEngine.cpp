#include "JAppPch.h"
#include "GameEngine.h"

using namespace J;
using namespace J::APP;


GameEngine::GameEngine()
{
}
GameEngine::~GameEngine()
{
}
GameEngine & GameEngine::GetSingleton()
{
	static GameEngine _singleton;
	return _singleton;
}
void GameEngine::Init(const std::string name)
{
	BASE::JBase::Init(name);
	LoadGameData();
	gJSavingSystem.ActivateData("save");
	LoadSaveData();

	/* Saving Systems samples
	bool alreadyRunned = data->at(alreadyRunnedKey);
	mGameSettings=GameSettings{ "prova",13 };
	json j = mGameSettings;
	GameSettings g2 = j.get<GameSettings>();*/
}
void GameEngine::NewGame()
{
	ClearSaveData();
	mGameSaving.mIsPlaying = true;
	Save();
}
void GameEngine::ContinueGame()
{

}
void GameEngine::GameOver()
{
	ClearSaveData();
}
void GameEngine::LoadGameData()
{
	using namespace BASE;
}
void GameEngine::LoadSaveData()
{
	gJSavingSystem.LoadData("./" + gJEngine.GetSettings()->DataFolder + "save.json");
	const json* data = gJSavingSystem.GetData();
	if (!gJSavingSystem.IsKeyExisting(AlreadyRunnedKey))
	{
		gJSavingSystem.SetBool(AlreadyRunnedKey, true);
		Save();
	}
	gJSavingSystem.GetData()->at(GameSavingKey).get_to(mGameSaving);
}
void GameEngine::Save()
{
	gJSavingSystem.SetJson(GameSavingKey, mGameSaving);
	gJSavingSystem.SaveData();
}
void GameEngine::ClearSaveData()
{
	//WE SAVE OLD DATA
	GameSaving oldSaving = mGameSaving;
	//WE CLEAR
	gJSavingSystem.ClearData();
	//WE LOAD (THIS SHOULD CREATE NEW DATA)
	LoadSaveData();
	//WE COPY WHAT WE WANT TO KEEP FROM PREVIOUS DATA
	mGameSaving.mIsPlaying = false;
	//WE SAVE
	Save();
}
void GameEngine::Clear()
{
	BASE::JBase::Clear();
}
void GameEngine::Update()
{
	BASE::JBase::Update();
}
void GameEngine::Activate()
{
	BASE::JBase::Activate();
}
void GameEngine::Deactivate()
{
	BASE::JBase::Deactivate();
}