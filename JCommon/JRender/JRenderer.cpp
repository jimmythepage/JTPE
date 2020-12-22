#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::RENDER;

static bool RenderableCompare(JRenderable* a, JRenderable* b)
{
	return (a->GetProperties().Z+a->GetProperties().ZAdd) <
		(b->GetProperties().Z+b->GetProperties().ZAdd);
}

JRenderer::JRenderer():mScreenWidth(1000), mScreenHeight(1000), mFullScreen(false)
{
}
JRenderer::~JRenderer()
{
}
void JRenderer::Init(const std::string name, const std::string appName)
{
	JBase::Init(name);
	mScreenWidth = gJEngine.GetSettings()->ScreenWidth;
	mScreenHeight = gJEngine.GetSettings()->ScreenHeight;
	mLogicalWidth = gJEngine.GetSettings()->LogicalWidth;
	mLogicalHeight = gJEngine.GetSettings()->LogicalHeight;
	mFullScreen = gJEngine.GetSettings()->FullScreen;
  mIsTransparent = gJEngine.GetSettings()->Transparent;
  mRCutoff = gJEngine.GetSettings()->R_CutOff;
  mGCutoff = gJEngine.GetSettings()->G_CutOff;
  mBCutoff = gJEngine.GetSettings()->B_CutOff;
}
void JRenderer::Clear()
{
	JBase::Clear();
	for (JRenderable* renderable : mRenderableToRender)
	{
		renderable->Clear();
		delete renderable;
		renderable = NULL;
	}
	mRenderableToRender.clear();
}
void JRenderer::AddRenderable(JRenderable* renderable) 
{ 
	mRenderableToRender.push_back(renderable);
	SortRenderables();
}
void JRenderer::RemoveRenderable(JRenderable* renderable) 
{ 
	mRenderableToRender.remove(renderable);
	SortRenderables();
}
void JRenderer::SortRenderables()
{
	mRenderableToRender.sort(RenderableCompare);
}
void JRenderer::PreFrame()
{

}
void JRenderer::Update()
{
}
void JRenderer::PostFrame()
{

}
void JRenderer::Activate()
{
	JBase::Activate();
}
void JRenderer::InitShaders()
{

}
void JRenderer::LoadShaders()
{
	
}
void JRenderer::UseShader(JShaderType type)
{

}
void JRenderer::UnloadShaders()
{

}
void JRenderer::Deactivate()
{
	JBase::Deactivate();
}