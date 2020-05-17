#ifndef JINPUTMANAGER
#define JINPUTMANAGER

namespace J
{
	namespace INPUT
	{
		class JInputManager : public ::J::BASE::JBase
		{
		public:
			JInputManager();
			~JInputManager();

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static JInputManager & GetSingleton();

			void Init(const std::string name);
			void Clear();
			void Update();
			void Activate();
			void Deactivate();

			JInputKeyboard* const	GetInputKeyboard() { return mJInputKeyboard; }
			JInputPointer* const	GetInputPointer() { return mJInputPointer; }
		private: 
			JInputKeyboard *	mJInputKeyboard;
			JInputPointer*		mJInputPointer;
		};
#define gJInputManager ::J::INPUT::JInputManager::GetSingleton()
	}
}

#endif
