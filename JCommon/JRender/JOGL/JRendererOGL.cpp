#include "JCommonPch.h"
#include "JRendererOGL.h"

using namespace J;
using namespace J::TASK;
using namespace J::RENDER;

JRendererOGL::JRendererOGL():mWindow(NULL), mMatrixID(0)
{
}
JRendererOGL::~JRendererOGL()
{
}
void JRendererOGL::Init(const std::string name)
{
	JRenderer::Init(name);
	// Initialise GLFW
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Open a window and create its OpenGL context
	mWindow = glfwCreateWindow(mScreenWidht, mScreenHeight, APP_NAME_STR, NULL, NULL);
	glfwMakeContextCurrent(mWindow);
	
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	glewInit();

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

	// Create and compile our GLSL program from the shaders
	InitShaders();
	LoadShaders();

	// Get a handle for our "MVP" uniform
	mMatrixID = glGetUniformLocation(mDefaultSpriteShader.programID, "MVP");

	glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

	// Camera matrix
	glm::mat4 View = glm::lookAt
	(
		glm::vec3(0, 0, 10), 
		glm::vec3(0, 0, 0), 
		glm::vec3(0, 1, 0)  
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	//Model = glm::translate(Model, glm::vec3(2.0f, 0.0f, 0.0f));
	//Model = glm::rotate(Model, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));
	//Model = glm::scale(Model,  glm::vec3(4.f, 4.f, 4.f));
	// Our ModelViewProjection : multiplication of our 3 matrices
	mMVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
}
void JRendererOGL::Clear()
{
	JRenderer::Clear();
	UnloadShaders();
	glfwTerminate();
}
void JRendererOGL::PreFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
void JRendererOGL::Update()
{
	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(mMatrixID, 1, GL_FALSE, &mMVP[0][0]);

	for (JRenderable* renderable : mRenderableToRender)
	{
		renderable->Update();
	}
}
void JRendererOGL::PostFrame()
{
	// Swap buffers
	glfwSwapBuffers(mWindow);
	glfwPollEvents();
	if (glfwWindowShouldClose(mWindow) != 0)
	{
		gJEngine.StopEngine();
	}
}
void JRendererOGL::InitShaders()
{
	mDefaultSpriteShader.name = "Shader_DefaultSprite.hlsl";
	mDefaultSpriteShader.type = Shader_DefaultSprite;
	mDefaultSpriteShader.vertexPath = "SimpleTransform.vertexshader";
	mDefaultSpriteShader.fragmentPath = "SingleColor.fragmentshader";
}
void JRendererOGL::LoadShaders()
{
	LOG_INFO(0, "Loading Shaders\n", 0);
	LoadShader(&mDefaultSpriteShader);
	LOG_INFO(0, "Shaders loaded\n", 0);
}
void JRendererOGL::UseShader(JShaderType type)
{
	JOGL_Shader* shader;
	switch (type)
	{
	case Shader_DefaultSprite:
		shader = &mDefaultSpriteShader;
		break;
	default:
		shader = NULL;
		break;
	}
	ASSERT(shader);
	// Use our shader
	glUseProgram(shader->programID);
}
void JRendererOGL::UnloadShaders()
{
	UnloadShader(&mDefaultSpriteShader);
	LOG_INFO(0, "Shaders unloaded\n", 0);
}
void JRendererOGL::LoadShader(JOGL_Shader* shader)
{
	std::string path = JDATA;
	path += JSHADERS;

	bool loaded = false;
	J::BASE::JFile file;
	file.Init((std::string)shader->name);

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string shaderPath = path + shader->vertexPath;
	std::string VertexShaderCode;

	//file.LoadAsync(shaderPath.c_str(), false);
	//while (!file.IsReadyToGet()) //JUST AN EXAMPLE, TO BE BOUND TO AN ACTUAL UPDATE WITH GFX FEEDBACK
	//{

	//}

	loaded = file.Load(shaderPath.c_str(), false);
	ASSERT(loaded);

	VertexShaderCode = file.GetStringData();
	file.Unload();

	// Read the Fragment Shader code from the file
	shaderPath = path + shader->fragmentPath;
	std::string FragmentShaderCode;
	loaded = file.Load(shaderPath.c_str(), false);
	ASSERT(loaded);
	FragmentShaderCode = file.GetStringData();
	file.Unload();

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	LOG_INFO(0, "Compiling Shader: %s\n", shader->vertexPath.c_str());
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) 
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		LOG_INFO(0, "Error compiling Shader: %s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	LOG_INFO(0, "Compiling Shader: %s\n", shader->fragmentPath.c_str());
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) 
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		LOG_INFO(0, "Error compiling Shader: %s\n", &FragmentShaderErrorMessage[0]);
	}


	// Link the program
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) 
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		LOG_INFO(0, "Program error: %s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	shader->programID= ProgramID;
}
void JRendererOGL::UnloadShader(JOGL_Shader * shader)
{
	glDeleteProgram(shader->programID);
}
