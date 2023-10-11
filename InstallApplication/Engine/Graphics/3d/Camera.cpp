
#include <Engine/Graphics/3d/Camera.hpp>

Camera::Camera()
{
	this->view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	this->view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	this->aspectRatio = 1200.f / 640.f;
	this->near = 0.1f;
	this->far = 100.f;
	this->fieldOfView = glm::radians(45.f);
	this->projection = glm::perspective(fieldOfView, aspectRatio, near, far);
}

glm::mat4 Camera::GetProjection()
{
	return this->projection;
}

glm::mat4 Camera::GetView()
{
	return this->view;
}
