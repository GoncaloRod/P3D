#include "pch.h"

#include "OrbitCamera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/scalar_constants.hpp>

#include "Window.h"

OrbitCamera::OrbitCamera(float fov, float nearPlane, float farPlane, Window* window, glm::vec3 lookAt /* = glm::vec3(0) */)
	: Camera(fov, nearPlane, farPlane, window, glm::vec3(0)), m_Rotation({ 0.0f, 0.0f }), m_LookAt(lookAt)
{
	double mouseX, mouseY;
	glfwGetCursorPos(m_pWindow->GetNativeWindow(), &mouseX, &mouseY);

	m_LastMousePos = glm::vec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
}

void OrbitCamera::Update(const float dt)
{
	GetInput(dt);
	
	UpdateCameraVectors();

	// WARNING: Up vector might not be correct
	m_ViewMat = glm::lookAt(m_Position, m_LookAt, kWorldUp);
}

void OrbitCamera::GetInput(const float dt)
{
	const auto pNativeWindow = m_pWindow->GetNativeWindow();

	double mouseX, mouseY;
	glfwGetCursorPos(pNativeWindow, &mouseX, &mouseY);

	double deltaX = mouseX - m_LastMousePos.x;
	double deltaY = mouseY - m_LastMousePos.y;

	m_Rotation.x += deltaX * kCameraRotationSpeed * dt;
	m_Rotation.y += deltaY * kCameraRotationSpeed * dt;

	if (m_Rotation.x > glm::pi<float>() * 2)
		m_Rotation.x -= glm::pi<float>() * 2;
	else if (m_Rotation.x < -glm::pi<float>() * 2)
		m_Rotation.x += glm::pi<float>() * 2;

	if (m_Rotation.y > kCameraMaxVerticalRotation)
		m_Rotation.y = kCameraMaxVerticalRotation;
	else if (m_Rotation.y < -kCameraMaxVerticalRotation)
		m_Rotation.y = -kCameraMaxVerticalRotation;

	m_LastMousePos.x = static_cast<float>(mouseX);
	m_LastMousePos.y = static_cast<float>(mouseY);
}

void OrbitCamera::UpdateCameraVectors()
{
	glm::vec4 base = { 0.0f, 0.0f, 1.0f, 0.0f };

	glm::mat4 rotation = glm::mat4(1.0f);

	rotation = glm::rotate(rotation, m_Rotation.y, glm::vec3(1, 0, 0));
	rotation = glm::rotate(rotation, m_Rotation.x, glm::vec3(0, 1, 0));
	
	base = base * rotation;

	m_Position = glm::vec3(base.x, base.y, base.z) * m_CameraDistance + m_LookAt;
}

void OrbitCamera::OnEnable()
{
	glfwSetInputMode(m_pWindow->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void OrbitCamera::OnDisable()
{
	glfwSetInputMode(m_pWindow->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
