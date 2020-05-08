#include "JCommonPch.h"
#include "JSavingSystem.h"

using namespace J;
using namespace J::BASE;


JSavingSystem::JSavingSystem() :mCurrentDataKey("Default")
{
}
JSavingSystem::~JSavingSystem()
{
}
JSavingSystem & JSavingSystem::GetSingleton()
{
	static JSavingSystem _singleton;
	return _singleton;
}
void JSavingSystem::Init(const std::string name)
{
	JBase::Init(name);
}
void JSavingSystem::ActivateData(const std::string dataKey)
{
	mCurrentDataKey = dataKey;
	if (mDatas.count(mCurrentDataKey) == 0)
	{
		std::pair<std::string, json > pair(mCurrentDataKey, json());
		mDatas.insert(pair);
	}
}
bool JSavingSystem::LoadData(const std::string path)
{
	mCurrentDataPath = path;
	JFile file;
	file.Init("Data " + mCurrentDataKey);
	bool loaded=file.Load(path,false);
	if (loaded)
	{
		mDatas[mCurrentDataKey]= json::parse(file.GetStringData());
		LOG_INFO(0, "Saving System has loaded %s\n", path.c_str());
	}
	else
	{
		LOG_INFO(0, "Saving System has failed loading %s\n", path.c_str());
	}
	file.Unload();
	file.Clear();
	return loaded;
}
bool JSavingSystem::SaveData()
{
	JFile file;
	file.Init("Data " + mCurrentDataKey);
	std::string jsonText = mDatas[mCurrentDataKey].dump();
	bool saved=file.Write(mCurrentDataPath, jsonText);
	if (saved)
	{
		LOG_INFO(0, "Saving System has saved %s\n", mCurrentDataPath.c_str());
	}
	else
	{
		LOG_INFO(0, "Saving System has failed saving %s\n", mCurrentDataPath.c_str());
	}
	file.Unload();
	file.Clear();
	return saved;
}
void JSavingSystem::ClearData()
{
	mDatas[mCurrentDataKey].clear();
}
json* const JSavingSystem::GetData()
{
	return &mDatas[mCurrentDataKey];
}
bool JSavingSystem::IsKeyExisting(const std::string key)
{
	auto found = mDatas[mCurrentDataKey].find(key);
	return (found != mDatas[mCurrentDataKey].end());
}
void JSavingSystem::SetString(const std::string key, const std::string value)
{
	mDatas[mCurrentDataKey][key] = value;
}
void JSavingSystem::SetInt(const std::string key, const int value)
{
	mDatas[mCurrentDataKey][key] = value;
}
void JSavingSystem::SetUnsignedInt(const std::string key, const unsigned int value)
{
	mDatas[mCurrentDataKey][key] = value;
}
void JSavingSystem::SetFloat(const std::string key, const float value)
{
	mDatas[mCurrentDataKey][key] = value;
}
void JSavingSystem::SetBool(const std::string key, const bool value)
{
	mDatas[mCurrentDataKey][key] = value;
}
void JSavingSystem::SetJson(const std::string key, const json value)
{
	mDatas[mCurrentDataKey][key] = value;
}
void JSavingSystem::SetVectorOfJson(const std::string key, const std::vector<json> value)
{
	mDatas[mCurrentDataKey][key] = value;
}
void JSavingSystem::Clear()
{
	JBase::Clear();
}
void JSavingSystem::Update()
{
	JBase::Update();
}
void JSavingSystem::Activate()
{
	JBase::Activate();
}
void JSavingSystem::Deactivate()
{
	JBase::Deactivate();
}