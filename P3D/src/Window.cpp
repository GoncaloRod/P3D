#include "pch.h"

#include "Window.h"

Window::Window(const std::string& title, uint32_t width, uint32_t height, bool vsync /*= false*/)
    : m_Title(title), m_Width(width), m_Height(height), m_pWindow(nullptr), m_VSync(vsync)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef MAC
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	m_pWindow = glfwCreateWindow(1280, 720, m_Title.c_str(), nullptr, nullptr);

	if (m_pWindow == nullptr)
	{
		std::cout << "Failed to initialize window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_pWindow);

	glfwSwapInterval(m_VSync ? 1 : 0);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	glViewport(0, 0, 1280, 720);

	glfwSetFramebufferSizeCallback(m_pWindow, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

	// Enable Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable Depth Test
	glEnable(GL_DEPTH_TEST);

	// Enable back-face culling
	glEnable(GL_CULL_FACE);

	// Enable MSAA
	glEnable(GL_MULTISAMPLE);

	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(m_pWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

Window::~Window()
{
	glfwTerminate();
}
