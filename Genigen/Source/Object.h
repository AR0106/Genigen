#pragma once

#include <vector>

#include "Shader.h"
#include "Renderer.h"

#include "glm/glm.hpp"

class Object
{
public:
	enum GeometricShape
	{
		Rectangle,
		Triangle
	};

	struct obj
	{
		Shader shader;
		glm::vec3 position;
		glm::vec3 size;
		glm::vec3 rotation;
	};
	
	Object(GeometricShape shape, Object::obj object);
	~Object();

private:
	std::vector<unsigned int> iArray;
	std::vector<float> vArray;
};

