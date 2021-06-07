#pragma once

#include "Camera.h"

#include "glm/glm.hpp"

class OrbitCamera : public Camera
{
public:
	OrbitCamera(float fov, float nearPlane, float farPlane, Window* window, glm::vec3 lookAt = glm::vec3(0));
	~OrbitCamera() = default;

	virtual void Update(const float dt) override;

	virtual void OnEnable() override;

	virtual void OnDisable() override;

private:

	void GetInput(const float dt);
	
	void UpdateCameraVectors();

	const glm::vec3 kWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	glm::vec2 m_Rotation;
	float m_CameraDistance = 10.0f;
	
	glm::vec3 m_LookAt;

	glm::vec2 m_LastMousePos;

	const float kCameraRotationSpeed = 2.0f;
	const float kCameraMaxVerticalRotation = glm::radians(80.0f);
};
