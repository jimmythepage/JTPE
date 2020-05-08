#ifndef JPHYSICOBJECT
#define JPHYSICOBJECT

namespace J
{
	namespace PHYSICS
	{
		enum BodyType
		{
			None,
			Trigger,
			Dynamic,
			Static
		};
		class JPhysicObject : public ::J::BASE::JBase
		{
		public:
			JPhysicObject();
			~JPhysicObject();

			virtual void Init(const std::string name, J::RENDER::JRenderableProperties properties, BodyType type);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();
			
			JBody*			GetBody() { return mBody; }
		protected:
			JBody*			mBody;
		private:
		};
	}
}

#endif // !JPhysicObject
