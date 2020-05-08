#ifndef JBODYBOX2D
#define JBODYBOX2D

namespace J
{
	namespace PHYSICS
	{
		class JBodyBox2D : public ::J::PHYSICS::JBody
		{
		public:
			JBodyBox2D();
			~JBodyBox2D();

			virtual void Init(const std::string name, J::RENDER::JRenderableProperties properties, BodyType type);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual void ApplyForce(const JVec2& force, const JVec2& point, bool wake);
			virtual void ApplyForceToCenter(const JVec2& force, bool wake);
			virtual void ApplyLinearImpulse(const JVec2& impulse, const JVec2& point, bool wake);
			virtual void ApplyLinearImpulseToCenter(const JVec2& impulse, bool wake);
			virtual void ApplyAngularImpulse(float impulse, bool wake);

			J::RENDER::JRenderableProperties	GetTransformedProperties(J::RENDER::JRenderableProperties	baseProperties);
		protected:
			b2BodyDef		mBodyDef;
			b2PolygonShape	mShape;
			b2FixtureDef	mFixture;
			b2Body*			m2DBody;
		};
	}
}

#endif // !JSPRITESDL
