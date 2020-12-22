#ifndef JENGINE
#define JENGINE

namespace J
{
	namespace ENGINE
	{
		enum EngineOptions
		{
			NONE=0,
			USES_BLOB,
			USES_STEAM
		};
		struct Settings
		{
			unsigned int	ScreenWidth, ScreenHeight;
			unsigned int	LogicalWidth,LogicalHeight;
			float			LogicalRatioX, LogicalRatioY;
			bool			FullScreen;
      bool      Transparent;
      unsigned int R_CutOff, G_CutOff, B_CutOff;
			std::string		DataFolder;
		};
		class JEngine : public ::J::BASE::JBase
		{
		public:
			JEngine();
			~JEngine();

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static JEngine & GetSingleton();

			void Init(const std::string name, const std::string absBasePath, const std::string settingsPath, unsigned int options);
			void Init(const std::string name,const std::string settingsPath, unsigned int options);
			void Clear();
			void Update();
			void Activate();
			void Deactivate();

			void StopEngine();
			bool IsReadyToShut();
			bool IsEngineRunning();

			const Settings* GetSettings() { return &mSettings; }
		private:
			bool mIsEngineRunning;
			Settings mSettings;
		};
		#define gJEngine ::J::ENGINE::JEngine::GetSingleton()
	}
}

#endif // !JENGINE
