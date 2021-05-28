#pragma once

#include "Camera.h"

class FreeCamera : public Camera
{
public:

	FreeCamera(float fov, float nearPlane, float farPlane, Window* window, glm::vec3 position, glm::vec3 rotation);
	~FreeCamera() = default;

	virtual void Update(const float dt) override;

private:

	void UpdateCameraVectors();

	const glm::vec3 kWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	glm::vec3 m_Rotation;
	glm::vec3 m_Forward, m_Up, m_Right;

	glm::vec2 m_LastMousePos;

	const float kCameraMovementSpeed = 2.0f;
	const float kCameraRotationSpeed = 2.0f;
};
