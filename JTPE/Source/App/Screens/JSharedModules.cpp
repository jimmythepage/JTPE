#include "JAppPch.h"
#include "JSharedModules.h"

using namespace J;
using namespace J::APP;


JSharedModules::JSharedModules():MainMenuScreen(NULL)
{

}
JSharedModules::~JSharedModules()
{
}
JSharedModules & JSharedModules::GetSingleton()
{
	static JSharedModules _singleton;
	return _singleton;
}