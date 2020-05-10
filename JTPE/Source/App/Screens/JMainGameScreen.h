#ifndef JMAINGAMESCREEN
#define JMAINGAMESCREEN

namespace J
{
	namespace GAME
	{
		class JYesNoModule;
		class JMainGameScreen : public ::J::GAME::JGameScreen
		{
		public:
			JMainGameScreen();
			~JMainGameScreen();

			void Init();
			void Clear();
			void Update();
			void Activate();
			void Deactivate();
		protected:
			void GoBackToMainMenu();
			void BackToMainCallback(JGameButton* caller, json params);
			void PlayResumeAudioClip(JGameButton* caller, json params);
			void StopAudioClip(JGameButton* caller, json params);

			::J::AUDIO::JAudioClip mBGMusic;
		private:
			TWEEN::JFloatTween  mVolumeFadeIn;
		};
	}
}

#endif