#include "JCommonPch.h"

using namespace J;
using namespace J::BASE;

JTextDB::JTextDB():mLanguage(ENG)
{
}
JTextDB::~JTextDB()
{
}
JTextDB & JTextDB::GetSingleton()
{
	static JTextDB _singleton;
	return _singleton;
}
void JTextDB::Init(const std::string name)
{
	JBase::Init(name);
	std::string path = gJEngine.GetSettings()->DataFolder;
	path += "GUI\\TextDB.json";
	JFile file;
	file.Init(path);
	file.Load(path,false);
	json db = json::parse(file.GetStringData());
	auto entries = db["Entries"];
	for (unsigned int i = 0; i < entries.size(); i++)
	{
		auto entry = entries[i];
		std::vector<std::string> t;
		t.push_back(entry["ENG"]);
		t.push_back(entry["ITA"]);
		mTextEntries[entry["ID"]] = t;
	}
	file.Unload();
}
std::string	JTextDB::GetTextEntry(std::string textID)
{
	std::string entry;
	if (mTextEntries.count(textID) == 1)
	{
		entry = mTextEntries[textID][(int)mLanguage];
	}
	if (entry.empty())
	{
		entry = textID;
	}
	return entry;
}
void JTextDB::Clear()
{
	JBase::Clear();
	mTextEntries.clear();
}