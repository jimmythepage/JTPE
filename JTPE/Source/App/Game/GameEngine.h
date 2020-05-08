#ifndef GAMEENGINE
#define GAMEENGINE

namespace J
{
	namespace APP
	{
		class GameEngine : public ::J::BASE::JBase
		{
		public:
			GameEngine();
			~GameEngine();

			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			//GENERAL GAME METHODS
			void		 NewGame();
			void		 ContinueGame();
			void		 GameOver();

			//SAVING METHODS
			void		 LoadSaveData();
			void		 Save();
			void		 ClearSaveData();

			//GAME DATA METHODS
			void		 LoadGameData();

			//SAVE GETTERS
			const GameSaving&		GetGameSaving() { return mGameSaving; }
			//GAME GETTERS

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static GameEngine & GetSingleton();
		protected:
			GameSaving		mGameSaving;
		};
#define gGameEngine ::J::APP::GameEngine::GetSingleton()
	}
}

#endif // !GAMEENGINE
