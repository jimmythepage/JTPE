#include "JCommonPch.h"
#include "JBodyBox2D.h"


using namespace J;
using namespace J::PHYSICS;

JBodyBox2D::JBodyBox2D():m2DBody(NULL)
{
}
JBodyBox2D::~JBodyBox2D()
{
}
void JBodyBox2D::Init(const std::string name, J::RENDER::JRenderableProperties properties, BodyType type)
{
	JBody::Init(name, properties,type);
	if (mBodyType == None)
	{
		return;//NO PHYSICS NEEDED
	}
	else if (mBodyType == Dynamic)
	{
		mBodyDef.type = b2BodyType::b2_dynamicBody;
		mBodyDef.gravityScale = mGravityScale;
		mFixture.friction = mFriction;
		mFixture.density = 1.0f;
	}
	else if (mBodyType == Trigger)
	{
		mBodyDef.type = b2BodyType::b2_dynamicBody;
		mFixture.density = 0.0f;
	}
	else if (mBodyType == Static)
	{
		mBodyDef.type = b2BodyType::b2_staticBody;
		mFixture.density = 0.0f;
	}
	mBodyDef.position.Set(properties.Position.x*gJPhysicsManager.GetPhysics()->GetScaleFactor()
		, properties.Position.y*gJPhysicsManager.GetPhysics()->GetScaleFactor());
	mBodyDef.angle = properties.Rot;

	m2DBody=static_cast<JPhysicsBox2D*>(gJPhysicsManager.GetPhysics())->GetWorld()->CreateBody(&mBodyDef);
	mShape.SetAsBox(properties.Size.x*gJPhysicsManager.GetPhysics()->GetScaleFactor()/2.f
		, properties.Size.y*gJPhysicsManager.GetPhysics()->GetScaleFactor() / 2.f);
	mFixture.shape = &mShape;
	m2DBody->CreateFixture(&mFixture);
}
J::RENDER::JRenderableProperties JBodyBox2D::GetTransformedProperties(J::RENDER::JRenderableProperties	baseProperties)
{
	if (mBodyType == None)
	{
		return baseProperties;//NO PHYSICS NEEDED
	}
	b2Vec2 position = m2DBody->GetPosition();
	float32 angle = m2DBody->GetAngle();
	baseProperties.Rot = angle;
	baseProperties.Position.x = position.x/gJPhysicsManager.GetPhysics()->GetScaleFactor();
	baseProperties.Position.y = position.y / gJPhysicsManager.GetPhysics()->GetScaleFactor();
	//LOG_INFO(0, "%4.2f %4.2f %4.2f\n", baseProperties.Position.x, baseProperties.Position.y, baseProperties.Rot);
	return baseProperties;
}
void JBodyBox2D::Clear()
{
	JBody::Clear();
	if (m2DBody)
	{
		static_cast<JPhysicsBox2D*>(gJPhysicsManager.GetPhysics())->GetWorld()->DestroyBody(m2DBody);
		m2DBody = NULL;
	}
}
void JBodyBox2D::Activate()
{
	JBody::Activate();
}
void JBodyBox2D::Update()
{
	JBody::Update();
	if (mBodyType == None)
	{
		return;
	}
	m2DBody->SetGravityScale(mGravityScale);

	//TODO CONTROLLARE BENE BOUNDARIES
	//TODO COLLEGARE FUNZIONI DI COLLISIONE (OnEnter, OnStay, OnExit)
	//TODO FILTERING
}
void JBodyBox2D::ApplyForce(const JVec2& force, const JVec2& point, bool wake)
{
	m2DBody->ApplyForce(b2Vec2(force.x, force.y), b2Vec2(point.x, point.y), wake);
}
void JBodyBox2D::ApplyForceToCenter(const JVec2& force, bool wake)
{
	m2DBody->ApplyForceToCenter(b2Vec2(force.x, force.y), wake);
}
void JBodyBox2D::ApplyLinearImpulse(const JVec2& impulse, const JVec2& point, bool wake)
{
	m2DBody->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), b2Vec2(point.x, point.y), wake);
}
void JBodyBox2D::ApplyLinearImpulseToCenter(const JVec2& impulse, bool wake)
{
	m2DBody->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), wake);
}
void JBodyBox2D::ApplyAngularImpulse(float impulse, bool wake)
{
	m2DBody->ApplyAngularImpulse(impulse, wake);
}
void JBodyBox2D::Deactivate()
{
	JBody::Deactivate();
}