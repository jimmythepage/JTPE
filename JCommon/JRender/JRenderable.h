#ifndef JRENDERABLE
#define JRENDERABLE

namespace J
{
	namespace RENDER
	{
		enum FontStyle
		{
			STYLE_NORMAL = 0,
			STYLE_BOLD,
			STYLE_ITALIC,
			STYLE_UNDERLINE,
			STYLE_STRIKETHROUGH
		};
		enum TextAlign
		{
			ALIGN_MIDDLE = 0,
			ALIGN_LEFT,
			ALIGN_RIGHT
		};
		struct JRenderableProperties
		{
			JVec2				Position;
			JVec2				Origin;
			JVec2				Size;
			JVec2				Scale;
			int					Z;
			int					ZAdd;
			float				Rot;
			float				R, G, B, A;
			bool				Visible;
			//Text params
			FontStyle			FontStyle;
			TextAlign			TextAlign;
			int					FontSize;

			JRenderableProperties() :
				Position(0.f,0.f),Origin(0.f,0.f),Size(100.f,100.f),Scale(1.f,1.f),Z(0), ZAdd(0),
				Rot(0.f), FontSize(20),R(1.f),G(1.f),B(1.f),A(1.f), Visible(true),
				FontStyle(STYLE_NORMAL), TextAlign(ALIGN_MIDDLE)
			{
			}
		};

		class JRenderable : public ::J::BASE::JBase
		{
		public:
			JRenderable();
			~JRenderable();

			virtual void Init(const std::string filepath, const std::string name, JRenderableProperties properties);
			virtual void Init(const std::string filepath, const std::string name, JRenderableProperties properties, JRenderableProperties clip);
			virtual void Init(const std::string filepath, const std::string name);
			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();

			virtual JRenderableProperties	GetProperties()					{ return mProperties;			}
			virtual void	SetProperties(JRenderableProperties properties)	{ mProperties =properties;		}
			virtual JRenderableProperties	GetSpriteClip()					{ return mSpriteClip;	}
			virtual void	SetSpriteClip(JRenderableProperties rect)		{ mSpriteClip = rect;	}
		protected:
			JRenderableProperties				mProperties;
			JRenderableProperties				mSpriteClip;
		};
	}
}

#endif
