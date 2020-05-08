#ifndef JSPRITE
#define JSPRITE

namespace J
{
	namespace RENDER
	{
		class JSprite : public ::J::BASE::JBase
		{
		public:
			JSprite();
			~JSprite();

			virtual void Init(const std::string filepath, const std::string spritesheet,const std::string name, JRenderableProperties properties);
			virtual void Init(const std::string filepath, const std::string name, JRenderableProperties properties);
			virtual void Init(const std::string filepath, const std::string name,JRenderableProperties properties, JRenderableProperties clip);
			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual JRenderableProperties	GetProperties()				{ return mRenderable->GetProperties(); }
			virtual void	SetProperties(JRenderableProperties properties)	{ mRenderable->SetProperties(properties); }
			virtual void	SetSpriteClip(std::string sprite);

			virtual void			SetAnim(std::string anim) { mCurrentAnim = anim; }
			virtual void			PlayAnim();
			virtual void			StopAnim();
			virtual void			SetLoop(bool loop) { mLoop = loop; }
			virtual void			SetPlayStyle(PlayStyle style);
			virtual void			SetPlayStyle(std::string playstyle);
			virtual void			SetCurrentFrame(unsigned int frame) { mCurrentFrame = frame; }

			virtual std::string		GetCurrentAnim() { return mCurrentAnim; }
			virtual bool			GetLoop() { return mLoop; }
			virtual PlayStyle		GetPlayStyle() { return mPlayStyle; }
			virtual unsigned int	GetCurrentFrame() { return mCurrentFrame; }
			virtual std::string		GetCurrentString() { return mCurrentAnim; }
		protected:
			JRenderable*					mRenderable;
			std::map<std::string, JRenderableProperties>	mSpriteSheet;
		private:
			//ANIMATED SPRITE STUFF
			PlayStyle										mPlayStyle;
			bool											mIsPlaying;
			bool											mForward;
			bool											mLoop;
			unsigned int									mFPS;
			int												mCurrentFrame;
			std::string										mCurrentAnim;
			std::map<std::string, std::vector<std::string>> mAnims;
			void											FrameTimerCallback();
			bool											mAnimated;
			J::BASE::JTimer									mFrameTimer;
		};
	}
}

#endif // !JSPRITE
