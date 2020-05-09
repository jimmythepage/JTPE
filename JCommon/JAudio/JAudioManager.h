#ifndef JAUDIOMANAGER
#define JAUDIOMANAGER

namespace J
{
	namespace AUDIO
	{
		class JAudioManager : public ::J::BASE::JBase
		{
		public:
			JAudioManager();
			~JAudioManager();

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static JAudioManager & GetSingleton();

			void Init(const std::string name);
			void Clear();
			void Update();
			void Activate();
			void Deactivate();

			JAudio* const  GetAudio() { return mAudio; }
		private:
			JAudio *			mAudio;
		};
#define gJAudioManager ::J::AUDIO::JAudioManager::GetSingleton()
	}
}

#endif // !JAUDIOMANAGER
