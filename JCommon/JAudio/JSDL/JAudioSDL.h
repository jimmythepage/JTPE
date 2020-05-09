#ifndef JAUDIOSDL
#define JAUDIOSDL

namespace J
{
	namespace AUDIO
	{
		class JAudioSDL : public ::J::AUDIO::JAudio
		{
		public:
			JAudioSDL();
			~JAudioSDL();

			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

		protected:
		};
	}
}

#endif // !JAUDIOSDL
