#include "Object.h"

Object::Object(GeometricShape shape, Object::obj object)
{
	switch (shape)
	{
	case Object::Rectangle:

		/*
		vArray.push_back(object.size.x + object.position.x);
		vArray.push_back(object.size.y + object.position.y);
		vArray.push_back(1.0f);
		vArray.push_back(1.0f);

		vArray.push_back(object.size.x + (object.position.x - (object.position.x * 2)));
		vArray.push_back(object.size.y + (object.position.y - (object.position.y * 2)));
		vArray.push_back(0.0f);
		vArray.push_back(0.0f);

		vArray.push_back((object.size.x - (object.position.x * 2)) + (object.position.x - (object.position.x * 2)));
		vArray.push_back((object.size.y - (object.position.y * 2)) + (object.position.y - (object.position.y * 2)));
		vArray.push_back()

		vArray.push_back((object.size.x - (object.position.x * 2)) + object.position.x);
		vArray.push_back((object.size.y - (object.position.y * 2)) + object.position.y);

		iArray.push_back();*/

		float vVecArray[] = 
		{
		//	  X-Pos   Y-Pos   UV-X   UV-Y
			 -object.size.x + -object.position.x, -object.size.y + -object.position.y,  0.0f,  0.0f, // 0
			  object.size.x + object.position.x,  -object.size.y + -object.position.y,  1.0f,  0.0f, // 1
			  object.size.x + object.position.x,   object.size.y + object.position.y,   1.0f,  1.0f, // 2
			 -object.size.x + -object.position.x,  object.size.y + object.position.y,  0.0f,  1.0f  // 3
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		/* Buffer Rectangle Data */
		unsigned int vao;
		glCall(glGenVertexArrays(1, &vao));
		glCall(glBindVertexArray(vao));

		// Vertex and Buffer Initialization
		VertexArray va;
		VertexBuffer vb(vVecArray, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);
		break;
	case Object::Triangle:
		break;
	}
}

Object::~Object()
{
	delete this;
}
