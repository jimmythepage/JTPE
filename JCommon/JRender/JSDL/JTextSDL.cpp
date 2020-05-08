#include "JCommonPch.h"
#include "JTextSDL.h"


#include <JRender/JSDL/SDL_FontCache.h>


using namespace J;
using namespace J::TASK;
using namespace J::RENDER;

JTextSDL::JTextSDL() :mFont(NULL),mRenderer(NULL)
{
}
JTextSDL::~JTextSDL()
{
}
void JTextSDL::Init(const std::string fontpath, const std::string name, JRenderableProperties properties)
{
	Init(name);
	SetProperties(properties);
	std::string path = gJEngine.GetSettings()->DataFolder;
	path += fontpath;
	mRenderer = static_cast<JRendererSDL*>(gJRenderManager.GetRenderer())->GetRenderer();
	mFont = FC_CreateFont();
	SDL_Color color = FC_MakeColor(
		(Uint8)(255 * GetProperties().R),
		(Uint8)(255 * GetProperties().G),
		(Uint8)(255 * GetProperties().B),
		(Uint8)(255 * GetProperties().A));
	if (mProperties.FontStyle == STYLE_NORMAL)
	{
		FC_LoadFont(mFont, mRenderer, path.c_str(), properties.FontSize,
			color, TTF_STYLE_NORMAL);
	}
	else if (mProperties.FontStyle == STYLE_BOLD)
	{
		FC_LoadFont(mFont, mRenderer, path.c_str(), properties.FontSize,
			color, TTF_STYLE_BOLD);
	}
	else if (mProperties.FontStyle == STYLE_ITALIC)
	{
		FC_LoadFont(mFont, mRenderer, path.c_str(), properties.FontSize,
			color, TTF_STYLE_ITALIC);
	}
	else if (mProperties.FontStyle == STYLE_UNDERLINE)
	{
		FC_LoadFont(mFont, mRenderer, path.c_str(), properties.FontSize,
			color, TTF_STYLE_UNDERLINE);
	}
	else if (mProperties.FontStyle == STYLE_STRIKETHROUGH)
	{
		FC_LoadFont(mFont, mRenderer, path.c_str(), properties.FontSize,
			color, TTF_STYLE_STRIKETHROUGH);
	}
}
void JTextSDL::Init(const std::string name)
{
	JRenderable::Init(name);
}
void JTextSDL::SetText(std::string text)
{
	mText = text;
}
void JTextSDL::Clear()
{
	JRenderable::Clear();
	FC_FreeFont(mFont);
	mRenderer = NULL;
}
void JTextSDL::Activate()
{
	JRenderable::Activate();
}
void JTextSDL::Update()
{
	JRenderable::Update();
	int logicalX = (int)(GetProperties().Position.x);
	int logicalY = (int)(GetProperties().Position.y) - (int)((float)GetProperties().FontSize*GetProperties().Origin.y);
	SDL_Color color;
	color.r= (Uint8)(255 * GetProperties().R);
	color.g= (Uint8)(255 * GetProperties().G);
	color.b= (Uint8)(255 * GetProperties().B);
	color.a= (Uint8)(255 * GetProperties().A);
	FC_Scale scale;
	scale.x = GetProperties().Scale.x;
	scale.y = GetProperties().Scale.y;
	FC_AlignEnum align = FC_AlignEnum::FC_ALIGN_CENTER;
	if (mProperties.TextAlign == ALIGN_RIGHT)
	{
		align = FC_AlignEnum::FC_ALIGN_RIGHT;
	}
	else if (mProperties.TextAlign == ALIGN_LEFT)
	{
		align = FC_AlignEnum::FC_ALIGN_LEFT;
	}
	FC_Effect effect{ align,scale,color };
	if (GetProperties().Visible)
	{
		FC_DrawEffect(mFont,mRenderer, (gJEngine.GetSettings()->LogicalWidth / 2.f + logicalX),
			(gJEngine.GetSettings()->LogicalHeight / 2.f + logicalY), effect, mText.c_str());
	}
}
void JTextSDL::Deactivate()
{
	JRenderable::Deactivate();
}