#ifndef JREQUEST
#define JREQUEST

namespace J
{
	namespace NET
	{
		class JRequest : public ::J::TASK::JTask
		{
		public:
			JRequest();
			~JRequest();

			void Init(const std::string name);
			void Clear();
			void Update();
			void Activate();
			void Deactivate();

			void Request(const std::string url, const std::string body="");
			
			bool				IsResponseReady() { return mResponseReady; }
			std::string GetResponse() { return mResponse; }

		private:
			std::string			mUrl;
			std::string			mBody;
			std::string			mResponse;
			bool						mResponseReady;
		};
	}
}

#endif // !JREQUEST
