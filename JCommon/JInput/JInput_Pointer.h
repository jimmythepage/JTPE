#ifndef JINPUTPOINTER
#define JINPUTPOINTER

namespace J
{
	namespace INPUT
	{
		class JInputPointer : public ::J::BASE::JBase
		{
		public:
			JInputPointer();
			~JInputPointer();

			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			float GetPointerX() { return mPointerX; }
			float GetPointerY() { return mPointerY; }
			
			bool GetPointerPressed(char keyCode);
			bool GetPointerDown(char keyCode);
			bool GetPointerReleased(char keyCode);

			const char GetMouseCode() { return mMouseCode; }
		protected:
			void			HandleStateChange(char keyCode);

			char				mMouseCode;
			JPointerState		mPointerState;

			float	mPointerX, mPointerY;
		};
	}
}

#endif // !JINPUTKEYBOARD
