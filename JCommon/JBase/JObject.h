#ifndef JOBJECT
#define JOBJECT

namespace J
{
	namespace BASE
	{
		class JObject: public JBase
		{
		public:
			JObject();
			virtual ~JObject();

			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();
		};
	}
}
#endif // !JOBJECT