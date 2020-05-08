#ifndef JFILEMANAGER
#define JFILEMANAGER

namespace J
{
	namespace BASE
	{
		class JFileManager : public ::J::BASE::JBase
		{
		public:
			JFileManager();
			~JFileManager();

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static JFileManager & GetSingleton();

			void Init(const std::string name,bool usesBlob);
			void Clear();
			void Update();
			void Activate();
			void Deactivate();

			void BuildBlobData();
			void LoadBlobData();

			bool LoadJFileFromBlob(JFile& file);
		private: 
			bool mIsBlobDataLoaded;

			void Crunch(const char * data, char * buffer, size_t dataLength);
			std::map<std::string, JFile*> mLoadedJFiles;
		};
#define gJFileManager ::J::BASE::JFileManager::GetSingleton()
	}
}

#endif // !JRENDERMANAGER
