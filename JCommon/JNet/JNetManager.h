#ifndef JNETMANAGER
#define JNETMANAGER

namespace J
{
	namespace NET
	{
		enum NET_PROVIDER
		{
			NONE,
			STEAM,
			EPIC,
			DISCORD
		};
		class JNetManager : public ::J::BASE::JBase
		{
		public:
			JNetManager();
			~JNetManager();

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static JNetManager & GetSingleton();

			void Init(const std::string name, NET_PROVIDER provider);
			void Clear();
			void Update();
			void Activate();
			void Deactivate();

			bool StartNetProvider(std::string& errorMsg);
			void StopNetProvider();

		private: 
			NET_PROVIDER mNetProvider;
			bool		 mNetProviderStarted;
		};
#define gJNetManager ::J::NET::JNetManager::GetSingleton()
	}
}

#endif
