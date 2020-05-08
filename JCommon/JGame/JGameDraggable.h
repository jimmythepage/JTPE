#ifndef JGAMEDRAGGABLE
#define JGAMEDRAGGABLE


namespace J
{
	namespace GAME
	{
		class JGameDraggable : public ::J::GAME::JGameButton
		{
		public:
			JGameDraggable();
			~JGameDraggable();

			virtual void Init(const std::string name, std::string applink, json button);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();
		protected:
			float								mOldXOffset, mOldYOffset;
			float								mLandingX, mLandingY;
			bool								mCanLandFreely;
			std::list<JGameElement*>			mLandingElements;

			virtual void						LongPressTimerCallback();
			float								mLongPressThreshold;
			bool								mForceRelease;
		};
	}
}

#endif