#ifndef IJBASE
#define IJBASE

namespace J
{
	namespace BASE
	{
		class iJBase
		{
		public:
			iJBase() {};
			virtual ~iJBase() {};
			virtual void Init(const std::string name)=0;
			virtual void Clear()=0;
			virtual void Update()=0;
			virtual void Activate()=0;
			virtual void Deactivate()=0;
			virtual bool IsActive() = 0;
		};
	}
}
#endif // !IJBASE