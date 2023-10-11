#pragma once

#include <Engine/Ecs/ActorComponent.h>
#include <glm/glm.hpp>

class TransformComponent : public ActorComponent
{
public:
	virtual bool VInit(tinyxml2::XMLNode* node);

	virtual std::string VGetComponentName();

	virtual void VUpdate(float deltaTime);

	virtual void PosInit();

	glm::vec3 GetPosition();

	glm::vec3 GetRotation();

	glm::vec3 GetScale();

	glm::mat4 GetTransform();

private:
	glm::vec3 m_position;

	glm::vec3 m_rotation;

	glm::vec3 m_scale;

	glm::mat4 m_transform;
};


