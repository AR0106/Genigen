#include "Object.h"

Object::Object(GeometricShape shape, Object::obj object)
{
	switch (shape)
	{
	case Object::Rectangle:

		vArray.push_back(object.size.x + object.position.x);
		vArray.push_back(object.size.x + (object.position.x - (object.position.x * 2)));
		vArray.push_back((object.size.x - (object.position.x * 2)) + (object.position.x - (object.position.x * 2)));
		vArray.push_back((object.size.x - (object.position.x * 2)) + object.position.x);

		iArray.push_back()
		break;
	case Object::Triangle:
		break;
	}

	/* Buffer Rectangle Data */
	unsigned int vao;
	glCall(glGenVertexArrays(1, &vao));
	glCall(glBindVertexArray(vao));

	// Vertex and Buffer Initialization
	VertexArray va;
	VertexBuffer vb(vArray, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(iArray, 6);
}

Object::~Object()
{
	delete this;
}
