#ifndef JVIDEOSPRITE
#define JVIDEOSPRITE

namespace J
{
	namespace RENDER
	{
		class JVideoSprite : public ::J::BASE::JBase
		{
		public:
			JVideoSprite();
			~JVideoSprite();

			virtual void Init(const std::string filepath, const std::string name, JRenderableProperties properties);
			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual JRenderableProperties	GetProperties()				{ return mRenderable->GetProperties(); }
			virtual void	SetProperties(JRenderableProperties properties)	{ mRenderable->SetProperties(properties); }

			virtual void			PlayVideo();
			virtual void			PauseVideo();
			virtual void			StopVideo();
			virtual void			SetLoop(bool loop);
			virtual void			SetFPS(unsigned int fps) { mFPS = fps; }

			virtual bool			GetLoop() { return mLoop; }
			virtual unsigned int GetFPS() { return mFPS; }
		protected:
			JRenderable*					mRenderable;
		private:
			//ANIMATED SPRITE STUFF
			bool											mIsPlaying;
			unsigned int							mFPS;
			bool											mLoop;
			void											FrameTimerCallback();
			J::BASE::JTimer						mFrameTimer;
		};
	}
}

#endif // !JVIDEOSPRITE
