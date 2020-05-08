#include "JCommonPch.h"
#include "J2DQuadOGL.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


using namespace J;
using namespace J::TASK;
using namespace J::RENDER;

J2DQuadOGL::J2DQuadOGL()
{
}
J2DQuadOGL::~J2DQuadOGL()
{
}
void J2DQuadOGL::Init(const std::string name)
{
	JRenderable::Init(name);
	glGenVertexArrays(1, &mVertexArrayID);
	glBindVertexArray(mVertexArrayID);

	glGenBuffers(1, &mVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexbuffer);
	//glBufferData(GL_ARRAY_BUFFER, mModel.mVertexBufferData.size()*sizeof(float), mModel.mVertexBufferData.data(), GL_STATIC_DRAW);
}
void J2DQuadOGL::Clear()
{
	JRenderable::Clear();
	glDeleteBuffers(1, &mVertexbuffer);
	glDeleteVertexArrays(1, &mVertexArrayID);
}
void J2DQuadOGL::Activate()
{
	JRenderable::Activate();
}
void J2DQuadOGL::Update()
{
	JRenderable::Update();
	// 1rst attribute buffer : verticesù
	gJRenderManager.GetRenderer()->UseShader(JShaderType::Shader_DefaultSprite);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexbuffer);
	glVertexAttribPointer(
		0,													// attribute. No particular reason for 0, but must match the layout in the shader.
		4,													// size
		GL_FLOAT,											// type
		GL_FALSE,											// normalized?
		0,													// stride
		(void*)0											// array buffer offset
	);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableVertexAttribArray(0);
}
void J2DQuadOGL::Deactivate()
{
	JRenderable::Deactivate();
}