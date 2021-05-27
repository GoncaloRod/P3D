#include "pch.h"

#include "glm/glm.hpp"

#include "Window.h"

#include "Cameras/FreeCamera.h"

int main(int argc, char** argv)
{
	double lastFrame, currentFrame, deltaTime;

	// Set up window
	Window window("P3D", 1280, 720);

	currentFrame = lastFrame = glfwGetTime();

	// Setup camera
	FreeCamera camera = FreeCamera(glm::radians(45.0f), 0.01f, 1000.0f, &window, glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, glm::radians(180.0f), 0.0f));

	glm::vec3 ambientColor = glm::vec3(0.1f, 0.1f, 0.1f);
	
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

		// OpenGL things
		window.SwapBuffers();
		glfwPollEvents();
	}

	glfwTerminate();
	
	return 0;
}