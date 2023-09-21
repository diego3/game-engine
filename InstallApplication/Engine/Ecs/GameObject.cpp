#include <Engine/Common/UUIDv4.hpp>
#include <Engine/Ecs/GameObject.hpp>

GameObject::GameObject() {
	this->id = uuid::generate_v4();
}

void GameObject::OnInit() {
	for (auto entry : this->components) {
		entry.second->Init();
	}
}

void GameObject::AddComponent(std::string name, Component* component) {
	this->components[name] = component;
}

Component* GameObject::GetComponent(std::string name) {
	Component* comp = components[name];
	if (comp) {
		return comp;
	}
	return nullptr;
}

void GameObject::OnUpdate(float elapsedTime) {
	for (auto entry : this->components) {
		entry.second->Update(elapsedTime);
	}
}

void GameObject::OnRender(void* target) {
	for (auto entry : this->components) {
		//entry.second->Draw(target);
	}
}
