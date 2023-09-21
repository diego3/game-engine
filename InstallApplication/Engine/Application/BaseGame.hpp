#include <iostream>
#include <vector>

#include <Engine/Ecs/GameObject.hpp>
#include <Engine/EventSystem/EventManager.hpp>

// specific games should implement this base class
class AbstractGame {
public:
	void Init();

	void Update(float elapsedTime);

	void Render();

private:
	std::string name;

	std::vector<GameObject*> gameObjects;

	EventManager* eventManager;
};