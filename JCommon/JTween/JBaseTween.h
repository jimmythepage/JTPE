#ifndef JBASETWEEN
#define JBASETWEEN

namespace J
{
	namespace TWEEN
	{
		class JBaseTween: public ::J::BASE::JBase
		{
		public:
			JBaseTween();
			virtual ~JBaseTween();

			virtual void		Init(const std::string name, long long time);
			virtual void		SetPlayStyle(PlayStyle style);
			virtual	PlayStyle	GetPlayStyle() { return mPlayStyle; }
			virtual void		SetPlayCurve(PlayCurve curve) { mPlayCurve = curve; }
			virtual	PlayCurve	GetPlayCurve() { return mPlayCurve; }
			virtual void		SetLoop(bool loop) { mLoop = loop; }
			virtual bool		GetLoop() { return mLoop; }
			virtual void		Clear();
			virtual void		Update();

			virtual void		StartTween();
			virtual void		RestartTween();
			virtual void		StopTween();

			virtual bool		IsTweening(){return mTimer.IsActive();};
			virtual bool		IsFinished() { return (mStarted && !mTimer.IsActive()); }

			virtual float		Lerp(float a, float b, float f);
		protected:
			virtual void			TimerCallback();
			virtual void			InvertValues();
			J::BASE::JTimer mTimer;
			bool			mStarted;
			bool			mLoop;
			unsigned int	mRoundCount;
			PlayStyle		mPlayStyle;
			PlayCurve		mPlayCurve;
		};
	}
}
#endif