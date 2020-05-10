#ifndef JAUDIOCLIP
#define JAUDIOCLIP

namespace J
{
	namespace AUDIO
	{
		class JAudioClipImpl;
		class JAudioClip : public ::J::BASE::JBase
		{
		public:
			JAudioClip();
			~JAudioClip();

			virtual void Init(const std::string name,const std::string filepath);
			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual void Play();
			virtual void Pause();
			virtual void Stop();

			virtual void			SetLoop(bool loop);
			virtual bool			GetLoop();
			virtual bool			IsPlaying();

			virtual void			SetVolume(int volume);
			virtual int				GetVolume();
		protected:
			JAudioClipImpl*						mAudioClipImpl;
		};
	}
}

#endif // !JAUDIOCLIP
