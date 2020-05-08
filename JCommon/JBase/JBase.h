#ifndef JBASE
#define JBASE

namespace J
{
	namespace BASE
	{
		class JBase: public iJBase
		{
		public:
			JBase();
			virtual ~JBase();
			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			bool			IsActive() { return mIsActive; }
			std::string		GetName	() { return mName; }
		protected:
			std::string		mName;
			bool			mIsActive;
		};
	}
}

#endif // !JBASE