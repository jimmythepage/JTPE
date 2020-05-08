#include "JCommonPch.h"
#include "JTextureManagerSDL.h"

using namespace J;
using namespace J::BASE;
using namespace J::RENDER;

JTextureManagerSDL::JTextureManagerSDL()
{
}
JTextureManagerSDL::~JTextureManagerSDL()
{
}
JTextureManagerSDL & JTextureManagerSDL::GetSingleton()
{
	static JTextureManagerSDL _singleton;
	return _singleton;
}
void JTextureManagerSDL::Init(std::string name)
{
	JBase::Init(name);
}
void JTextureManagerSDL::Clear()
{
	JBase::Clear();
	for (std::map<std::string, SDL_Surface *>::iterator it = mTextures.begin(); it != mTextures.end(); it++)
	{
		SDL_Surface * texture = (*it).second;
		SDL_FreeSurface(texture);
		texture = NULL;
	}
	mTextures.clear();
}
SDL_Surface * JTextureManagerSDL::GetOrLoadTexture(std::string path)
{
	SDL_Surface * texture = NULL;
	if (mTextures.count(path) == 1)
	{
		texture = mTextures[path];
	}
	else
	{
		J::BASE::JFile file;
		file.Load(path, false, true);
		SDL_RWops *rw = SDL_RWFromConstMem(file.GetBinData(), (int)file.GetBinSize());
		texture = IMG_Load_RW(rw, 1);
		ASSERT(texture);
		file.Unload();
		std::pair<std::string, SDL_Surface* > pair(path, texture);
		mTextures.insert(pair);
	}
	return texture;
}