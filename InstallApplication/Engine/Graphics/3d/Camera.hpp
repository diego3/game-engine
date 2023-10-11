#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>  // translate, rotate, scale
#include <glm/ext/matrix_clip_space.hpp> // projection
#include <glm/gtc/type_ptr.hpp> 


class Camera {
public:
	Camera();

	glm::mat4 GetProjection();

	glm::mat4 GetView();
private:
	glm::mat4 view;
	glm::mat4 projection;

	float aspectRatio;
	float near;
	float far;
	float fieldOfView;
};