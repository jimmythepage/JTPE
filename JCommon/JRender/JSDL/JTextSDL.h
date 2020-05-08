#ifndef JTEXTSDL
#define JTEXTSDL

struct FC_Font;

namespace J
{
	namespace RENDER
	{
		class JTextSDL : public ::J::RENDER::JRenderable
		{
		public:
			JTextSDL();
			~JTextSDL();

			virtual void Init(const std::string fontpath, const std::string name, JRenderableProperties properties);
			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			void SetText(std::string text);
		protected:
			std::string		mText;
			FC_Font *		mFont;
			SDL_Renderer*	mRenderer;
		};
	}
}

#endif
