#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::RENDER;

JText::JText()
{
	if (!mRenderable)
	{
#ifdef __J_SIMPLE2D__
		mRenderable = new JTextSimple2D();
#elif defined(__SFML__)
		mRenderable = new JTextSFML();
#elif defined(__SDL__)
		mRenderable = new JTextSDL();
#else
		mRenderable = new JRenderable();
#endif
	}
}
JText::~JText()
{
	delete mRenderable;
	mRenderable = NULL;
}
void JText::Init(const std::string fontpath, const std::string name, JRenderableProperties properties)
{
	Init(name);
	mRenderable->Init(fontpath, name + " renderable", properties);
}
void JText::Init(const std::string name)
{
	JBase::Init(name);
}
void JText::SetText(std::string text)
{
	mText = text;
#ifdef __J_SIMPLE2D__
	static_cast<JTextSimple2D*>(mRenderable)->SetText(text);
#elif defined(__SFML__)
	static_cast<JTextSFML*>(mRenderable)->SetText(text);
#elif defined(__SDL__)
	static_cast<JTextSDL*>(mRenderable)->SetText(text);
#endif
}
std::string JText::GetText()
{
	return mText;
}
void JText::Clear()
{
	JBase::Clear();
	Deactivate();
	mRenderable->Clear();
}
void JText::Activate()
{
	JBase::Activate();
	mRenderable->Activate();
	gJRenderManager.GetRenderer()->AddRenderable(mRenderable);
}
void JText::Update()
{
	JBase::Update();
}
void JText::Deactivate()
{
	JBase::Deactivate();
	gJRenderManager.GetRenderer()->RemoveRenderable(mRenderable);
	mRenderable->Deactivate();
}