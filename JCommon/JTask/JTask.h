#ifndef JTASK
#define JTASK

namespace J
{
	namespace TASK
	{
		class JTask : public ::J::BASE::JBase
		{
		public:
			JTask();
			~JTask();

			virtual void	Init(const std::string name);
			virtual void	Clear();
			virtual void	Update();
			virtual void	Activate();
			virtual void	Deactivate();

			void			Join();
			void			Detach();
			virtual bool	IsRunning() { return mIsRunning; }
		protected:
			std::thread		mThread;
			bool			mIsRunning;
		};
	}
}

#endif // !JTASK
