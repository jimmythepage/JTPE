#ifndef JGAMESCREEN
#define JGAMESCREEN

/*JScreen legge dal json come montare la schermata e prepare i JGameModule da renderizzare.
Registrandoli si può tenere i puntatori ai JGameElement da usare.
Registra anche le appfunction su delle callback.
In generale è il cuore della schermata sia per la gui che per i livelli.*/

namespace J
{
	namespace GAME
	{
		class JGameScreen : public ::J::GAME::JGameElement
		{
		public:
			JGameScreen();
			~JGameScreen();

			virtual void Init(const json screenJson, const std::string name);
			virtual void Init(const std::string filepath, const std::string name);
			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			JGameModule*					GetGameModule(std::string appLink);//RETRIEVE ONLY THE FIRST AMONG ALL MODULES
			std::vector<JGameModule*>		GetGameModules(std::string appLink);//RETRIEVE EVERY MODULES WITH THE SAME APPLINK AMONG ALL MODULES

		protected:
			std::multimap<std::string, JGameModule*>		mRegisteredAppLinks;
		};
	}
}

#endif