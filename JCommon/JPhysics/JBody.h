#ifndef JBODY
#define JBODY

using namespace J::RENDER;

namespace J
{
	namespace PHYSICS
	{
		class JBody : public ::J::BASE::JBase
		{
		public:
			JBody();
			~JBody();

			virtual void Init(const std::string name, J::RENDER::JRenderableProperties properties, BodyType type);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual void ApplyForce(const JVec2& force, const JVec2& point, bool wake) {}
			virtual void ApplyForceToCenter(const JVec2& force, bool wake) {}
			virtual void ApplyLinearImpulse(const JVec2& impulse, const JVec2& point, bool wake) {}
			virtual void ApplyLinearImpulseToCenter(const JVec2& impulse, bool wake) {}
			virtual void ApplyAngularImpulse(float impulse, bool wake) {}

			virtual float GetFriction() { return mFriction; }
			virtual float GetGravityScale() { return mGravityScale; }
			virtual void  SetFriction(float friction) { mFriction= friction; }
			virtual void  SetGravityScale(float gravity) { mGravityScale= gravity; }

			virtual J::RENDER::JRenderableProperties	GetTransformedProperties(J::RENDER::JRenderableProperties	baseProperties);
		protected:
			BodyType	mBodyType;
			float		mFriction;
			float		mGravityScale;
		private:
		};
	}
}

#endif // !JBody
