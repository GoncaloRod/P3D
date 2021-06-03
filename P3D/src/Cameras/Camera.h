#pragma once

#include "glm/mat4x4.hpp"

class Window;
struct GLFWwindow;

class Camera
{
public:

    Camera(float fov, float nearPlane, float farPlane, Window* pWindow, glm::vec3 position);
	~Camera() = default;

    /**
     * Update camera.
     *
     * @param dt Time passed since last frame.
     */
    virtual void Update(const float dt) {};

    /**
     * Get camera's projection matrix.
     *
     * @return Projection matrix.
     */
    inline glm::mat4x4 GetProjectionMatrix() const
    {
        return m_ProjectionMat;
    }

    /**
     * Get camera's view matrix.
     *
     * @return View matrix.
     */
    inline glm::mat4x4 GetViewMatrix() const
    {
        return m_ViewMat;
    }

	/**
	 * Get camera's position.
	 *
	 * @return 3 dimensional vector with camera's position.
	 */
	constexpr glm::vec3 GetPosition() const
    {
    	return m_Position;
    }

	/**
	 * Resize camera projection matrix.
	 *
	 * @param width New window width.
	 * @param height New window height.
	 */
	inline void Resize(int width, int height);

	/**
	 * Function called when camera is enabled.
	 * Each type of camera have specific behaviours.
	 */
	virtual void OnEnable();

	/**
	 * Function called when camera is enabled.
	 * Each type of camera have specific behaviours.
	 */
	virtual void OnDisable();

protected:

    glm::mat4x4 m_ViewMat;
    glm::mat4x4 m_ProjectionMat;

	glm::vec3 m_Position;

    Window* m_pWindow;

    float m_FOV;
    float m_NearPlane, m_FarPlane;
};
