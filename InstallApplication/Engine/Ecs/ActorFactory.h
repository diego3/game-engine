#pragma once

#include "Actor.h"
#include "ActorComponent.h"

typedef unsigned long ActorId;
typedef ActorComponent* (*ActorComponentCreator)(void);
typedef std::map<std::string, ActorComponentCreator> ActorComponentCreatorsMap;

typedef std::shared_ptr<Actor> StrongActorPtr;
typedef std::shared_ptr<ActorComponent> StrongActorComponent;

class ActorFactory
{
public:
	ActorFactory();
	StrongActorPtr CreateActor(const char* xmlFilePath);

protected:
	ActorComponentCreatorsMap m_actorComponentCreators;

	virtual StrongActorComponent CreateComponent(tinyxml2::XMLNode* node);

private:
	unsigned long GenerateNextActorId();
	unsigned long m_lastActorId;
};

