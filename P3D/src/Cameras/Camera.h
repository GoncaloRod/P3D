#pragma once

#include "glm/mat4x4.hpp"

class Window;
struct GLFWwindow;

class Camera
{
public:

    Camera(float fov, float nearPlane, float farPlane, Window* pWindow);
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
	 * Resize camera projection matrix.
	 *
	 * @param width New window width.
	 * @param height New window height.
	 */
	inline void Resize(int width, int height);

protected:

    glm::mat4x4 m_ViewMat;
    glm::mat4x4 m_ProjectionMat;

    Window* m_pWindow;

    float m_FOV;
    float m_NearPlane, m_FarPlane;
};
