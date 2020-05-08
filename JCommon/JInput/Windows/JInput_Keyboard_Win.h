#ifndef JINPUTKEYBOARDWIN
#define JINPUTKEYBOARDWIN

namespace J
{
	namespace INPUT
	{
		class JInputKeyboardWin : public ::J::INPUT::JInputKeyboard
		{
		public:
			JInputKeyboardWin();
			~JInputKeyboardWin();

			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();
		private:
		};
	}
}

#endif // !JINPUTKEYBOARDWIN
