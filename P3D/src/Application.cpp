#include "pch.h"

#include "glm/glm.hpp"

#include "Window.h"

#include "Cameras/FreeCamera.h"
#include "Graphics/Model.h"
#include "Renderer/Shader.h"

int main(int argc, char** argv)
{
	double lastFrame, currentFrame, deltaTime;

	// Set up window
	Window window("P3D", 1280, 720);

	currentFrame = lastFrame = glfwGetTime();

	// Setup camera
	FreeCamera camera = FreeCamera(glm::radians(45.0f), 0.01f, 1000.0f, &window, glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, glm::radians(180.0f), 0.0f));

	// Load assets
	auto shader = std::make_shared<Shader>("assets/shaders/Phong.vert", "assets/shaders/Phong.frag");

	/*
	auto rocket = Model::LoadFromObj(shader, "assets/models/TheRocket/TheRocket.obj");
	if (rocket == nullptr)
	{
		std::cout << "Failed to load model" << std::endl;
		return 0;
	}
	*/

	auto ironMan = Model::LoadFromObj(shader, "assets/models/Iron_Man/Iron_Man.obj");
	if (ironMan == nullptr)
	{
		std::cout << "Failed to load model" << std::endl;
		return 0;
	}
	
	glm::vec3 ambientColor = glm::vec3(0.1f, 0.1f, 0.1f);

	glm::vec3 directionLightPos = glm::vec3(10.0f, 10.0f, 10.0f);
	
	while (!window.ShouldClose())
	{
		// Update render stats
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// Update
		camera.Update(static_cast<float>(deltaTime));

		// Draw
		glClearColor(ambientColor.r, ambientColor.g, ambientColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->Bind();

		shader->SetMat4("u_View", camera.GetViewMatrix());
		shader->SetMat4("u_Projection", camera.GetProjectionMatrix());

		shader->SetVec3("u_AmbientColor", ambientColor);

		shader->SetVec3("u_DirectionalLightPosition", directionLightPos);
		shader->SetVec3("u_DirectionalLightColor", glm::vec3(1.0f));

		shader->SetVec3("u_CameraPos", camera.GetPosition());

		//rocket->Draw();
		ironMan->Draw();

		// OpenGL things
		window.SwapBuffers();
		glfwPollEvents();
	}

	glfwTerminate();
	
	return 0;
}
