#ifndef JSAVINGSYSYSTEM
#define JSAVINGSYSYSTEM

namespace J
{
	namespace BASE
	{
		class JSavingSystem : public ::J::BASE::JBase
		{
		public:
			JSavingSystem();
			~JSavingSystem();

			virtual void			Init(const std::string name);
			virtual void			Clear();
			virtual void			Update();
			virtual void			Activate();
			virtual void			Deactivate();

			//FIRST YOU ACTIVATE THEN YOU USE EVERY OTHER METHODS REFERRING TO THE ACTIVATED DATA
			virtual void			ActivateData(const std::string dataKey);

			virtual bool			LoadData(const std::string path);
			virtual bool			SaveData();
			virtual void			ClearData();
			virtual	json* const		GetData();

			virtual bool			IsKeyExisting(const std::string key);
			virtual void			SetString(const std::string key, const std::string value);
			virtual void			SetInt(const std::string key, const int value);
			virtual void			SetUnsignedInt(const std::string key, const unsigned int value);
			virtual void			SetFloat(const std::string key, const float value);
			virtual void			SetBool(const std::string key, const bool value);
			virtual void			SetJson(const std::string key, const json value);
			virtual void			SetVectorOfJson(const std::string key, const std::vector<json> value);

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static JSavingSystem & GetSingleton();
		protected:
			std::map<std::string, json> mDatas;
			std::string					mCurrentDataKey;
			std::string					mCurrentDataPath;
		};
#define gJSavingSystem ::J::BASE::JSavingSystem::GetSingleton()
	}
}

#endif // !JSavingSystem
