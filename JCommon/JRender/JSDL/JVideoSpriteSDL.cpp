#include "JCommonPch.h"
#include "JVideoSpriteSDL.h"

using namespace J;
using namespace J::TASK;
using namespace J::RENDER;

JVideoSpriteSDL::JVideoSpriteSDL():mTexture(NULL),mRenderer(NULL), 
	mFormatCtx(NULL), mCodecParameters(NULL), mCodecAudioParameters(NULL), 
	mCodec(NULL),mAudioCodec(NULL),mFrame(NULL),mFrameRGB(NULL),
	mCodecCtx(NULL),mCodecAudioCtx(NULL),
	mVideoStream(0), mAudioStream(0),
	mBuffer(NULL), mUpdateVideoFrame(false)
{
}
JVideoSpriteSDL::~JVideoSpriteSDL()
{
}
void JVideoSpriteSDL::DisplayException(const char * message)
{
	Player::get_instance()->clear();
	throw std::runtime_error(message);
}
void JVideoSpriteSDL::Display_ffmpeg_exception(int error_code)
{
	char error_buf[ERROR_SIZE];
	av_strerror(error_code, error_buf, ERROR_SIZE);
	DisplayException(error_buf);
}
void JVideoSpriteSDL::Init(const std::string filepath, const std::string name, JRenderableProperties properties)
{
	Init(filepath, name);
	SetProperties(properties);
}	
void JVideoSpriteSDL::Init(const std::string filepath, const std::string name)
{
	Init(name);
	std::string path = gJEngine.GetSettings()->DataFolder;
	path += filepath;

	// open video
	int res = avformat_open_input(&mFormatCtx, path.c_str(), NULL, NULL);
	// check video
	if (res != 0)
	{
		Display_ffmpeg_exception(res);
	}

	// get video info
	res = avformat_find_stream_info(mFormatCtx, NULL);
	if (res < 0)
	{
		Display_ffmpeg_exception(res);
	}

	// get video stream
	mVideoStream = GetVideoStream();
	if (mVideoStream == -1)
	{
		DisplayException("Error opening your video using AVCodecParameters, probably doesnt have codecpar_type type AVMEDIA_TYPE_VIDEO");
	}

	// open
	ReadAudioVideoCodec();

	Audio::get_instance()->malloc(mCodecAudioCtx);

	//Audio::get_instance()->open();

	mFrame = av_frame_alloc();
	if (mFrame == NULL)
		DisplayException("Couldnt allocate frame memory");

	mFrameRGB = av_frame_alloc();
	if (mFrameRGB == NULL)
		DisplayException("Couldnt allocate rgb frame memory");

	int numBytes = av_image_get_buffer_size(VIDEO_FORMAT, mCodecCtx->width, mCodecCtx->height, 1);

	mBuffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

	int res_avImage = av_image_fill_arrays(mFrameRGB->data, mFrameRGB->linesize, mBuffer, VIDEO_FORMAT, mCodecCtx->width, mCodecCtx->height, 1);
	if (res_avImage < 0)
		Display_ffmpeg_exception(res_avImage);

	mRenderer = static_cast<JRendererSDL*>(gJRenderManager.GetRenderer())->GetRenderer();
	mTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STATIC, mCodecCtx->width, mCodecCtx->height);
}
int JVideoSpriteSDL::ReadAudioVideoCodec()
{
	mCodec = avcodec_find_decoder(mCodecParameters->codec_id);
	mAudioCodec = avcodec_find_decoder(mCodecAudioParameters->codec_id);

	if (mCodec == NULL)
	{
		DisplayException("Video decoder not found");
	}

	if (mAudioCodec == NULL)
	{
		DisplayException("Audio decoder not found");
	}

	mCodecCtx = avcodec_alloc_context3(mCodec);

	if (mCodecCtx == NULL)
	{
		DisplayException("Failed to allocate video context decoder");
	}

	mCodecAudioCtx = avcodec_alloc_context3(mAudioCodec);

	if (mCodecAudioCtx == NULL)
	{
		DisplayException("Failed to allocate audio context decoder");
	}

	int res = avcodec_parameters_to_context(mCodecCtx, mCodecParameters);

	if (res < 0)
	{
		DisplayException("Failed to transfer video parameters to context");
	}

	res = avcodec_parameters_to_context(mCodecAudioCtx, mCodecAudioParameters);

	if (res < 0)
	{
		DisplayException("Failed to transfer audio parameters to context");
	}

	res = avcodec_open2(mCodecCtx, mCodec, NULL);

	if (res < 0)
	{
		DisplayException("Failed to open video codec");
	}

	res = avcodec_open2(mCodecAudioCtx, mAudioCodec, NULL);

	if (res < 0)
	{
		DisplayException("Failed to open auvio codec");
	}

	return 1;
}
int JVideoSpriteSDL::GetVideoStream()
{
	int videoStream = -1;

	for (unsigned int i = 0; i < mFormatCtx->nb_streams; i++) 
	{
		if (mFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) videoStream = i;
		if (mFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) mAudioStream = i;
	}

	if (videoStream == -1)
	{
		DisplayException("Couldnt find stream");
	}

	mCodecParameters = mFormatCtx->streams[videoStream]->codecpar;
	if (mAudioStream != -1)
	{
		mCodecAudioParameters = mFormatCtx->streams[mAudioStream]->codecpar;
	}

	return videoStream;
}
void JVideoSpriteSDL::Init(const std::string name)
{
	JRenderable::Init(name);
}
void JVideoSpriteSDL::Clear()
{
	JRenderable::Clear();
	// close context info
	avformat_close_input(&mFormatCtx);
	avcodec_free_context(&mCodecCtx);

	// free buffers
	av_free(mBuffer);
	av_free(mFrameRGB);

	// Free the YUV frame
	av_free(mFrame);

	// Close the codecs
	avcodec_close(mCodecCtx);

	// Close the video file
	avformat_close_input(&mFormatCtx);

	if (mTexture)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
	mRenderer = NULL;
}
void JVideoSpriteSDL::Activate()
{
	JRenderable::Activate();
}
void JVideoSpriteSDL::UpdateVideoFrame()
{
	mUpdateVideoFrame = true;
}
void JVideoSpriteSDL::Update()
{
	JRenderable::Update();
	float width = (float)GetProperties().Size.x*GetProperties().Scale.x;
	float height = (float)GetProperties().Size.y*GetProperties().Scale.y;
	int logicalX = (int)(GetProperties().Position.x) - (int)(width*GetProperties().Origin.x);
	int logicalY = (int)(GetProperties().Position.y) - (int)(height*GetProperties().Origin.y);
	SDL_Rect transform =
	{
		(int)(gJEngine.GetSettings()->LogicalWidth / 2.f + logicalX),
		(int)(gJEngine.GetSettings()->LogicalHeight / 2.f + logicalY),
		(int)width, (int)height
	};

	SDL_Rect clip = { (int)GetSpriteClip().Position.x, (int)GetSpriteClip().Position.y, (int)GetSpriteClip().Size.x, (int)GetSpriteClip().Size.y };

	SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(mTexture, (Uint8)(255 * GetProperties().A));
	SDL_SetTextureColorMod(mTexture, (Uint8)(255 * GetProperties().R),
		(Uint8)(255 * GetProperties().G),
		(Uint8)(255 * GetProperties().B));

	SDL_Point Origin = { (int)(width*GetProperties().Origin.x),
		(int)(height*GetProperties().Origin.y), };
	if (GetProperties().Visible)
	{
		if (mUpdateVideoFrame)
		{
			mUpdateVideoFrame = false;
			AVPacket packet;

			if (av_read_frame(mFormatCtx, &packet) >= 0)
			{
				/*if (packet.stream_index == mAudioStream)
				{
					Audio::get_instance()->put_audio_packet(&packet);
				}*/
				if (packet.stream_index == mVideoStream)
				{
					int res = avcodec_send_packet(mCodecCtx, &packet);
					if (res < 0)
					{
						Display_ffmpeg_exception(res);
					}

					res = avcodec_receive_frame(mCodecCtx, mFrame);

					SDL_UpdateYUVTexture(mTexture, NULL, mFrame->data[0], mFrame->linesize[0],
						mFrame->data[1], mFrame->linesize[1],
						mFrame->data[2], mFrame->linesize[2]);
				}
			}
			av_packet_unref(&packet);
		}
		//SDL_RenderCopy(mRenderer, mTexture, NULL, NULL);
		SDL_RenderCopyEx(mRenderer, mTexture, &clip, &transform, GetProperties().Rot, &Origin, SDL_FLIP_NONE);
		//TODO
		//- Clipping into texture
		//- Timing (timers seems wrong)
		//- Audio not loading
		//- Audio not cleaning
		//- Import parameter from JSON (fps, loop)
		//- Setup controls (PlayVideo, ResumeVideo, StopVideo)
		//
	}
}
void JVideoSpriteSDL::Deactivate()
{
	JRenderable::Deactivate();
}