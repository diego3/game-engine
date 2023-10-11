#include "ActorFactory.h"
#include <plog/Log.h>
#include "ActorFactory.h"

#include <Engine/Ecs/Comps/TransformComponent.h>

ActorComponent* createTransform() {
	return new TransformComponent();
}

ActorFactory::ActorFactory()
{
	m_lastActorId = 0;


	ActorComponentCreator creatorFn = &createTransform;
	m_actorComponentCreators["TransformComponent"] = creatorFn;

}

StrongActorPtr ActorFactory::CreateActor(const char* xmlFilePath)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError error = doc.LoadFile(xmlFilePath);
	if (error != tinyxml2::XML_SUCCESS) {
		PLOG_ERROR << "Error load xml file: " << xmlFilePath;
		return nullptr;
	}

	StrongActorPtr actor = std::make_shared<Actor>(this->GenerateNextActorId());
	tinyxml2::XMLElement* root = doc.FirstChildElement("Actor");
	if (!actor->Init(root)) {
		PLOG_WARNING << "Actor init failure: " << xmlFilePath;
		return nullptr;
	}
	PLOG_DEBUG << "actorId: " << actor->GetId();

	tinyxml2::XMLNode* pNode = root->FirstChild();

	while (pNode != nullptr) {
		PLOG_DEBUG << "component: " << pNode->Value();

		StrongActorComponent component = CreateComponent(pNode);
		if (component) {
			actor->AddComponent(component);
			component->SetOwner(actor);
		}
		else {
			PLOG_WARNING << "Component creation failure: " << pNode->Value();
			return nullptr;
		}

		pNode = pNode->NextSibling();
	}


	return StrongActorPtr();
}

StrongActorComponent ActorFactory::CreateComponent(tinyxml2::XMLNode* node)
{
	const char* componentName = node->Value();
	auto findIt = m_actorComponentCreators.find(componentName);
	if (findIt == m_actorComponentCreators.end()) {
		PLOG_WARNING << "Creator function reference not found for component: " << componentName;
		return nullptr;
	}

	StrongActorComponent component;

	auto componentCreatorFn = findIt->second;
	if (!componentCreatorFn) {
		PLOG_ERROR << "Component [" << componentName << "] miss configured, missing creator function";
		return nullptr;
	}

	component.reset(componentCreatorFn());
	if (component) {
		if (!component->VInit(node)) {
			PLOG_WARNING << "Component [" << componentName << "] init failure";
			return nullptr;
		}
		return component;
	}

	component->PosInit();

	return nullptr;
}

unsigned long ActorFactory::GenerateNextActorId()
{
	++m_lastActorId;
	return m_lastActorId;
}
