#ifndef JINPUTPOINTERWIN
#define JINPUTPOINTERWIN

namespace J
{
	namespace INPUT
	{
		class JInputPointerWin : public ::J::INPUT::JInputPointer
		{
		public:
			JInputPointerWin();
			~JInputPointerWin();

			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();
		private:
#ifdef __SFML__
			sf::RenderWindow* mWindow;
#endif // __SFML__

		};
	}
}

#endif // !JINPUTKEYBOARDWIN
