#pragma once

#include <Engine/Ecs/ActorComponent.h>
#include <glm/glm.hpp>

class BaseRenderComponent : public ActorComponent
{
public:
	virtual bool VInit(tinyxml2::XMLNode* node);

	virtual std::string VGetComponentName();

	virtual void VUpdate(float deltaTime);

	virtual void PosInit();

private:
	std::string m_shape;

	glm::vec4 m_color;
};

