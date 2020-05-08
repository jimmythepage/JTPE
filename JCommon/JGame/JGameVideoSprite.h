#ifndef JGAMEVIDEOSPRITE
#define JGAMEVIDEOSPRITE


namespace J
{
	namespace GAME
	{
		class JGameVideoSprite : public ::J::GAME::JGameElement
		{
		public:
			JGameVideoSprite();
			~JGameVideoSprite();

			virtual void Init(const std::string name, std::string applink,json sprite);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();
		protected:
			J::RENDER::JVideoSprite* mSprite;
		};
	}
}

#endif