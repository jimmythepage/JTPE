#ifndef JPHYSICS
#define JPHYSICS

using namespace J::RENDER;

namespace J
{
	namespace PHYSICS
	{
		class JPhysics : public ::J::BASE::JBase
		{
		public:
			JPhysics();
			~JPhysics();

			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual void PreFrame();
			virtual void PostFrame();

			float		GetScaleFactor() { return mScaleFactor; }
			JVec2		GetGravity() { return mGravity; }
		protected:
			float		mScaleFactor;
			JVec2		mGravity;
		};
	}
}

#endif // !JRENDERER
