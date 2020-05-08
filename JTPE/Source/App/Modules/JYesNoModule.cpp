#include "JAppPch.h"
#include "JYesNoModule.h"

using namespace J;
using namespace J::GAME;


JYesNoModule::JYesNoModule()
{

}
JYesNoModule::~JYesNoModule()
{
}
void JYesNoModule::Init(const std::string modulePath, const std::string yesTextID, const std::string noTextID, const std::string descriptionTextID)
{
	JGameModule::Init(modulePath);
	JGameText* yesText = static_cast<JGameText*>(
		GetElement("Yes_ButtonLink")->GetChild("ButtonLink")->GetChild("ButtonText"));
	yesText->SetText(gJTextDB.GetTextEntry(yesTextID));
	JGameText* noText = static_cast<JGameText*>(
		GetElement("No_ButtonLink")->GetChild("ButtonLink")->GetChild("ButtonText"));
	noText->SetText(gJTextDB.GetTextEntry(noTextID));
	JGameText* descText = static_cast<JGameText*>(GetElement("YesNoTextLink"));
	descText->SetText(gJTextDB.GetTextEntry(descriptionTextID));
}
void  JYesNoModule::OnYesReleased(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params)
{
	static_cast<JGameButton*>(GetElement("Yes_ButtonLink")->GetChild("ButtonLink"))->AddOnReleased(caller, function, params);
}
void  JYesNoModule::OnNoReleased(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params)
{
	static_cast<JGameButton*>(GetElement("No_ButtonLink")->GetChild("ButtonLink"))->AddOnReleased(caller, function, params);
}
void JYesNoModule::Clear()
{
	JGameModule::Clear();
}
void JYesNoModule::Update()
{
	JGameModule::Update();
}
void JYesNoModule::Activate()
{
	JGameModule::Activate();
}
void JYesNoModule::Deactivate()
{
	JGameModule::Deactivate();
}