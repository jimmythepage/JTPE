#ifndef JPHYSICSBOX2D
#define JPHYSICSBOX2D

namespace J
{
	namespace PHYSICS
	{
		class JPhysicsBox2D : public ::J::PHYSICS::JPhysics
		{
		public:
			JPhysicsBox2D();
			~JPhysicsBox2D();

			void Init(const std::string name);
			void Clear(); 
			void PreFrame();
			void Update();
			void PostFrame();
			void Activate();
			void Deactivate();

			b2World*	GetWorld() { return mWorld; }
		private:
			b2World*	mWorld;
			b2Vec2		mGravityb2;
			float32		mTimeStep;
			int32		mVelocityIterations;
			int32		mPositionIterations;
		};
	}
}

#endif // !JRENDERERSDL
