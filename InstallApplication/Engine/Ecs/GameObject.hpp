#include <map>
#include <iostream>
#include <Engine/Ecs/Component.hpp>

class GameObject {

public:
	GameObject();

	void OnInit();
	
	void AddComponent(std::string name, Component *component);

	Component* GetComponent(std::string name);

	void OnUpdate(float elapsedTime);

	void OnRender(void* target);

private:
	std::string id;

	std::map<std::string, Component*> components;
};