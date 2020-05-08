#ifndef J2DQUAD
#define J2DQUAD

namespace J
{
	namespace RENDER
	{
		class J2DQuad : public ::J::BASE::JBase
		{
		public:
			J2DQuad();
			~J2DQuad();

			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();
		protected:
			JRenderable*		mRenderable;
		};
	}
}

#endif //
