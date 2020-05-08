#include "JCommonPch.h"

using namespace J;
using namespace J::BASE;


JBase::JBase():mName(""), mIsActive(false)
{

}
JBase::~JBase()
{

}
void JBase::Init(const std::string name)
{
	mName = name;
}
void JBase::Clear()
{
	mName = "";
}
void JBase::Update()
{
}
void JBase::Activate()
{
	mIsActive = true;
}
void JBase::Deactivate()
{
	mIsActive = false;
}