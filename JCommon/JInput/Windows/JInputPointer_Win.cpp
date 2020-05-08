#include "JCommonPch.h"
#include "JInput/Windows/JInputPointer_Win.h"

using namespace J;
using namespace J::INPUT;

JInputPointerWin::JInputPointerWin()
{

}
JInputPointerWin::~JInputPointerWin()
{

}
void JInputPointerWin::Init(const std::string name)
{
	JBase::Init(name);
#ifdef  __SFML__
	mWindow= static_cast<J::RENDER::JRendererSFML*>(gJRenderManager.GetRenderer())->Window();
#elif defined(__SDL__)
	SDL_PumpEvents();
#endif

}
void JInputPointerWin::Clear()
{
#ifdef  __SFML__
	mWindow = NULL;
#endif
}
void JInputPointerWin::Update()
{
#ifdef __SFML__
	sf::Vector2i localPosition = sf::Mouse::getPosition(*mWindow);
	sf::Vector2f worldPos = mWindow->mapPixelToCoords(localPosition);
	worldPos.x -= gJEngine.GetSettings()->LogicalWidth / 2.f;
	worldPos.y -= gJEngine.GetSettings()->LogicalHeight / 2.f;
	mPointerX = worldPos.x;
	mPointerY = worldPos.y;

	//TODO MULTIPLE KEYS AT THE SAME TIME IF NEEDED
	char keyCode = Mouse_None;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		keyCode = Mouse_Left;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		keyCode = Mouse_Right;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		keyCode = Mouse_Middle;
	}
	HandleStateChange(keyCode);
#elif defined (__SDL__)
	int x, y;
	SDL_GetMouseState(&x, &y);
	mPointerX = (float)x- (float)gJEngine.GetSettings()->ScreenWidth / 2.f;
	mPointerY = (float)y- (float)gJEngine.GetSettings()->ScreenHeight / 2.f;
	mPointerX = (mPointerX* gJEngine.GetSettings()->LogicalWidth) / gJEngine.GetSettings()->ScreenWidth;
	mPointerY = (mPointerY* gJEngine.GetSettings()->LogicalHeight) / gJEngine.GetSettings()->ScreenHeight;
	//LOG_INFO(0, "PointerX:%f PointerY:%f\n", mPointerX,mPointerY);
	char keyCode = Mouse_None;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) 
	{
		keyCode = Mouse_Left;
	}
	else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		keyCode = Mouse_Right;
	}
	else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
	{
		keyCode = Mouse_Middle;
	}
	HandleStateChange(keyCode);
#endif
}
void JInputPointerWin::Activate()
{
}
void JInputPointerWin::Deactivate()
{

}