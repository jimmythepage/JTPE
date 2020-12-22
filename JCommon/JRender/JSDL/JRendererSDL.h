#ifndef JRENDERERSDL
#define JRENDERERSDL


namespace J
{
	namespace RENDER
	{
		class JRendererSDL : public ::J::RENDER::JRenderer
		{
		public:
			JRendererSDL();
			~JRendererSDL();

			void Init(const std::string name, const std::string appName);
			void Clear(); 
			void PreFrame();
			void Update();
			void PostFrame();
			void Activate();
			void Deactivate();

			SDL_Window*		GetWindow()				{ return mWindow; }
			SDL_Renderer*	GetRenderer()			{ return mRenderer; }
		private:
			SDL_Window *		mWindow;
			SDL_Renderer *		mRenderer;
			SDL_Event			mEvent;

      bool MakeWindowTransparent(SDL_Window* window, COLORREF colorKey);
		};
	}
}

#endif // !JRENDERERSDL
