#ifndef		JGAMEMODULE
#define		JGAMEMODULE

/*JGameModule genera dai un json specifico per JGameModule la lista di
JGameSprite, JGameButton, JGameText ecc da renderizzare e ne chiama i metodi.
Inoltre ritorna puntatori e appfunction se richiesto.
JGameModule può essere chiamato da JGameScreen ma può anche essere renderizzato da solo.*/

namespace J
{
	namespace GAME
	{
		class JGameModule : public ::J::GAME::JGameElement
		{
		public:
			JGameModule();
			~JGameModule();

			virtual void Init(const std::string filepath, J::RENDER::JRenderableProperties properties, json extraParams);
			virtual void Init(const std::string filepath);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			JGameElement*				GetElement(std::string appLink);//RETRIEVE ONLY THE FIRST
			std::vector<JGameElement*>	GetElements(std::string appLink);//RETRIEVE EVERY JGUIELEMENTS WITH THE SAME APPLINK
		protected:
			JGameElement * LoadElement(json gameElement,JGameElement* parent);
			std::multimap<std::string, JGameElement*> mRegisteredAppLinks;
		};
	}
}

#endif // ! JGAMEMODULE
