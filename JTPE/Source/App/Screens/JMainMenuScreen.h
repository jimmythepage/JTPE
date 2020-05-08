#ifndef JMAINMENUSCREEN
#define JMAINMENUSCREEN

namespace J
{
	namespace GAME
	{
		class JYesNoModule;
		class JMainMenuScreen : public ::J::GAME::JGameScreen
		{
		public:
			JMainMenuScreen();
			~JMainMenuScreen();

			void Init();
			void Clear();
			void Update();
			void Activate();
			void Deactivate();
		protected:
			void GoToMainGameScreen();
			void NewGameCallback(JGameButton* caller, json params);
			void ConfirmNewGameCallback(JGameButton* caller, json params);
			void CancelNewGameCallback(JGameButton* caller, json params);
			void ContinueCallback(JGameButton* caller, json params);

		private:
			JYesNoModule* mYesNoNewGameDialog;
		};
	}
}

#endif