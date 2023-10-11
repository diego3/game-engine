#include "Actor.h"

#include "Actor.h"
#include "ActorFactory.h"
#include <plog/Log.h>

Actor::Actor(unsigned long id)
{
    m_id = id;
    m_name = "";
    m_layer = "";
}

Actor::~Actor()
{
}

bool Actor::Init(tinyxml2::XMLNode* node)
{
    // TODO: Implement some initialization here...
    return true;
}

void Actor::PosInit()
{

}

std::shared_ptr<ActorComponent> Actor::AddComponent(std::shared_ptr<ActorComponent> component)
{
    auto findIt = m_components.find(component->VGetComponentName());
    if (findIt != m_components.end()) {
        PLOG_WARNING << "component [" << component->VGetComponentName() << "] replaced. ActorId: " << m_id;
    }

    m_components[component->VGetComponentName()] = component;

    return component;
}

std::shared_ptr<ActorComponent> Actor::GetComponent(std::string name)
{
    auto findIt = m_components.find(name);
    if (findIt != m_components.end()) {
        return m_components[name];
    }
    else {

        PLOG_WARNING << "component not found[" << name << "]. ActorId: " << m_id;
    }
    return nullptr;
}

void Actor::Update(float deltaTime)
{

}

unsigned long Actor::GetId()
{
    return m_id;
}