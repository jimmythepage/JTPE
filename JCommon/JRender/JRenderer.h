#ifndef JRENDERER
#define JRENDERER

namespace J
{
	namespace RENDER
	{
		class JRenderer : public ::J::BASE::JBase
		{
		public:
			JRenderer();
			~JRenderer();

			virtual void Init(const std::string name,const std::string appName);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual void PreFrame();
			virtual void PostFrame();

			virtual void UseShader(JShaderType type);

			virtual void AddRenderable(JRenderable* renderable);
			virtual void RemoveRenderable(JRenderable* renderable);
			virtual void SortRenderables();

			const unsigned int ScreenWidth() { return mScreenWidth; }
			const unsigned int ScreenHeight() { return mScreenHeight; }
		protected:
			virtual void InitShaders();
			virtual void LoadShaders();
			virtual void UnloadShaders();

			std::list<JRenderable*> mRenderableToRender;

			unsigned int mScreenWidth, mScreenHeight;
			unsigned int mLogicalWidth, mLogicalHeight;
			bool		 mFullScreen;
		};
	}
}

#endif // !JRENDERER
