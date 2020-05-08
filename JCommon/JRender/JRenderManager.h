#ifndef JRENDERMANAGER
#define JRENDERMANAGER

namespace J
{
	namespace RENDER
	{
		class JRenderManager : public ::J::BASE::JBase
		{
		public:
			JRenderManager();
			~JRenderManager();

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static JRenderManager & GetSingleton();

			void Init(const std::string name, const std::string appName);
			void Clear();
			void Update();
			void Activate();
			void Deactivate();

			JRenderer* const  GetRenderer() { return mJRenderer; }
		private:
			JRenderer *			mJRenderer;
		};
#define gJRenderManager ::J::RENDER::JRenderManager::GetSingleton()
	}
}

#endif // !JRENDERMANAGER
