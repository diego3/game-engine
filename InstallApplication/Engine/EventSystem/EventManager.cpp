#include "EventManager.hpp"
#include <plog/Log.h>
#include <memory>

EventManager::EventManager() 
{
    m_pEventQueue = std::vector<std::shared_ptr<IEvent>>();
}

void EventManager::AddListener(EventListener listener, std::string eventName) {
    std::vector<EventListener> listeners = m_listenersMap[eventName];
    if (!listener) {
        listeners = std::vector<EventListener>::vector();
    }
    listeners.push_back(listener);

    m_listenersMap[eventName] = listeners;
}

void EventManager::Update(float elapsedTime) {
    if (this->m_pEventQueue.empty())
    {
        PLOG_DEBUG << "event queue is empty";
    }

    for (std::shared_ptr<IEvent> event : this->m_pEventQueue) {
        this->TriggerEvent(event);
    }
}

void EventManager::TriggerEvent(std::shared_ptr<IEvent> event) {
    std::vector<EventListener> listeners = this->m_listenersMap[event->GetName()];
    for (EventListener listener : listeners) {
        listener(event);
    }
}

void EventManager::QueueEvent(std::shared_ptr<IEvent> event)
{
    this->m_pEventQueue.emplace_back(event);
}

EventManager* EventManager::Get()
{
    if (!instance) {
        instance = new EventManager();
    }
    return instance;
}
