#include "pch.h"

#include "FreeCamera.h"

#include "Window.h"
#include "GLFW/glfw3.h"
#include "glm/trigonometric.hpp"
#include "glm/ext/matrix_transform.hpp"

FreeCamera::FreeCamera(float fov, float nearPlane, float farPlane, Window* window, glm::vec3 position, glm::vec3 rotation)
	: Camera(fov, nearPlane, farPlane, window, position), m_Rotation(rotation)
{
	double mouseX, mouseY;
	glfwGetCursorPos(m_pWindow->GetNativeWindow(), &mouseX, &mouseY);

	m_LastMousePos = glm::vec2(static_cast<float>(mouseX), static_cast<float>(mouseY));

	UpdateCameraVectors();

	m_ViewMat = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

void FreeCamera::Update(const float dt)
{
	const auto pNativeWindow = m_pWindow->GetNativeWindow();

	double mouseX, mouseY;
	glfwGetCursorPos(pNativeWindow, &mouseX, &mouseY);
	
	if (glfwGetMouseButton(pNativeWindow, GLFW_MOUSE_BUTTON_RIGHT))
	{
		auto movementInput = glm::vec3(0);

		if (glfwGetKey(pNativeWindow, GLFW_KEY_W))
			movementInput.z += 1;
		if (glfwGetKey(pNativeWindow, GLFW_KEY_S))
			movementInput.z -= 1;

		if (glfwGetKey(pNativeWindow, GLFW_KEY_A))
			movementInput.x -= 1;
		if (glfwGetKey(pNativeWindow, GLFW_KEY_D))
			movementInput.x += 1;

		if (glfwGetKey(pNativeWindow, GLFW_KEY_E))
			movementInput.y += 1;
		if (glfwGetKey(pNativeWindow, GLFW_KEY_Q))
			movementInput.y -= 1;

		m_Position += (m_Forward * movementInput.z + m_Right * movementInput.x + glm::vec3(0, 1, 0) * movementInput.y) * kCameraMovementSpeed * dt;

		m_Rotation -= glm::vec3(mouseY - m_LastMousePos.y, mouseX - m_LastMousePos.x, 0.0f) * kCameraRotationSpeed * dt;

		UpdateCameraVectors();

		m_ViewMat = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
	}

	m_LastMousePos.x = static_cast<float>(mouseX);
	m_LastMousePos.y = static_cast<float>(mouseY);
}

void FreeCamera::UpdateCameraVectors()
{
	m_Forward.x = glm::sin(m_Rotation.y) * glm::cos(m_Rotation.x);
	m_Forward.y = glm::sin(m_Rotation.x);
	m_Forward.z = glm::cos(m_Rotation.y) * glm::cos(m_Rotation.x);

	m_Forward = glm::normalize(m_Forward);
	m_Right = glm::normalize(glm::cross(m_Forward, kWorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Forward));
}
