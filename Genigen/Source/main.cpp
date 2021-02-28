/* Dependency Includes */
#include "../Dependencies/GLEW/include/glew.h"
#include "../Dependencies/GLFW/include/glfw3.h"
#include "../Dependencies/Box2d/include/box2d.h"

/* System Includes */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/* Project Includes */
#include "main.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Audio.h"
#include "../World.h"

/* Vendor Includes */
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "Geniren", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Verifies GLEW
	if (glewInit() != GLEW_OK)
		std::cout << "GLEW NOT OK" << std::endl;

	// Prints OpenGL Version ( Should Print 4.3.0 )
	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		// Vertex Buffer Values
		float xyCrossPoints[] =
		{
		//	  X-Pos   Y-Pos   UV-X   UV-Y
			 -25.5f, -50.0f,  0.0f,  0.0f, // 0
			  25.5f, -50.0f,  1.0f,  0.0f, // 1
			  25.5f,  50.0f,  1.0f,  1.0f, // 2
			 -25.5f,  50.0f,  0.0f,  1.0f  // 3
		};

		// Index Buffer Values
		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		// Enables Alpha Channels For Shaders
		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		/* Buffer Rectangle Data */
		unsigned int vao;
		glCall(glGenVertexArrays(1, &vao));
		glCall(glBindVertexArray(vao));

		// Vertex and Buffer Initialization
		VertexArray va;
		VertexBuffer vb(xyCrossPoints, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		/*
			Window Has 16:9 Aspect Ratio
			|-4.0f * 4.0f| = 16.0f
			|-3.0f * 3.0f| = 9.0f
		*/

		/* Sets New Renderering Boundries */
		/* From 4 Quadrant Percentage to Pixels */
		glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		/*glm::mat4 perspectiveProjection = glm::infinitePerspective(45.0f, (float)1280 / (float)720, 1.0f);
		glm::mat4 perspectiveView = glm::lookAt
		(
			glm::vec3(0, 0, 3),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
		);*/

		/* Shaders */
		Shader shader("Resources/Shaders/Basic.shader");
		shader.Bind();

		//Texture texture("Resources/Textures/logoMain.png");
		//texture.Bind();
		//shader.SetUniform1i("u_Texture", 0);

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		Renderer renderer;
		Audio audio;

		// Settings
		

		// World Initialization


		// UI Initialziation
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsLight();

		// Object Variable Intialization
		glm::vec3 translationA(200, 200, 1);
		glm::vec3 translationB(400, 200, 1);

		glm::vec4 colorA = DARKPURPLE;
		glm::vec4 colorB = BLUE;

		// Sound Initialization
		audio.InitAudio();

		FMOD::Sound* sound = audio.CreateSound("Resources/Sounds/sound1.mp3", FMOD_2D, 0);

		// Physics Setup and Initialization
		b2Vec2 gravity(0.0f, -1.0f);
		b2World world(gravity);

		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, -10.0f);

		b2Body* groundBody = world.CreateBody(&groundBodyDef);

		b2PolygonShape groundBox;
		groundBox.SetAsBox(500000.0f, 10.0f);

		groundBody->CreateFixture(&groundBox, 0.0f);

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(translationA.x, translationA.y);
		b2Body* body = world.CreateBody(&bodyDef);

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(1.0f, 1.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

		body->CreateFixture(&fixtureDef);

		float timeStep = 1.0f / 60.0f;

		int32 velocityIterations = 6;
		int32 positionIterations = 2;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			ImGui_ImplGlfwGL3_NewFrame();

			world.Step(timeStep, velocityIterations, positionIterations);
			b2Vec2 position = body->GetPosition();
			float angle = body->GetAngle();
			//printf("%4.2f %4.2f %4.2f\n", position.x, position.y + 50.0f, angle);

			{
				translationA = glm::vec3(position.x, position.y + 50.0f, 1);
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
				glm::mat4 mvp = projection * view * model;
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", mvp);
				shader.SetUniform4f("u_Color", colorA);
				renderer.Draw(va, ib, shader);
			}

			shader.Bind();

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
				glm::mat4 mvp = projection * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);
				shader.SetUniform4f("u_Color", colorB);
				renderer.Draw(va, ib, shader);
			}

			{
				ImGui::SliderFloat2("TranslationA", &position.x, 0.0f, 1280.0f);
				ImGui::SliderFloat2("TranslationB", &translationB.x, 0.0f, 1280.0f);
				ImGui::SliderFloat4("ColorA", &colorA.x, 0.0f, 1.0f);
				ImGui::SliderFloat4("ColorB", &colorB.x, 0.0f, 1.0f);
				if (ImGui::Button("Play Sound", ImVec2(150, 25)))
				{
					audio.PlaySound(sound, nullptr, 0);
				}
				ImGui::Text("Average %3.f ms/frame (%.1f FPS", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}