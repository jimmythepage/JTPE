#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::RENDER;

JRenderable::JRenderable()
{
}
JRenderable::~JRenderable()
{
}
void JRenderable::Init(const std::string filepath, const std::string name, JRenderableProperties properties)
{

}
void JRenderable::Init(const std::string filepath, const std::string name, JRenderableProperties properties, JRenderableProperties clip)
{

}
void JRenderable::Init(const std::string filepath, const std::string name)
{
	Init(name);
}
void JRenderable::Init(const std::string name)
{
	JBase::Init(name);
}
void JRenderable::Clear()
{
	JBase::Clear();
}
void JRenderable::Activate()
{
	JBase::Activate();
}
void JRenderable::Update()
{
	JBase::Update();
}
void JRenderable::Deactivate()
{
	JBase::Deactivate();
}