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

			virtual void			SetLoop(bool loop) { mLoop = loop; }
			virtual bool			GetLoop() { return mLoop; }
			virtual bool			IsPlaying() { return mIsPlaying; }
		protected:
			::J::BASE::JBase*					mAudioClipImpl;
			std::string								mFilePath;
			bool											mIsPlaying;
			bool											mLoop;
		};
	}
}

#endif // !JAUDIOCLIPIMPL
