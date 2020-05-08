#ifndef JTEXTUREMANAGERSDL
#define JTEXTUREMANAGERSDL


namespace J
{
	namespace RENDER
	{
		class JTextureManagerSDL : public ::J::BASE::JBase
		{
		public:
			JTextureManagerSDL();
			~JTextureManagerSDL();

			void Init(std::string name);
			void Clear();

			//##=--------------------------------------------
			//## Singleton
			//##=--------------------------------------------
			static JTextureManagerSDL & GetSingleton();

			
			SDL_Surface * GetOrLoadTexture(std::string path);

		protected:
			std::map<std::string, SDL_Surface *> mTextures;
		};
	#define gJTextureManagerSDL ::J::RENDER::JTextureManagerSDL::GetSingleton()
	}
}

#endif
