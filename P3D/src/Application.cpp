#include "pch.h"

#include "glm/glm.hpp"

#include "Window.h"

#include "Cameras/FreeCamera.h"

int main(int argc, char** argv)
{
	Window window("P3D", 1280, 720);

	FreeCamera camera = FreeCamera(glm::radians(45.0f), 0.01f, 1000.0f, &window, glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, glm::radians(180.0f), 0.0f));

	while (!window.ShouldClose())
	{
		// Update

		// Draw

		// OpenGL things
		window.SwapBuffers();
		glfwPollEvents();
	}

	glfwTerminate();
	
	return 0;
}