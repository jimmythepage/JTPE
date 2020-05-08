#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::RENDER;

J2DQuad::J2DQuad():mRenderable(NULL)
{
}
J2DQuad::~J2DQuad()
{
	delete mRenderable;
	mRenderable = NULL;
}
void J2DQuad::Init(const std::string name)
{
	JBase::Init(name);

	if (!mRenderable)
	{
#ifdef __OGL__
		mRenderable = new J2DQuadOGL();
#else
		mRenderable = new JRenderable();
#endif
		std::vector<float> vertex_buffer_data;
		std::vector<unsigned int> indices_buffer_data;
		float step = 0.5f;
		vertex_buffer_data=
		{
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f
		};
		//mRenderable->Init(name + " renderable", vertex_buffer_data);
	}
}
void J2DQuad::Clear()
{
	JBase::Clear();
	Deactivate();
	mRenderable->Clear();
}
void J2DQuad::Activate()
{
	JBase::Activate();
	mRenderable->Activate();
	gJRenderManager.GetRenderer()->AddRenderable(mRenderable);
}
void J2DQuad::Update()
{
	JBase::Update();
}
void J2DQuad::Deactivate()
{
	JBase::Deactivate();
	gJRenderManager.GetRenderer()->RemoveRenderable(mRenderable);
	mRenderable->Deactivate();
}