/* Project Includes */
#include "Renderer.h"

/* System Includes */
#include <iostream>

void glClearError()
{
	while (glGetError() != GL_NO_ERROR)
	{
	}
}

bool glLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		const char* glErrorType = NULL;

		switch (error)
		{
		default:
			glErrorType = "UNDEFINED";
		case GL_INVALID_ENUM:
			glErrorType = "GL_INVALID_ENUM";
		case GL_INVALID_VALUE:
			glErrorType = "GL_INVALID_VALUE";
		case GL_INVALID_OPERATION:
			glErrorType = "GL_INVALID_OPERATION";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			glErrorType = "GL_INVALID_FRAMEBUFFER_OPERATION";
		case GL_OUT_OF_MEMORY:
			glErrorType = "GL_OUT_OF_MEMORY";
		case GL_STACK_OVERFLOW:
			glErrorType = "GL_STACK_OVERFLOW";
		case GL_STACK_UNDERFLOW:
			glErrorType = "GL_STACK_UNDERFLOW";
		}

		std::cout << "[OpenGL Error] ( " << error << " )" << glErrorType << " | function: " << function << " | file: " << file << " | line: " << line << std::endl;
		return false;
	}

	return true;
}

void Renderer::Clear() const
{
	glCall(glClearColor(1.0, 1.0, 1.0, 1.0));
	glCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();

	va.Bind();
	ib.Bind();

	glCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, NULL));
}