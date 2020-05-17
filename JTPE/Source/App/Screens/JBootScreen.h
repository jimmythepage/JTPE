#ifndef JBOOTSCREEN
#define JBOOTSCREEN

namespace J
{
	namespace GAME
	{
		class JOkModule;
		class JBootScreen : public ::J::GAME::JGameScreen
		{
		public:
			JBootScreen();
			~JBootScreen();

			virtual void Init();
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();
		protected:
			void GoToMain();
			void OkNetCallback(JGameButton* caller, json params);

			GAME::JGameElement*	mBootModule;
			TWEEN::JFloatTween  mAlphaTween;
			JOkModule*			mOkNetDialog;

			J::NET::JRequest	mTestRequest;
		};
	}
}

#endif