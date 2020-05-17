#include "JCommonPch.h"

using namespace J;
using namespace J::TASK;
using namespace J::NET;

const __int64 TIMEOUT_REQUEST = 2000;

JRequest::JRequest():mResponseReady(false)
{
}
JRequest::~JRequest()
{
	
}
void JRequest::Init(const std::string name)
{
	JTask::Init(name);
	mResponseReady = false;
}
void JRequest::Clear()
{
	JTask::Clear();
}
void JRequest::Update()
{
	LOG_INFO(0, "%s started a request\n", mName.c_str());
#ifdef __LIBCURL__
	try
	{
		curlpp::Cleanup clean;
		curlpp::Easy r;
		r.setOpt(new curlpp::options::Url(mUrl));
		if (!mBody.empty())
		{
			r.setOpt(new curlpp::options::PostFields(mBody));
			r.setOpt(new curlpp::options::PostFieldSize((const long)mBody.length()));
		}

		std::ostringstream response;
		r.setOpt(new curlpp::options::WriteStream(&response));

		r.perform();

		mResponse=(response.str());
		mResponseReady = true;
		//TIMEOUT SET AND TEST
		//POST SETTING
	}
	catch (curlpp::RuntimeError &e)
	{
		std::string error = e.what();
		LOG_WARNING(error.c_str());
	}
	catch (curlpp::LogicError &e)
	{
		std::string error = e.what();
		LOG_WARNING(error.c_str());
	}
	

#endif
	LOG_INFO(0, "%s finished a request\n", mName.c_str());
}
void JRequest::Activate()
{
	JTask::Activate();
	LOG_INFO(0, "%s is Activated\n", mName.c_str());
}
void JRequest::Deactivate()
{
	JTask::Deactivate();
	LOG_INFO(0, "%s is Deactivated\n", mName.c_str());
}
void JRequest::Request(const std::string url, const std::string body)
{
	mResponseReady = false;
	mUrl = url;
	mBody = body;
	Activate();
	Detach();
}