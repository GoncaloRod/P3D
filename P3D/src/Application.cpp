#include "pch.h"

#include "Window.h"

int main(int argc, char** argv)
{
	Window window("P3D", 1280, 720);

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