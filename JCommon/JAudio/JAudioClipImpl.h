#ifndef JAUDIOCLIPIMPL
#define JAUDIOCLIPIMPL

namespace J
{
	namespace AUDIO
	{
		class JAudioClipImpl : public ::J::BASE::JBase
		{
		public:
			JAudioClipImpl();
			~JAudioClipImpl();

			virtual void Init(const std::string name,const std::string filepath);
			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual void Play();
			virtual void Pause();
			virtual void Stop();

			virtual void			SetIsPlaying(bool isPlaying) { mIsPlaying = isPlaying; }
			virtual bool			IsPlaying() { return mIsPlaying; }

			virtual void			SetLoop(bool loop) { mLoop = loop; }
			virtual bool			GetLoop() { return mLoop; }

			virtual void			SetVolume(int volume);
			virtual int				GetVolume();

			virtual void			SetAudioChannel(int channel) { mChannel = channel; }
			virtual bool			GetAudioChannel() { return mChannel; }
		protected:
			::J::BASE::JBase*					mAudioClipImpl;
			std::string								mFilePath;
			bool											mIsPlaying;
			bool											mLoop;
			int												mChannel;
			int												mVolume;
		};
	}
}

#endif // !JAUDIOCLIPIMPL
