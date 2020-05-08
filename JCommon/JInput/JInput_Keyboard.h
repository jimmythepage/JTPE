#ifndef JINPUTKEYBOARD
#define JINPUTKEYBOARD

namespace J
{
	namespace INPUT
	{
		class JInputKeyboard : public ::J::BASE::JBase
		{
		public:
			JInputKeyboard();
			~JInputKeyboard();

			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			bool GetKeyHeld(char keyCode);
			bool GetKeyPressed(char keyCode);

			const char GetKeyCode()	{ return mKeyCode; }
		protected:
			void			HandleStateChange(char keyCode);

			char			mKeyCode;
			JKeyState		mKeyState;
		};
	}
}

#endif // !JINPUTKEYBOARD
