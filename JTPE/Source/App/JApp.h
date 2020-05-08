#ifndef JAPP
#define JAPP

namespace J
{
	namespace APP
	{
		class JApp : public ::J::BASE::JBase
		{
		public:
			JApp();
			~JApp();

			void Init(const std::string name);
			void Clear();
			void Update();
			void Activate();
			void Deactivate();

			void StopApp();
			bool IsReadyToShut();
		private:
		};
	}
}

#endif // !JENGINE
