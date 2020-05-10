#ifndef JAUDIOMANAGER
#define JAUDIOMANAGER

namespace J
{
	namespace AUDIO
	{
		const static int MAX_CHANNELS = 16;
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

			int  GetFreeAudioChannel();
			void ReleaseAudioChannel(int channel);

			JAudio* const  GetAudio() { return mAudio; }
		private:
			JAudio *			mAudio;
			bool					mAudioChannelsPairs[MAX_CHANNELS];
		};
#define gJAudioManager ::J::AUDIO::JAudioManager::GetSingleton()
	}
}

#endif // !JAUDIOMANAGER
