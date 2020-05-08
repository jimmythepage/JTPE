#ifndef JSPRITESDL
#define JSPRITESDL

namespace J
{
	namespace RENDER
	{
		class JSpriteSDL : public ::J::RENDER::JRenderable
		{
		public:
			JSpriteSDL();
			~JSpriteSDL();

			virtual void Init(const std::string filepath,const std::string name);
			virtual void Init(const std::string filepath, const std::string name, JRenderableProperties properties);
			virtual void Init(const std::string filepath, const std::string name, JRenderableProperties properties, JRenderableProperties clip);
			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

		protected:
			SDL_Surface *	mImage;
			SDL_Texture *	mTexture;
			SDL_Renderer*	mRenderer;
		};
	}
}

#endif // !JSPRITESDL
