#ifndef JFILE
#define JFILE

namespace J
{
	namespace BASE
	{
		enum ASYNC_FILE_OP
		{
			ASYNC_NONE=0,
			ASYNC_LOAD,
			ASYNC_WRITE
		};
		class JFile: public ::J::TASK::JTask
		{
		public:
			JFile();
			virtual ~JFile();

			virtual void			Init(const std::string name);
			virtual void			Clear();
			virtual void			Update();
			virtual void			Activate();
			virtual void			Deactivate();

			void LoadAsync			(const std::string filePath, const bool isWide, const bool isBinary = false);
			bool Load				(const std::string filePath,const bool isWide, const bool isBinary=false);

			void Set				(const std::string filePath, const char* data, const size_t size, const bool isBinary = false);

			bool Write				(const std::string filePath, const std::string data);
			bool Write				(const std::string filePath, const std::wstring data);
			bool Write				(const std::string filePath, const char* data,const size_t size,float append=false);

			void Unload						();

			const std::string	GetStringData	();	
			const std::wstring	GetWStringData	();	
			const char*			GetBinData		()	{ return mBinData;						}
			const size_t		GetBinSize		()	{ return mBinSize;						}
			const bool			IsReadyToGet	()	{ return (!mIsDirty && mIsLoaded && mAsyncTask==ASYNC_NONE);		}
			const std::string	GetFilePath		()	{ return mFilePath;						}

			bool operator==(const JFile& rhs)
			{
				return (this->mFilePath == rhs.mFilePath);
			}
			void operator=(const JFile & f);
		private:
			bool _Load						();

			ASYNC_FILE_OP	mAsyncTask;

			bool			mIsBinary;
			bool			mIsWide;
			bool			mIsLoaded;
			bool			mIsDirty;
			bool			mFromBlob;
			
			std::string		mFilePath;
			std::string		mStringData;
			std::wstring	mWStringData; 
			char			*mBinData;
			size_t			mBinSize;
		};
	}
}
#endif // !JFILE