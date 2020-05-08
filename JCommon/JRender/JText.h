#ifndef JTEXT
#define JTEXT

namespace J
{
	namespace RENDER
	{
		class JText : public ::J::BASE::JBase
		{
		public:
			JText();
			~JText();

			virtual void Init(const std::string fontpath, const std::string name, JRenderableProperties properties);
			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual JRenderableProperties	GetProperties() { return mRenderable->GetProperties(); }
			virtual void	SetProperties(JRenderableProperties properties) { mRenderable->SetProperties(properties); }

			virtual void				SetText(std::string text);
			virtual std::string 		GetText();
		protected:
			JRenderable *	mRenderable;
			std::string		mText;
		};
	}
}

#endif // !JTEXT
