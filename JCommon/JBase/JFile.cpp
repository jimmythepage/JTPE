#include "JCommonPch.h"

using namespace J;
using namespace J::BASE;


JFile::JFile() : mAsyncTask(ASYNC_NONE),
	mIsBinary(false), mWStringData(L""), mStringData(""), mIsLoaded(false), mFilePath(""),
	mBinData(NULL), mIsDirty(false), mBinSize(0), mIsWide(false), mFromBlob(false)
{

}
JFile::~JFile()
{
}
void JFile::operator=(const JFile & f)
{
	mIsBinary = f.mIsBinary;
	mWStringData = f.mWStringData;
	mStringData = f.mStringData;
	mIsLoaded = f.mIsLoaded;
	mFilePath = f.mFilePath;
	mBinSize = f.mBinSize;
	mBinData = (char*)realloc(mBinData, mBinSize);
	memcpy_s(mBinData, mBinSize, f.mBinData, mBinSize);
	mIsWide = f.mIsWide;
	mFromBlob = f.mFromBlob;
}
void JFile::Init(const std::string name)
{
	JTask::Init(name);
}
void JFile::Update()
{
	switch (mAsyncTask)
	{
	case ASYNC_LOAD:
		LOG_INFO(0, "File %s is async loading\n", mName.c_str());
		Load(mFilePath, mIsWide, mIsBinary);
		LOG_INFO(0, "File %s is async loaded\n", mName.c_str());
		break;
	case ASYNC_WRITE:
		//TODO FILL WRITE TYPE
		break;
	}
	mAsyncTask = ASYNC_NONE;
}
void JFile::LoadAsync(const std::string filePath, const bool isWide, const bool isBinary)
{
	mFilePath = filePath;
	mIsWide = isWide;
	mIsBinary = isBinary;
	mAsyncTask = ASYNC_LOAD;
	Activate();
	Detach();
}
bool JFile::Load(const std::string filePath,const bool isWide, const bool isBinary)
{
	if (mIsLoaded)
	{
		Unload();
	}
	LOG_INFO(0, "File  %s is loading\n", mName.c_str());
	mIsDirty = true;
	mIsWide = isWide;
	mFilePath = filePath;
	mIsBinary = isBinary;

	mIsLoaded= mFromBlob = gJFileManager.LoadJFileFromBlob(*this);
	if (!mFromBlob)
	{
		mIsLoaded = _Load();
	}
	else
	{
		//TODO PUT mBinData into string format if not bin
	}
	if (mIsLoaded)
	{
		LOG_INFO(0, "File  %s is loaded\n", mName.c_str());
	}
	else
	{
		LOG_INFO(0, "File  %s was not loaded\n", mName.c_str());
	}
	mIsDirty = false;
	return mIsLoaded;
}
bool JFile::_Load()
{
	if (mIsBinary)
	{
		std::ifstream file(mFilePath, std::ios::in | std::ios::binary | std::ios::ate);
		if (file.is_open())
		{
			mBinSize = (size_t)file.tellg();
			mBinData = new char[mBinSize];
			file.seekg(0, std::ios::beg);
			file.read(mBinData, mBinSize);
			file.close();
			return true;
		}
	}
	else
	{
		if (mIsWide)
		{
			std::wstring line;
			std::wifstream myfile(mFilePath);
			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					mWStringData += line;
					mWStringData += JNEWLINE;
				}
				myfile.close();
				return true;
			}
		}
		else
		{
			std::string line;
			std::ifstream myfile(mFilePath);
			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					mStringData += line;
					mStringData += JNEWLINE;
				}
				myfile.close();
				return true;
			}
		}
		
	}
	return false;
}
void  JFile::Set(const std::string filePath, const char* data, const size_t size, const bool isBinary)
{
	ASSERT(!filePath.empty());
	mIsDirty = true;
	mFilePath = filePath;
	mIsBinary = isBinary;
	mIsWide = false;
	if (mIsBinary)
	{
		mBinSize = size;
		mBinData = (char*)realloc(mBinData, mBinSize);
		memcpy_s(mBinData, mBinSize, data, mBinSize);
	}
	else
	{
		mStringData=std::string(size, '.');
		memcpy(&mStringData[0], data, size);
	}
	mFromBlob = true;
	mIsLoaded = true;
	mIsDirty = false;
}
bool JFile::Write(const std::string filePath, const std::wstring data)
{
	ASSERT(!filePath.empty());
	mIsDirty = true;
	mWStringData = data;
	mFilePath = filePath;
	bool result = false;
	LOG_INFO(0, "Writing on File  %s\n", mName.c_str());
	std::wofstream myfile(filePath, std::ios_base::trunc);//FOW NOW NO APPEND IS POSSIBLE BY CHOICE
	if (myfile.is_open())
	{
		myfile << mWStringData;
		myfile.close();
		LOG_INFO(0, "File  %s written.\n", mName.c_str());
		result = true;
	}
	else
	{
		LOG_INFO(0, "File  %s NOT written.\n", mName.c_str());
	}
	mIsDirty = false;
	return result;
}
bool JFile::Write(const std::string filePath, const std::string data)
{
	ASSERT(!filePath.empty());
	mIsDirty = true;
	mStringData = data;
	mFilePath = filePath;
	bool result = false;
	LOG_INFO(0, "Writing on File  %s\n", mName.c_str());
	std::ofstream myfile(filePath, std::ios_base::trunc);//FOR NOW NO APPEND IS POSSIBLE BY CHOICE
	if (myfile.is_open())
	{
		myfile << mStringData;
		myfile.close();
		LOG_INFO(0, "File  %s written.\n", mName.c_str());
		result = true;
		return true;
	}
	else
	{
		LOG_INFO(0, "File  %s NOT written.\n", mName.c_str());
	}
	mIsDirty = false;
	return result;
}
bool JFile::Write(const std::string filePath, const char * data, const size_t size, float append)
{
	ASSERT(!filePath.empty());
	mIsDirty = true;
	mBinData = new char[size];
	mBinSize = size;
	mFilePath = filePath;
	memcpy_s(mBinData, size, data, size);
	bool result = false;
	LOG_INFO(0, "Writing on File  %s\n", mName.c_str());

	int mode = std::ios::out | std::ios_base::trunc | std::fstream::binary;
	if (append)
	{
		mode = std::ofstream::out | std::ofstream::app | std::fstream::binary;
	}
	std::ofstream myfile(filePath, mode);
	if (myfile.is_open())
	{
		myfile.write(mBinData, mBinSize);
		myfile.close();
		LOG_INFO(0, "File  %s written.\n", mName.c_str());
		mIsDirty = false;
		result = true;
	}
	else
	{
		LOG_INFO(0, "File  %s NOT written.\n", mName.c_str());
	}
	mIsDirty = false;
	return result;
}
void JFile::Unload()
{
	LOG_INFO(0, "File  %s is unloading\n", mName.c_str());
	mAsyncTask = ASYNC_NONE;
	if (mIsBinary)
	{
		delete[] mBinData;
		mBinData = NULL;
		mBinSize = 0;
	}
	else
	{
		mStringData.clear();
		mWStringData.clear();
	}
	mIsLoaded = false;
	mIsDirty = false;
	mIsWide = false;
	mFromBlob = false;
	LOG_INFO(0, "File  %s is unloaded\n", mName.c_str());
}
const std::string JFile::GetStringData()
{
	return mStringData;
}
const std::wstring JFile::GetWStringData()
{
	return mWStringData;
}
void JFile::Clear()
{
	JTask::Clear();
	mAsyncTask = ASYNC_NONE;
	mIsLoaded = false;
	mIsBinary = false;
	mIsWide = false;
	mFromBlob = false;
	mStringData.clear();
	mWStringData.clear();
	mFilePath.clear();
	delete[] mBinData;
	mBinData = NULL;
	mIsDirty = false;
	mBinSize = 0;
}
void JFile::Activate()
{
	JTask::Activate();
}
void JFile::Deactivate()
{
	JTask::Deactivate();
}