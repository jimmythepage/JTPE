#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::RENDER;

JRenderManager::JRenderManager():mJRenderer(NULL)
{
}
JRenderManager::~JRenderManager()
{
}
JRenderManager & JRenderManager::GetSingleton()
{
	static JRenderManager _singleton;
	return _singleton;
}
void EngineUpdate()//KEEP IT LOCAL
{
	gJEngine.Update();
}
void JRenderManager::Init(const std::string name, const std::string appName)
{
	JBase::Init(name);
	if (!mJRenderer)
	{
#if defined(__J_SIMPLE2D__)
		mJRenderer = new JRendererSimple2D();
		static_cast<JRendererSimple2D*>(mJRenderer)->Init("mJRenderer Simple2D", EngineUpdate);
#elif   defined(__OGL__)
		mJRenderer = new JRendererOGL();
		mJRenderer->Init("mJRenderer OGL");
#elif defined(__DIRECTX__)
		mJRenderer = new JRendererDX();
		mJRenderer->Init("mJRenderer DirectX"); 
#elif defined(__SFML__)
		mJRenderer = new JRendererSFML();
		mJRenderer->Init("mJRenderer SFML");
#elif defined (__SDL__)
		mJRenderer = new JRendererSDL();
		mJRenderer->Init("mJRenderer SDL",appName);
#else
		mJRenderer = new JRenderer();
		mJRenderer->Init("mJRenderer Generic",appName);
#endif
	}
}
void JRenderManager::Clear()
{
	JBase::Clear();
	if (mJRenderer)
	{
		mJRenderer->Clear();
		delete mJRenderer;
		mJRenderer = NULL;
	}
}
void JRenderManager::Update()
{
	mJRenderer->PreFrame();
	mJRenderer->Update();
	mJRenderer->PostFrame();
}
void JRenderManager::Activate()
{
	mJRenderer->Activate();
	JBase::Activate();
}
void JRenderManager::Deactivate()
{
	JBase::Deactivate();
	mJRenderer->Deactivate();
}