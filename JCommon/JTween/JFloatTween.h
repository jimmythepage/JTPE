#ifndef JFLOATTWEEN
#define JFLOATTWEEN

namespace J
{
	namespace TWEEN
	{
		class JFloatTween : public JBaseTween
		{
		public:
			JFloatTween();
			~JFloatTween();

			virtual void Init(const std::string name, long long time,float value,float goal);
			virtual void Clear();

			virtual void InvertValues();

			float GetValue();
		protected:
			float mStart,mGoal;
		};
	}
}
#endif