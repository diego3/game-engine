#include <functional>
#include <iostream>
#include <functional>
#include <map>
#include <vector>

enum class Event {
    GO_RIGHT,
    GO_LEFT,
    GO_UP,
    GO_DOWN,
    COLLISION_ENTER
};

class GameEvent {

public:
    GameEvent(Event event) {
        this->event = event;
    }

    Event GetEvent() {
        return event;
    };
private:
    std::string uuid;

    std::string gameObjectId;
    
    Event event;
};

typedef std::function<void(GameEvent*)> EventListener;

class EventManager {
public:
    EventManager();

    void AddListener(EventListener listener, Event event);

    void Update(float elapsedTime);

    void TriggerEvent(Event event, GameEvent* gameEvent);

    void TriggetEvent(Event event);

private:
    std::map<Event, std::vector<EventListener>> listenersMap;

    std::vector<Event> eventQueue;
};