#ifndef JGAMELEVEL
#define JGAMELEVEL

namespace J
{
	namespace GAME
	{
		class JGameLevel : public ::J::GAME::JGameScreen
		{
		public:
			JGameLevel();
			~JGameLevel();

			virtual void Update();

		protected:
		};
	}
}

#endif