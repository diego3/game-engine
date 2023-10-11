#pragma once

#include <functional>
#include <iostream>
#include <functional>
#include <memory>
#include <map>
#include <vector>

#include "GameEvent.hpp"

typedef std::function<void(std::shared_ptr<IEvent>)> EventListener;

class EventManager {
public:
    void AddListener(EventListener listener, std::string eventName);

    void Update(float elapsedTime);

    void TriggerEvent(std::shared_ptr<IEvent> gameEvent);

    void QueueEvent(std::shared_ptr<IEvent> event);
    
    static EventManager* Get();
private:
    inline static EventManager* instance = nullptr;

    EventManager();
    // key = event name
    std::map<std::string, std::vector<EventListener>> m_listenersMap;

    std::vector<std::shared_ptr<IEvent>> m_pEventQueue;
};