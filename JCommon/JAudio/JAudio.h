#ifndef JAUDIO
#define JAUDIO

namespace J
{
	namespace AUDIO
	{
		class JAudio : public ::J::BASE::JBase
		{
		public:
			JAudio();
			~JAudio();

			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

		protected:
		};
	}
}

#endif // !JAUDIO
