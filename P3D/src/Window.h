#pragma once

#include <GLFW/glfw3.h>

class Window
{
public:

	Window(const std::string& title, uint32_t width, uint32_t height, bool vsync = false);
	~Window();

	/**
	 * Get window size in pixels.
	 *
	 * @return Pair o unsigned integers.
	 */
	constexpr std::pair<uint32_t, uint32_t> GetWindowSize() const
	{
		return { m_Width, m_Height };
	}

	/**
	 * Get reference to the native window.
	 *
	 * @return Pointer to a GLFWwindow.
	 */
	constexpr GLFWwindow* GetNativeWindow() const
	{
		return m_pWindow;
	}

	inline bool ShouldClose() const
	{
		return glfwWindowShouldClose(m_pWindow);
	}

	inline void SwapBuffers() const
	{
		glfwSwapBuffers(m_pWindow);
	}
	 
private:

	GLFWwindow* m_pWindow;
	uint32_t m_Width, m_Height;
	std::string m_Title;
	bool m_VSync;
};
