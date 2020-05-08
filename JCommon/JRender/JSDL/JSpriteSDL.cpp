#include "JCommonPch.h"
#include "JSpriteSDL.h"



using namespace J;
using namespace J::TASK;
using namespace J::RENDER;

JSpriteSDL::JSpriteSDL():mImage(NULL),mTexture(NULL),mRenderer(NULL)
{
}
JSpriteSDL::~JSpriteSDL()
{
}
void JSpriteSDL::Init(const std::string filepath, const std::string name, JRenderableProperties properties)
{
	Init(filepath, name);
	SetProperties(properties);
	JRenderableProperties clip;
	clip.Size.x = (float)mImage->w;
	clip.Size.y = (float)mImage->h;
	SetSpriteClip(clip);
}	
void JSpriteSDL::Init(const std::string filepath, const std::string name, JRenderableProperties properties, JRenderableProperties clip)
{
	Init(filepath, name);
	SetProperties(properties);
	SetSpriteClip(clip);
}
void JSpriteSDL::Init(const std::string filepath, const std::string name)
{
	Init(name);
	std::string path = gJEngine.GetSettings()->DataFolder;
	path += filepath;
	mImage = gJTextureManagerSDL.GetOrLoadTexture(path);
	mRenderer = static_cast<JRendererSDL*>(gJRenderManager.GetRenderer())->GetRenderer();
	mTexture= SDL_CreateTextureFromSurface(mRenderer, mImage);
}
void JSpriteSDL::Init(const std::string name)
{
	JRenderable::Init(name);
}
void JSpriteSDL::Clear()
{
	JRenderable::Clear();
	if (mTexture)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
	mImage = NULL;
	mRenderer = NULL;
}
void JSpriteSDL::Activate()
{
	JRenderable::Activate();
}
void JSpriteSDL::Update()
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
		SDL_RenderCopyEx(mRenderer, mTexture, &clip, &transform, GetProperties().Rot, &Origin, SDL_FLIP_NONE);
	}
}
void JSpriteSDL::Deactivate()
{
	JRenderable::Deactivate();
}