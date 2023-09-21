#include "EventManager.hpp"

EventManager::EventManager() {}

void EventManager::AddListener(EventListener listener, Event event) {
    std::vector<EventListener> listeners = listenersMap[event];
    if (!listener) {
        listeners = std::vector<EventListener>::vector();
    }
    listeners.push_back(listener);

    listenersMap[event] = listeners;
}

void EventManager::Update(float elapsedTime) {

}

void EventManager::TriggerEvent(Event event, GameEvent* gameEvent) {
    std::vector<EventListener> listeners = this->listenersMap[event];
    for (EventListener listener : listeners) {
        listener(gameEvent);
    }
}

void EventManager::TriggetEvent(Event event)
{
}
