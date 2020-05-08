#ifndef JYESNOMODULE
#define JYESNOMODULE

namespace J
{
	namespace GAME
	{
		class JYesNoModule : public ::J::GAME::JGameModule
		{
		public:
			JYesNoModule();
			~JYesNoModule();

			virtual void Init(const std::string modulePath, std::string yesTextID, const std::string noTextID, const std::string descriptionTextID);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			void OnYesReleased(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params);
			void OnNoReleased(J::BASE::JBase* caller, std::function<void(JGameButton*, json)> function, json params);
		protected:
		};
	}
}

#endif