#ifndef JAUDIOCLIPSDL
#define JAUDIOCLIPSDL

namespace J
{
	namespace AUDIO
	{
		class JAudioClipSDL : public ::J::AUDIO::JAudioClipImpl
		{
		public:
			JAudioClipSDL();
			~JAudioClipSDL();

			virtual void Init(const std::string name, const std::string filepath);
			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual void Play();
			virtual void Pause();
			virtual void Stop();

			void OnCallback(Uint8 *stream, int len);

		protected:
			SDL_AudioDeviceID		mAudioDevice;
			Uint8 *mAudioPos; // global pointer to the audio buffer to be played
			Uint32 mAudioLen; // remaining length of the sample we have to play
		};
	}
}

#endif // !JAUDIOCLIPSDL
