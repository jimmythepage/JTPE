#include "JCommonPch.h"

using namespace J;
using namespace J::RENDER;
using namespace J::GAME;


JGameScreen::JGameScreen()
{

}
JGameScreen::~JGameScreen()
{

}
void JGameScreen::Init(const json screenJson, const std::string name)
{
	Init(name);
	Init(screenJson[JsonDefine::Name]);
	auto elements = screenJson[JsonDefine::Modules];
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		JGameModule* module = new JGameModule();
		gJGameManager.LoadGameModule(module, elements[i]);
		if (!module->GetAppLink().empty())
		{
			mRegisteredAppLinks.insert(std::pair<std::string, JGameModule*>(module->GetAppLink(), module));
		}
		mChilds.push_back(module);
	}
}
void JGameScreen::Init(const std::string filepath, const std::string name)
{
	Init(name);
	std::string path = gJEngine.GetSettings()->DataFolder +filepath;
	json module = gJGameManager.GetJsonScreen(path);
	Init(module[JsonDefine::Name]);
	auto elements = module[JsonDefine::Modules];
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		JGameModule* module = new JGameModule();
		gJGameManager.LoadGameModule(module, elements[i]);
		if (!module->GetAppLink().empty())
		{
			mRegisteredAppLinks.insert(std::pair<std::string, JGameModule*>(module->GetAppLink(), module));
		}
		mChilds.push_back(module);
	}
}
JGameModule* JGameScreen::GetGameModule(std::string appLink)
{
	JGameModule* element = NULL;
	std::pair <std::multimap<std::string, JGameModule*>::iterator, std::multimap<std::string, JGameModule*>::iterator> ret;
	ret = mRegisteredAppLinks.equal_range(appLink);
	for (std::multimap<std::string, JGameModule*>::iterator it = ret.first; it != ret.second; ++it)
	{
		element = (*it).second;
		break;
	}
	return element;
}
std::vector<JGameModule*> JGameScreen::GetGameModules(std::string appLink)
{
	std::vector<JGameModule*> elements;
	std::pair <std::multimap<std::string, JGameModule*>::iterator, std::multimap<std::string, JGameModule*>::iterator> ret;
	ret = mRegisteredAppLinks.equal_range(appLink);
	for (std::multimap<std::string, JGameModule*>::iterator it = ret.first; it != ret.second; ++it)
	{
		elements.push_back((*it).second);
	}
	return elements;
}
void JGameScreen::Init(const std::string name)
{
	JGameElement::Init(name);
}
void JGameScreen::Clear()
{
	JGameElement::Clear();
}
void JGameScreen::Update()
{
	JGameElement::Update();
}
void JGameScreen::Activate()
{
	JGameElement::Activate();
}
void JGameScreen::Deactivate()
{
	JGameElement::Deactivate();
}