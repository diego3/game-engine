#pragma once

#include <map>

class ActorComponent;
#include "ActorComponent.h"

class Actor
{

public:
	Actor(unsigned long id);
	~Actor();

	bool Init(tinyxml2::XMLNode* node);
	void PosInit();

	std::shared_ptr<ActorComponent> AddComponent(std::shared_ptr<ActorComponent> component);

	std::shared_ptr<ActorComponent> GetComponent(std::string name);

	void Update(float deltaTime);

	unsigned long GetId();

private:
	unsigned long m_id;

	std::map<std::string, std::shared_ptr<ActorComponent>> m_components;

	std::string m_name;
	std::string m_layer;//? maybe for collision???
};


