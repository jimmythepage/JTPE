#ifndef JGAMESPRITE
#define JGAMESPRITE


namespace J
{
	namespace GAME
	{
		class JGameSprite : public ::J::GAME::JGameElement
		{
		public:
			JGameSprite();
			~JGameSprite();

			virtual void Init(const std::string name, std::string applink,json sprite);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();
		protected:
			J::RENDER::JSprite* mSprite;
		};
	}
}

#endif