#ifndef JRENDERERABLEOGL
#define JRENDERERABLEOGL

namespace J
{
	namespace RENDER
	{
		class J2DQuadOGL : public ::J::RENDER::JRenderable
		{
		public:
			J2DQuadOGL();
			~J2DQuadOGL();

			virtual void Init(const std::string name);
			virtual void Clear();
			virtual void Update();
			virtual void Activate();
			virtual void Deactivate();
		protected:
			GLuint					mVertexbuffer;
			GLuint					mVertexArrayID;
		};
	}
}

#endif // !JRENDERERABLEOGL
