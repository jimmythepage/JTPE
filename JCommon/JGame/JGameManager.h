#ifndef JGAMEMANAGER
#define JGAMEMANAGER

/*JGAMEMANAGER gestisce le Screens attuali e ne chiama i metodi.
Si tiene inoltre le Screens precedenti per funzioni di back.
Varie ed eventuali*/
namespace J
{
	namespace GAME
	{
		enum DebugLogger_State
		{
			None = 0,
			FPS
		};

		class JGameManager : public ::J::BASE::JBase
		{
		public:
			JGameManager();
			~JGameManager();

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static JGameManager & GetSingleton();

			void Init(const std::string name);
			void Clear();
			void Update();
			void Activate();
			void Deactivate();


			void			LoadGameModule(JGameModule* module, json gameModule);

			void			SetCurrentScreen	(JGameScreen* screen,bool cleanPrevious=false);
			JGameScreen*	GetCurrentScreen	() { return mCurrentScreen; }
			JGameScreen*	GetPrevScreen		() { return mPrevScreen; }

			void			SetCurrentLevel(JGameLevel* level);
			JGameLevel*		GetCurrentLevel() { return mCurrentLevel; }
			JGameLevel*		GetPrevLevel() { return mPrevLevel; }

			void			SetCurrentCamera(JGameCamera* camera);
			JGameCamera*	GetCurrentCamera() { return mCurrentCamera; }

			void				SetCurrentExploredButton(JGameButton* button) { mCurrentExploredButton = button; }
			JGameButton*		GetCurrentExploredButton() { return mCurrentExploredButton; }

			json		GetJsonModule		(std::string filepath);
			json		GetJsonScreen		(std::string filepath);

			void		SetCachedMode(bool cached) { mLoadCached = cached; }

		protected:
			void		ClearUnusedElements();

			JGameScreen*			mCurrentScreen;
			JGameScreen*			mPrevScreen;

			JGameLevel*				mCurrentLevel;
			JGameLevel*				mPrevLevel;

			JGameCamera*			mCurrentCamera;

			std::vector<JBase*>		mToDelete;
			bool					mNeedCleaning;

			JGameButton*			mCurrentExploredButton;

			json		LoadJson			(std::string filepath);

			std::map<std::string, json> mJsonScreens;
			std::map<std::string, json> mJsonModules;
			bool						mLoadCached;

			//DEBUG LOGGER STUFF
			J::RENDER::JText*			mDebugLogger;
			DebugLogger_State			mDebugLoggerState;
			clock_t						mLastTime;
		};
#define gJGameManager ::J::GAME::JGameManager::GetSingleton()
	}
}

#endif // !JGUIMANAGER
