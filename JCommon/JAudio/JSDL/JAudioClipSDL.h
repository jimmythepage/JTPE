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

			virtual void			SetVolume(int volume);
			virtual int				GetVolume();

		protected:
			Mix_Chunk* _clipSample;
		};
	}
}

#endif // !JAUDIOCLIPSDL
