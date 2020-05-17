#ifndef JTIMER
#define JTIMER

namespace J
{
	namespace BASE
	{
		class JTimer: public ::J::BASE::JBase
		{
		public:
			JTimer();
			virtual ~JTimer();

			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();

			virtual void	SetTime(__int64 time);//IN MILLISECONDS
			virtual void	SetCallback(std::function<void()> callback) { mTimerCallback = callback; }
			virtual void	StartTimer(bool restart=true,bool repeat=false);
			virtual void	StopTimer();
			virtual __int64 GetTime()			{ return mTime; }
			virtual __int64 GetTimeToReach()	{ return mTimeToReach; }
			virtual bool		IsFinished() { return mTime >= mTimeToReach; }
		private:
			virtual void Activate();
			virtual void Deactivate();

			bool			DoTick();

			__int64	mTimeToReach;
			__int64	mTime;
			bool	mRepeat;

			std::chrono::high_resolution_clock::time_point mStartTime;

			std::function<void()> mTimerCallback;
		};
	}
}
#endif // !JOBJECT