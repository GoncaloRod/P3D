#include "pch.h"

#include "Camera.h"

#include "Window.h"
#include "GLFW/glfw3.h"

#include "glm/ext/matrix_clip_space.hpp"

Camera::Camera(float fov, float nearPlane, float farPlane, Window* pWindow)
	: m_pWindow(pWindow), m_FOV(fov), m_NearPlane(nearPlane), m_FarPlane(farPlane)
{
	int32_t width, height;

	glfwGetWindowSize(m_pWindow->GetNativeWindow(), &width, &height);

	Resize(width, height);
	m_ViewMat = glm::mat4x4();
}
void Camera::Resize(int width, int height)
{
	const float kRatio = static_cast<float>(width) / height;
	
	m_ProjectionMat = glm::perspective(m_FOV, kRatio, m_NearPlane, m_FarPlane);
}
