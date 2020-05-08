#include "JAppPch.h"
#include "JOkModule.h"

using namespace J;
using namespace J::GAME;


JOkModule::JOkModule()
{

}
JOkModule::~JOkModule()
{
}
void JOkModule::Init(const std::string modulePath, const std::string okTextID, const std::string descriptionTextID)
{
	JGameModule::Init(modulePath);
	JGameText* okText = static_cast<JGameText*>(
		GetElement("Ok_ButtonLink")->GetChild("ButtonLink")->GetChild("ButtonText"));
	okText->SetText(gJTextDB.GetTextEntry(okTextID));
	JGameText* descText = static_cast<JGameText*>(GetElement("OkModuleTextLink"));
	descText->SetText(gJTextDB.GetTextEntry(descriptionTextID));
}
void  JOkModule::OnOkReleased(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params)
{
	static_cast<JGameButton*>(GetElement("Ok_ButtonLink")->GetChild("ButtonLink"))->AddOnReleased(caller, function, params);
}
void JOkModule::Clear()
{
	JGameModule::Clear();
}
void JOkModule::Update()
{
	JGameModule::Update();
}
void JOkModule::Activate()
{
	JGameModule::Activate();
}
void JOkModule::Deactivate()
{
	JGameModule::Deactivate();
}