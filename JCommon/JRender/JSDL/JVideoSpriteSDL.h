#ifndef JVIDEOSPRITESDL
#define JVIDEOSPRITESDL

namespace J
{
	namespace RENDER
	{
		class JVideoSpriteSDL : public ::J::RENDER::JRenderable
		{
		public:
			JVideoSpriteSDL();
			~JVideoSpriteSDL();

			virtual void Init(const std::string filepath,const std::string name);
			virtual void Init(const std::string filepath, const std::string name, JRenderableProperties properties);
			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual void				UpdateVideoFrame();
			virtual void				RestartVideo();
			virtual void				SetLoop(bool loop) { mLoop = loop; }
		protected:
			SDL_Texture *				mTexture;
			SDL_Renderer*				mRenderer;

			AVFormatContext*		mFormatCtx;
			AVCodecParameters*	mCodecParameters;
			AVCodecParameters*	mCodecAudioParameters;
			AVCodec*						mCodec;
			AVCodec*						mAudioCodec;
			AVFrame*						mFrame;
			AVFrame*						mFrameRGB;
			AVCodecContext*			mCodecCtx;
			AVCodecContext*			mCodecAudioCtx;
			int									mVideoStream ;
			int									mAudioStream;
			uint8_t*						mBuffer;
			int									mPreviousFrameNumber;

			bool								mUpdateVideoFrame;
			bool								mLoop;

		private:
			int		GetVideoStream();
			int		ReadAudioVideoCodec();
			void	DisplayException(const char * message);
			void	Display_ffmpeg_exception(int error_code);
		};
	}
}

#endif // !JSPRITESDL
