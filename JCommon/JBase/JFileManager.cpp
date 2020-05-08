#include "JCommonPch.h"

using namespace J;
using namespace J::BASE;

const std::string Bin = "BIN";

JFileManager::JFileManager() :mIsBlobDataLoaded(false)
{
}
JFileManager::~JFileManager()
{
}
JFileManager & JFileManager::GetSingleton()
{
	static JFileManager _singleton;
	return _singleton;
}
void JFileManager::Init(const std::string name, bool usesBlob)
{
	JBase::Init(name);
	mLoadedJFiles.clear();
	if (!usesBlob)
	{
		BuildBlobData();
	}
	else
	{
		LoadBlobData();
	}
}
void JFileManager::Clear()
{
	JBase::Clear();
	mIsBlobDataLoaded = false;
}
void JFileManager::Update()
{

}
void JFileManager::Activate()
{
	JBase::Activate();
}
void JFileManager::Deactivate()
{
	JBase::Deactivate();
}
void J::BASE::JFileManager::BuildBlobData()
{
	JFile buildData;
	buildData.Init("BuildData");
	bool loaded = buildData.Load(JBUILD_FILES, false, false);
	if (!loaded)
	{
		return;
	}
	std::string data = buildData.GetStringData();
	buildData.Unload();
	std::istringstream f(data);
	std::string arg;
	std::getline(f, arg);
	if (arg == "NO")
	{
		return;
	}
	LOG_INFO(0, "Build Files founded and allowed starting the scouting\n", 0);
	std::string savePath = gJEngine.GetSettings()->DataFolder;
	savePath += JDATA_FILES;
	JFile saveFile;
	saveFile.Init(JDATA_FILES);
	saveFile.Write(savePath, NULL, 0);
	char* allBlob = NULL;
	size_t blobSize = 0;
	size_t  blobIndex = 0;
	unsigned int fileCount = 0;
	//PRE ALLOCATE MEMORY FOR FILE COUNT
	blobSize += sizeof(unsigned int);
	allBlob = (char*)realloc(allBlob, blobSize);
	blobIndex = blobSize;
	while (std::getline(f, arg))
	{
		fileCount++;
		//WRITE IS BINARY
		unsigned char bin = (arg == Bin)?'y':'n';
		blobSize += sizeof(unsigned char);
		allBlob = (char*)realloc(allBlob, blobSize);
		memcpy(&allBlob[blobIndex], &bin, sizeof(unsigned char));
		//LOADING FILE
		std::getline(f, arg);
		JFile file;
		file.Init(arg);
		bool load = file.Load(arg, false, (bin=='y'));
		ASSERT(load);
		//WRITE FILE PATH SIZE
		blobIndex = blobSize;
		blobSize += sizeof(size_t);
		allBlob = (char*)realloc(allBlob, blobSize);
		size_t size = arg.size();
		memcpy(&allBlob[blobIndex], &size, sizeof(size_t));
		//WRITE FILE PATH
		blobIndex = blobSize;
		blobSize += arg.size();
		allBlob = (char*)realloc(allBlob, blobSize);
		memcpy_s(&allBlob[blobIndex], blobSize, arg.c_str(), arg.size());
		//WRITE FILE SIZE
		blobIndex = blobSize;
		blobSize += sizeof(size_t);
		size_t fileSize = 0;
		allBlob = (char*)realloc(allBlob, blobSize);
		if (bin=='y')
		{
			fileSize= file.GetBinSize();
		}
		else
		{
			fileSize = file.GetStringData().size();
		}
		memcpy(&allBlob[blobIndex], &fileSize, sizeof(size_t));
		//WRITE FILE DATA
		blobIndex = blobSize;
		if (bin == 'y')
		{
			blobSize += file.GetBinSize();
			allBlob = (char*)realloc(allBlob, blobSize);
			memcpy_s(&allBlob[blobIndex], blobSize, file.GetBinData(), file.GetBinSize());
		}
		else
		{
			blobSize += file.GetStringData().size();
			allBlob = (char*)realloc(allBlob, blobSize);
			memcpy_s(&allBlob[blobIndex], blobSize, file.GetStringData().c_str(), file.GetStringData().size());
		}
		blobIndex = blobSize;
	}
	memcpy(allBlob, &fileCount, sizeof(unsigned int));
	char * crunchBuffer = (char *)malloc(blobSize);
	Crunch(allBlob, crunchBuffer, blobSize);
	saveFile.Write(savePath, crunchBuffer, blobSize, true);
	//saveFile.Write(savePath, allBlob, blobSize, true);
	saveFile.Clear();
	EXIT(15);
}
void JFileManager::Crunch(const char * data, char * buffer, size_t dataLength)
{
	srand(0xCE558671);

	const char * peek = data;
	char *poke = buffer;

	for (size_t i = 0; i < dataLength; i++, peek++, poke++)
	{
		char key = (char)(rand() % 0xFF);
		(*poke) = ((*peek) ^ key);
	}
}
std::vector<std::string> split(std::string stringToBeSplitted, std::string delimeter)
{
	std::vector<std::string> splittedString;
	size_t startIndex = 0;
	size_t  endIndex = 0;
	while ((endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size())
	{
		std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
		splittedString.push_back(val);
		startIndex = endIndex + delimeter.size();
	}
	if (startIndex < stringToBeSplitted.size())
	{
		std::string val = stringToBeSplitted.substr(startIndex);
		splittedString.push_back(val);
	}
	return splittedString;
}
void JFileManager::LoadBlobData()
{
	JFile blobData;
	blobData.Init("BlobData");
	std::string path = gJEngine.GetSettings()->DataFolder;
	path += JDATA_FILES;
	bool loaded = blobData.Load(path, false, true);
	if (!loaded)
	{
		return;
	}
	char * blobBuffer = (char *)malloc(blobData.GetBinSize());
	Crunch(blobData.GetBinData(), blobBuffer, blobData.GetBinSize());

	LOG_INFO(0, "%s", blobBuffer);

	size_t index = 0;
	unsigned int fileCount = 0;
	memcpy(&fileCount, &blobBuffer[index], sizeof(unsigned int));
	index += sizeof(unsigned int);
	for (unsigned int i = 0; i < fileCount; i++)
	{
		//BINARY
		unsigned char isBinary;
		memcpy(&isBinary, &blobBuffer[index], sizeof(unsigned char));
		index += sizeof(unsigned char);
		//PATH SIZE
		size_t filePathSize = 0;
		memcpy(&filePathSize, &blobBuffer[index], sizeof(size_t));
		index += sizeof(size_t);
		//FILE PATH
		std::string filePath(filePathSize, '.');
		memcpy(&filePath[0], &blobBuffer[index], filePathSize);
		filePath.erase(std::remove(filePath.begin(), filePath.end(), '\\'), filePath.end());
		filePath.erase(std::remove(filePath.begin(), filePath.end(), '/'), filePath.end());
		index += filePathSize;
		//FILE SIZE
		size_t fileSize = 0;
		memcpy(&fileSize, &blobBuffer[index], sizeof(size_t));
		index += sizeof(size_t);
		//FILE DATA
		char* data = NULL;
		data = (char*)realloc(data, fileSize);
		memcpy(data, &blobBuffer[index], fileSize);
		JFile* file = new JFile();
		file->Set(filePath, data, fileSize, isBinary =='y');
		std::pair<std::string, JFile* > pair(filePath, file);
		mLoadedJFiles.insert(pair);
		index += fileSize;
	}
	mIsBlobDataLoaded = true;
}
bool JFileManager::LoadJFileFromBlob(JFile& file)
{
	if (!mIsBlobDataLoaded)
	{
		return false;
	}
	std::string filePathforKey = file.GetFilePath();
	filePathforKey.erase(std::remove(filePathforKey.begin(), filePathforKey.end(), '\\'), filePathforKey.end());
	filePathforKey.erase(std::remove(filePathforKey.begin(), filePathforKey.end(), '/'), filePathforKey.end());
	if (mLoadedJFiles.find(filePathforKey) != mLoadedJFiles.end())
	{
		JFile* fileFromBlob = mLoadedJFiles[filePathforKey];
		if (fileFromBlob)
		{
			file = *fileFromBlob;
			return true;
		}
	}
	return false;
}
