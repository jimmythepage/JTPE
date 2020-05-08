#ifndef JGAMECAMERA
#define JGAMECAMERA


namespace J
{
	namespace GAME
	{
		class JGameCamera : public ::J::GAME::JGameElement
		{
		public:
			JGameCamera();
			~JGameCamera();

			virtual void Init(const std::string name, std::string filepath);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual void			SetToFollow(JGameElement* element) { mToFollow = element; }
			virtual JGameElement*	GetToFollow() { return mToFollow; }
		protected:
			JGameElement*	mToFollow;
			float			mFollowSpeedX, mFollowSpeedY;
		};
	}
}

#endif