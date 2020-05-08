#ifndef JOKMODULE
#define JOKMODULE

namespace J
{
	namespace GAME
	{
		class JOkModule : public ::J::GAME::JGameModule
		{
		public:
			JOkModule();
			~JOkModule();

			virtual void Init(const std::string modulePath, std::string okTextID,const std::string descriptionTextID);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			void OnOkReleased(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params);
		protected:
		};
	}
}

#endif