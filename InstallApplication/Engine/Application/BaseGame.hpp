#pragma once

#include <iostream>
#include <vector>

#include <Engine/Ecs/GameObject.hpp>
#include <Engine/EventSystem/EventManager.hpp>

// specific games should implement this base class
class AbstractGame {
public:
	virtual void VInit() {};

	virtual void VUpdate(float elapsedTime) {};

	virtual void VRender() {};

private:
	std::string name;

	std::vector<GameObject*> gameObjects;

	EventManager* eventManager;
};