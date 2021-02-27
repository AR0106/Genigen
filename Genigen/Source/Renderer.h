#pragma once

/* Dependency Includes */
#include "../Dependencies/GLEW/include/glew.h"

/* Project Includes */
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "glm/vec4.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();
#define glCall(x) glClearError();\
	x;\
	ASSERT(glLogCall(#x, __FILE__, __LINE__));

#define LIGHTGRAY  glm::vec4{ 0.702f, 0.702f, 0.702f, 1.0f }   // Light Gray
#define GRAY       glm::vec4{ 0.468f, 0.468f, 0.468f, 1.0f }   // Gray
#define DARKGRAY   glm::vec4{ 0.149f, 0.149f, 0.149f, 1.0f }   // Dark Gray
#define YELLOW     glm::vec4{ 0.957f, 0.915f, 0.0f,   1.0f }   // Yellow
#define GOLD       glm::vec4{ 1.0f,   0.681f, 0.0f,   1.0f }   // Gold
#define ORANGE     glm::vec4{ 1.0f,   0.298f, 0.0f,   1.0f }   // Orange
#define PINK       glm::vec4{ 1.0f,   0.404f, 0.638f, 1.0f }   // Pink
#define RED        glm::vec4{ 0.936f, 0.0f,   0.213f, 1.0f }   // Red
#define MAROON     glm::vec4{ 0.468f, 0.106f, 0.0f,   1.0f }   // Maroon
#define GREEN      glm::vec4{ 0.0f,   0.532f, 0.149f, 1.0f }   // Green
#define LIME       glm::vec4{ 0.0f,   0.638f, 0.149f, 1.0f }   // Lime
#define DARKGREEN  glm::vec4{ 0.0f,   0.319f, 0.106f, 1.0f }   // Dark Green
#define SKYBLUE    glm::vec4{ 0.240f, 0.723f, 1.0f,   1.0f }   // Sky Blue
#define BLUE       glm::vec4{ 0.0f,   0.426f, 0.936f, 1.0f }   // Blue
#define DARKBLUE   glm::vec4{ 0.0f,   0.170f, 0.362f, 1.0f }   // Dark Blue
#define PURPLE     glm::vec4{ 0.404f, 0.238f, 1.0f,   1.0f }   // Purple
#define VIOLET     glm::vec4{ 0.191f, 0.277f, 0.872f, 1.0f }   // Violet
#define DARKPURPLE glm::vec4{ 0.447f, 0.085f, 0.489f, 1.0f }   // Dark Purple
#define BEIGE      glm::vec4{ 0.809f, 0.617f, 0.574f, 1.0f }   // Beige
#define BROWN      glm::vec4{ 0.511f, 0.362f, 0.277f, 1.0f }   // Brown
#define DARKBROWN  glm::vec4{ 0.298f, 0.191f, 0.218f, 1.0f }      // Dark Brown

#define WHITE      glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f}   // White
#define BLACK      glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f }  // Black
#define BLANK      glm::vec4{ 0.0f, 0.0f, 0.0f, 0.0f }  // Blank (Transparent)
#define MAGENTA    glm::vec4{ 1.0f, 0.0f, 1.0f, 1.0f }  // Magenta

void glClearError();

bool glLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};