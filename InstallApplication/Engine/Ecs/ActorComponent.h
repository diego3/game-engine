#pragma once

#include <memory>
#include <string>
#include <tinyxml2.h>

class Actor;
#include "Actor.h"

class ActorComponent
{
public:
	ActorComponent() {};
	virtual ~ActorComponent() {};

	void SetOwner(std::shared_ptr<Actor> owner)
	{
		m_owner = owner;
	};

	virtual bool VInit(tinyxml2::XMLNode* node) = 0;

	virtual std::string VGetComponentName() = 0;

	virtual void VUpdate(float deltaTime) {};

	virtual void PosInit() {};
protected:
	std::shared_ptr<Actor> m_owner;
};