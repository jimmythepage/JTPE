#include "JCommonPch.h"

using namespace J;
using namespace J::RENDER;
using namespace J::GAME;


JGameModule::JGameModule()
{

}
JGameModule::~JGameModule()
{

}
void  JGameModule::Init(const std::string filepath)
{
	CalcAbsProperties();
	std::string path = gJEngine.GetSettings()->DataFolder;
	path += filepath;
	json module = gJGameManager.GetJsonModule(path);
	JGameElement::Init(module[JsonDefine::Name], module[JsonDefine::AppLink]);
	if (!GetAppLink().empty())
	{
		mRegisteredAppLinks.insert(std::pair<std::string, JGameElement*>(GetAppLink(), this));
	}
	auto elements = module[JsonDefine::JElements];
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		AddChild(LoadElement(elements[i],this));
	}
}
void JGameModule::Init(const std::string filepath, J::RENDER::JRenderableProperties properties, json extraParams)
{
	mRelProperties = properties;
	CalcAbsProperties();
	std::string path = gJEngine.GetSettings()->DataFolder;
	path += filepath;
	json module = gJGameManager.GetJsonModule(path);
	if (!extraParams[JsonDefine::AppLink].is_null())
	{
		JGameElement::Init(module[JsonDefine::Name], extraParams[JsonDefine::AppLink]);
	}
	else
	{
		JGameElement::Init(module[JsonDefine::Name], module[JsonDefine::AppLink]);
	}
	if (!GetAppLink().empty())
	{
		mRegisteredAppLinks.insert(std::pair<std::string, JGameElement*>(GetAppLink(), this));
	}
	auto elements= module[JsonDefine::JElements];
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		if (!extraParams[JsonDefine::TextAppLink].is_null())
		{
			elements[i][JsonDefine::TextAppLink] = extraParams[JsonDefine::TextAppLink];
		}
		AddChild(LoadElement(elements[i],this));
	}
}
JGameElement*  JGameModule::LoadElement(json gameElement, JGameElement* parent)
{
	std::string type = gameElement[JsonDefine::Type];
	JGameElement* element = NULL;
	if (type == JsonDefine::JGameSprite)
	{
		JGameSprite* sprite = new JGameSprite();
		sprite->SetParent(parent, false);
		sprite->Init(gameElement[JsonDefine::Name], gameElement[JsonDefine::AppLink], gameElement);
		element = sprite;
	}
	else if (type == JsonDefine::JGameButton)
	{
		JGameButton* button = new JGameButton();
		button->SetParent(parent, false);
		button->Init(gameElement[JsonDefine::Name], gameElement[JsonDefine::AppLink], gameElement);
		element = button;
	}
	else if (type == JsonDefine::JGameDraggable)
	{
		JGameDraggable* draggable = new JGameDraggable();
		draggable->SetParent(parent, false);
		draggable->Init(gameElement[JsonDefine::Name], gameElement[JsonDefine::AppLink], gameElement);
		element = draggable;
	}
	else if (type == JsonDefine::JGameText)
	{
		JGameText* text = new JGameText();
		text->SetParent(parent, false);
		text->Init(gameElement[JsonDefine::Name], gameElement[JsonDefine::AppLink], gameElement);
		element = text;
	}
	else if (type == JsonDefine::JGameModule)
	{
		JGameModule* module = new JGameModule();
		module->SetParent(parent, false);
		gJGameManager.LoadGameModule(module, gameElement);
		element = module;
	}
	J::RENDER::JRenderableProperties relProperties=element->GetRelProperties();
	relProperties.ZAdd += mRelProperties.ZAdd;
	element->SetRelProperties(relProperties);
	ASSERT(element);
	auto childs = gameElement[JsonDefine::Childs];
	for (unsigned int i = 0; i < childs.size(); i++)
	{
		element->AddChild(LoadElement(childs[i],this));
	}
	if (type == JsonDefine::JGameButton)
	{
		static_cast<JGameButton*>(element)->InitButtonText();
	}
	if (!element->GetAppLink().empty())
	{
		mRegisteredAppLinks.insert(std::pair<std::string, JGameElement*>(element->GetAppLink(), element));
	}
	return element;
}
JGameElement* JGameModule::GetElement(std::string appLink)
{
	JGameElement* element = NULL;
	std::pair <std::multimap<std::string, JGameElement*>::iterator, std::multimap<std::string, JGameElement*>::iterator> ret;
	ret = mRegisteredAppLinks.equal_range(appLink);
	for (std::multimap<std::string, JGameElement*>::iterator it = ret.first; it != ret.second; ++it)
	{
		element = (*it).second;
		break;
	}
	return element;
}
std::vector<JGameElement*> JGameModule::GetElements(std::string appLink)
{
	std::vector<JGameElement*> elements;
	std::pair <std::multimap<std::string, JGameElement*>::iterator, std::multimap<std::string, JGameElement*>::iterator> ret;
	ret = mRegisteredAppLinks.equal_range(appLink);
	for (std::multimap<std::string, JGameElement*>::iterator it = ret.first; it != ret.second; ++it)
	{
		elements.push_back((*it).second);
	}
	return elements;
}
void JGameModule::Clear()
{
	JGameElement::Clear();
	mRegisteredAppLinks.clear();
}
void JGameModule::Update()
{
	JGameElement::Update();
}
void JGameModule::Activate()
{
	JGameElement::Activate();
}
void JGameModule::Deactivate()
{
	JGameElement::Deactivate();
}