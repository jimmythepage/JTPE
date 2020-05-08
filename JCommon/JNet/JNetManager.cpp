#include "JCommonPch.h"

using namespace J;
using namespace J::BASE;
using namespace J::NET;


JNetManager::JNetManager():mNetProvider(NONE), mNetProviderStarted(false)
{
}
JNetManager::~JNetManager()
{
	
}
JNetManager & JNetManager::GetSingleton()
{
	static JNetManager _singleton;
	return _singleton;
}
void JNetManager::Init(const std::string name, NET_PROVIDER provider)
{
	JBase::Init(name);
	mNetProvider = provider;
}
bool JNetManager::StartNetProvider(std::string& errorMsg)
{
	if (mNetProvider == STEAM)
	{
#ifdef __STEAM__
		if (SteamAPI_RestartAppIfNecessary(k_uAppIdInvalid))
		{
			// if Steam is not running or the game wasn't started through Steam, SteamAPI_RestartAppIfNecessary starts the 
			// local Steam client and also launches this game again.

			// Once you get a public Steam AppID assigned for this game, you need to replace k_uAppIdInvalid with it and
			// removed steam_appid.txt from the game depot.
			return false;
		}
		// Init Steam CEG
		if (!Steamworks_InitCEGLibrary())
		{
			errorMsg = gJTextDB.GetTextEntry("STEAM_MUST_RUN_ID");
			return false;
		}
		// Initialize SteamAPI, if this fails we bail out since we depend on Steam for lots of stuff.
		// You don't necessarily have to though if you write your code to check whether all the Steam
		// interfaces are NULL before using them and provide alternate paths when they are unavailable.
		//
		// This will also load the in-game steam overlay dll into your process.  That dll is normally
		// injected by steam when it launches games, but by calling this you cause it to always load,
		// even when not launched via steam.
		if (!SteamAPI_Init())
		{
			errorMsg = gJTextDB.GetTextEntry("STEAM_MUST_RUN_ID");
			return false;
		}
		// Ensure that the user has logged into Steam. This will always return true if the game is launched
		// from Steam, but if Steam is at the login prompt when you run your game from the debugger, it
		// will return false.
		if (!SteamUser()->BLoggedOn())
		{
			errorMsg = gJTextDB.GetTextEntry("STEAM_USER_MUST_LOG_ID");
			return false;
		}
		// do a DRM self check
		Steamworks_SelfCheck();
#endif
	}
	mNetProviderStarted = true;
	return true;
}
void JNetManager::StopNetProvider()
{
	if (mNetProvider == STEAM)
	{
#ifdef __STEAM__
		// Shutdown the SteamAPI
		SteamAPI_Shutdown();
		// Shutdown Steam CEG
		Steamworks_TermCEGLibrary();
#endif
	}
	mNetProviderStarted = false;
}
void JNetManager::Clear()
{
	JBase::Clear();
}
void JNetManager::Update()
{
#ifdef __STEAM__
	if (mNetProvider == STEAM)
	{
		// test a user specific secret before entering main loop
		Steamworks_TestSecret();
	}
#endif
}
void JNetManager::Activate()
{
	JBase::Activate();
	LOG_INFO(0, "%s is Activated\n", mName.c_str());
}
void JNetManager::Deactivate()
{
	JBase::Deactivate();
	StopNetProvider();
	LOG_INFO(0, "%s is Deactivated\n", mName.c_str());
}