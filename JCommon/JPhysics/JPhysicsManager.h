#ifndef JPHYSICSMANAGER
#define JPHYSICSMANAGER

namespace J
{
	namespace PHYSICS
	{
		class JPhysicsManager : public ::J::BASE::JBase
		{
		public:
			JPhysicsManager();
			~JPhysicsManager();

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static JPhysicsManager & GetSingleton();

			void Init(const std::string name);
			void Clear();
			void Update();
			void Activate();
			void Deactivate();

			JPhysics* const  GetPhysics() { return mPhysics; }
		private:
			JPhysics *			mPhysics;
		};
#define gJPhysicsManager ::J::PHYSICS::JPhysicsManager::GetSingleton()
	}
}

#endif // !JPHYSICSMANAGER
