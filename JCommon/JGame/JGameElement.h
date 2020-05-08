#ifndef JGAMEELEMENT
#define JGAMEELEMENT


namespace J
{
	namespace PHYSICS
	{
		class	JPhysicObject;
		enum	BodyType;
	}
	namespace GAME
	{
		class JGameCamera;

		class JGameElement : public ::J::BASE::JBase
		{
		public:
			JGameElement();
			~JGameElement();

			virtual void Init(const std::string name, std::string applink = "");
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			std::string  GetAppLink	()				{ return mAppLink; }

			void							SetParent		(JGameElement* parent, bool retain);
			JGameElement*					GetParent		();
			void							AddChild		(JGameElement* child);
			JGameElement*					GetChild		(std::string appLink);// YOU CAN ONLY GET CHILD WITH APPLINK
			std::list<JGameElement*>		GetChilds		(std::string appLink);// YOU CAN ONLY GET CHILDS WITH APPLINK
			void							RemoveChild		(JGameElement* child);
			//DESING CHOICE: YOU ARE NOT ALLOWED TO MESS UP WITH CHILD WITHOUT YOUR POINTER REGISTERED PROPERLY
			//YOU CAN ADD AND REMOVE THEM, BUT THEN, IF YOU DON'T HAVE A POINTER AGAIN, THE SYSTEM WILL TAKE CARE

			virtual J::RENDER::JRenderableProperties GetAbsProperties() { return mAbsProperties; };
			virtual J::RENDER::JRenderableProperties GetRelProperties() { return mRelProperties; };

			virtual void			SetCamera(JGameCamera* camera);
			virtual JGameCamera*	GetCamera() { return mCamera; }

			virtual void						SetBodyType(J::PHYSICS::BodyType type) { mBodyType = type; }
			virtual J::PHYSICS::BodyType		GetBodyType() { return mBodyType; }
			virtual J::PHYSICS::JPhysicObject*	GetPhysicsObjects() { return mPhysicsObject; }
			
			virtual void	SetRelProperties(J::RENDER::JRenderableProperties& properties);

			virtual bool				IsInside(float x, float y);
		protected:
			virtual void	CalcAbsProperties();
			virtual void	ReadGeneralProperties(json properties);

			std::string		mAppLink;

			J::RENDER::JRenderableProperties mAbsProperties;
			J::RENDER::JRenderableProperties mRelProperties;
			J::RENDER::JRenderableProperties mOldAbsProperties;

			std::list<JGameElement*>	mChilds;
			JGameElement*				mParent;
			JGameCamera*				mCamera;

			J::PHYSICS::BodyType		mBodyType;
			J::PHYSICS::JPhysicObject*	mPhysicsObject;
		};
	}
}

#endif