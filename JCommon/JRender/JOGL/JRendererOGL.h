#ifndef JRENDEREROGL
#define JRENDEREROGL

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace J
{
	namespace RENDER
	{
		struct JOGL_Shader
		{
			unsigned int		programID;		// the pointer to the vertex shader
			JShaderType			type;
			std::string			name;
			std::string			vertexPath;
			std::string			fragmentPath;
		};
		class JRendererOGL : public ::J::RENDER::JRenderer
		{
		public:
			JRendererOGL();
			~JRendererOGL();

			void Init(const std::string name);
			void Clear(); 
			void PreFrame();
			void Update();
			void PostFrame();

			void UseShader(JShaderType type);
		protected:
			virtual void InitShaders();
			virtual void LoadShaders();
			virtual void UnloadShaders();

		private:
			void LoadShader(JOGL_Shader* shader);
			void UnloadShader(JOGL_Shader* shader);


			GLFWwindow*				mWindow;
			JOGL_Shader				mDefaultSpriteShader;
			glm::mat4				mMVP;
			GLuint					mMatrixID;
		};
	}
}

#endif // !JRENDEREROGL
