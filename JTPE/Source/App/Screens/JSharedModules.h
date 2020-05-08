#ifndef JSHAREDMODULES
#define JSHAREDMODULES

namespace J
{
	namespace APP
	{
		class JSharedModules : public ::J::BASE::JBase
		{
		public:
			JSharedModules();
			~JSharedModules();

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static JSharedModules & GetSingleton();

			GAME::JGameScreen* MainMenuScreen;
			GAME::JGameScreen* MainGameScreen;
		};
#define gJSharedModules ::J::APP::JSharedModules::GetSingleton()
	}
}

#endif // !JENGINE
