#ifndef JTEXTDB
#define JTEXTDB

namespace J
{
	namespace BASE
	{
		enum Language
		{
			ENG=0,
			ITA
		};
		class JTextDB : public ::J::BASE::JBase
		{
		public:
			JTextDB();
			~JTextDB();

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static JTextDB & GetSingleton();

			void Init(const std::string name);
			void Clear();

			std::string		GetTextEntry(std::string textID);
			void			SetLanguage(Language language)	{ mLanguage = language; }
			const Language	GetLanguage	()					{ return mLanguage; }
		private:
			std::map<std::string, std::vector<std::string>> mTextEntries;
			Language mLanguage;
		};
#define gJTextDB ::J::BASE::JTextDB::GetSingleton()
	}
}

#endif // !JRENDERMANAGER
