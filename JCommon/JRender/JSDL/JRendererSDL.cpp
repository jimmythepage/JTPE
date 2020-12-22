#include "JCommonPch.h"
#include "JRendererSDL.h"


using namespace J;
using namespace J::TASK;
using namespace J::RENDER;

JRendererSDL::JRendererSDL() :mWindow(NULL), mRenderer(NULL)
{
}
JRendererSDL::~JRendererSDL()
{
}
bool JRendererSDL::MakeWindowTransparent(SDL_Window* window, COLORREF colorKey)
{
  SDL_SysWMinfo wmInfo;
  SDL_VERSION(&wmInfo.version);  // Initialize wmInfo
  SDL_GetWindowWMInfo(window, &wmInfo);
  HWND hWnd = wmInfo.info.win.window;
  SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
  // Set transparency color
  return SetLayeredWindowAttributes(hWnd, colorKey, 0, LWA_COLORKEY);
}
void JRendererSDL::Init(const std::string name, const std::string appName)
{
	JRenderer::Init(name,appName);
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	unsigned int style = 0;
	if (mFullScreen)
	{
		style = style | SDL_WINDOW_FULLSCREEN;
	}
	style = style | SDL_WINDOW_OPENGL;
  if (mIsTransparent)
  {
    style = style | SDL_WINDOW_BORDERLESS;
  }
	if (!mWindow)
	{
		mWindow = SDL_CreateWindow(appName.c_str(),
			100, 100, mScreenWidth, mScreenHeight, style);
    if (mIsTransparent)
    {
      MakeWindowTransparent(mWindow, RGB(mRCutoff, mGCutoff, mBCutoff));
    }
		mRenderer= SDL_CreateRenderer(mWindow, -1, 0);
	}
	SDL_RenderSetLogicalSize(mRenderer, mLogicalWidth, mLogicalHeight);
	gJTextureManagerSDL.Init("Texture Manager SFML");
	/*gJFontManagerSFML.Init("Font Manager SFML");*/
}
void JRendererSDL::Clear()
{
	JRenderer::Clear();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	IMG_Quit();
	SDL_Quit();

	//gJFontManagerSDL.Clear();
	gJTextureManagerSDL.Clear();
	
	mRenderer = NULL;
	mWindow = NULL;
}
void JRendererSDL::Activate()
{
}
void JRendererSDL::Deactivate()
{
}
void JRendererSDL::PreFrame()
{
	SDL_RenderClear(mRenderer);
	SDL_PollEvent(&mEvent);
}
void JRendererSDL::Update()
{
	switch (mEvent.type)
	{
	case SDL_QUIT:
		gJEngine.StopEngine();
		break;
	default:
		break;
	}
	SortRenderables();
	for (JRenderable* renderable : mRenderableToRender)
	{
		renderable->Update();
	}
}
void JRendererSDL::PostFrame()
{
	SDL_RenderPresent(mRenderer);
}
