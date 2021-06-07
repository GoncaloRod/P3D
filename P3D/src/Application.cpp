#include "pch.h"

#include "glm/glm.hpp"

#include "Window.h"

#include "Cameras/FreeCamera.h"
#include "Cameras/OrbitCamera.h"
#include "Graphics/Model.h"
#include "Renderer/Shader.h"

int main(int argc, char** argv)
{
	double lastFrame, currentFrame, deltaTime;

	// Set up window
	Window window("P3D", 1280, 720);

	currentFrame = lastFrame = glfwGetTime();

	// Setup cameras
	FreeCamera freeCamera = FreeCamera(glm::radians(45.0f), 0.01f, 1000.0f, &window, glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, glm::radians(180.0f), 0.0f));
	OrbitCamera orbitCamera = OrbitCamera(glm::radians(45.0f), 0.01f, 1000.0f, &window, { 0.0f, 1.0f, 0.0f });

	Camera* activeCamera = &orbitCamera;
	activeCamera->OnEnable();
	
	// Load assets
	auto shader = std::make_shared<Shader>("assets/shaders/Phong.vert", "assets/shaders/Phong.frag");

	auto rocket = Model::LoadFromObj(shader, "assets/models/TheRocket/TheRocket.obj");
	if (rocket == nullptr)
	{
		std::cout << "Failed to load model" << std::endl;
		return 0;
	}

	rocket->SetPosition({ -2.0f, 0.0f, 0.0f });

	auto ironMan = Model::LoadFromObj(shader, "assets/models/Iron_Man/Iron_Man.obj");
	if (ironMan == nullptr)
	{
		std::cout << "Failed to load model" << std::endl;
		return 0;
	}

	ironMan->SetPosition({ 2.0f, 0.0f, 0.0f });
	
	glm::vec3 ambientColor = glm::vec3(0.1f, 0.1f, 0.1f);

	bool ambientEnable = true;
	bool directionalEnable = true;
	bool pointEnable = false;
	bool spotEnable = false;

	bool inflation = false;
	
	while (!window.ShouldClose())
	{
		// Update render stats
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Update
		if (glfwGetKey(window.GetNativeWindow(), GLFW_KEY_F1) == GLFW_PRESS)
		{
			activeCamera->OnDisable();
			activeCamera = &orbitCamera;
			activeCamera->OnEnable();
		}
		else if (glfwGetKey(window.GetNativeWindow(), GLFW_KEY_F2) == GLFW_PRESS)
		{
			activeCamera->OnDisable();
			activeCamera = &freeCamera;
			activeCamera->OnEnable();
		}

		if (glfwGetKey(window.GetNativeWindow(), GLFW_KEY_1) == GLFW_PRESS)
			ambientEnable = !ambientEnable;

		if (glfwGetKey(window.GetNativeWindow(), GLFW_KEY_2) == GLFW_PRESS)
			directionalEnable = !directionalEnable;

		if (glfwGetKey(window.GetNativeWindow(), GLFW_KEY_3) == GLFW_PRESS)
			pointEnable = !pointEnable;

		if (glfwGetKey(window.GetNativeWindow(), GLFW_KEY_4) == GLFW_PRESS)
			spotEnable = !spotEnable;

		if (glfwGetKey(window.GetNativeWindow(), GLFW_KEY_T) == GLFW_PRESS)
			inflation = !inflation;
		
		activeCamera->Update(static_cast<float>(deltaTime));

		// Draw
		glClearColor(ambientColor.r, ambientColor.g, ambientColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->Bind();

		//shader->SetMat4("u_View", activeCamera->GetViewMatrix());
		//shader->SetMat4("u_Projection", activeCamera->GetProjectionMatrix());
		shader->SetMat4("u_ViewProjection", activeCamera->GetProjectionMatrix() * activeCamera->GetViewMatrix());

		shader->SetBool("u_Lighting.AmbientEnable", ambientEnable);
		shader->SetBool("u_Lighting.DirectionalEnable", directionalEnable);
		shader->SetBool("u_Lighting.PointEnable", pointEnable);
		shader->SetBool("u_Lighting.SpotEnable", spotEnable);

		shader->SetVec3("u_Lighting.Ambient.Color", ambientColor);

		shader->SetVec3("u_Lighting.Directional.Direction", { -1, -1, 0});
		shader->SetVec3("u_Lighting.Directional.Color", glm::vec3(1.0f));

		shader->SetVec3("u_Lighting.Point.Position", freeCamera.GetPosition());
		shader->SetVec3("u_Lighting.Point.Color", { 1.0f, 1.0f, 1.0f });
		shader->SetFloat("u_Lighting.Point.Constant", 1.0f);
		shader->SetFloat("u_Lighting.Point.Linear", 0.09f);
		shader->SetFloat("u_Lighting.Point.Quadratic", 0.032f);

		shader->SetVec3("u_Lighting.Spot.Position", freeCamera.GetPosition());
		shader->SetVec3("u_Lighting.Spot.Direction", freeCamera.GetForward());
		shader->SetVec3("u_Lighting.Spot.Color", { 1.0f, 1.0f, 1.0f });
		shader->SetFloat("u_Lighting.Spot.InnerCutOff", glm::cos(glm::radians(10.0f)));
		shader->SetFloat("u_Lighting.Spot.OuterCutOff", glm::cos(glm::radians(17.5f)));

		shader->SetVec3("u_CameraPos", activeCamera->GetPosition());

		shader->SetFloat("u_Inflation", 0.0f);

		rocket->Draw();

		if (inflation)
			shader->SetFloat("u_Inflation", (glm::sin(static_cast<float>(glfwGetTime())) / 2 + 0.5f) * 0.1f);
		
		ironMan->Draw();

		// OpenGL things
		window.SwapBuffers();
		glfwPollEvents();
	}

	glfwTerminate();
	
	return 0;
}
