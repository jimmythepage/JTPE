#ifndef JGAMETEXT
#define JGAMETEXT


namespace J
{
	namespace GAME
	{
		class JGameText : public ::J::GAME::JGameElement
		{
		public:
			JGameText();
			~JGameText();

			virtual void Init(const std::string name, std::string applink, json text);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual void SetText(std::string text);
		protected:
			J::RENDER::JText* mText;
		};
	}
}

#endif