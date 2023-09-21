
#include <iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <functional>
#include <Engine/EventSystem/EventManager.hpp>
#include <Engine/Ecs/Component.hpp>

void HandleInput2(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::TextEntered) {
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        }
    }
}

class MyContactListener : public b2ContactListener {
public:
    MyContactListener() {}

    /// Called when two fixtures begin to touch.
    void BeginContact(b2Contact* contact) {
        b2Vec2 fixApos = contact->GetFixtureA()->GetBody()->GetPosition();
        b2Vec2 fixBpos = contact->GetFixtureB()->GetBody()->GetPosition();
        //contact->GetFixtureB();
        printf("contactA: [%4.2f, %4.2f]\n", fixApos.x, fixApos.y);
        printf("contactB: [%4.2f, %4.2f]\n", fixBpos.x, fixBpos.y);
    }

};

b2Vec2 gravity(0, 0);
int32 velocityIterations = 6;
int32 positionIterations = 2;
float timeStep = 1.0f / 60.0f;
float sFactor = 10.f;
int width = 800;
int height = 600;

float meterToPixel(float meters) {
    return meters * sFactor;
}

float pixelToMeter(float pixel) {
    return pixel / sFactor;
}

b2Vec2 pixelToMeterCoords(sf::Vector2f &pixel) {
    return b2Vec2(pixelToMeter(pixel.x), pixelToMeter(pixel.y));
}


class Player : public Component {
public:
    Player() {}
public:
    // render, mesh, material
    sf::Color color;
    sf::RectangleShape shape;

    sf::Vector2f position;

    // physics, kinda player controller
    b2Vec2 forceRight;
    b2Vec2 forceLeft;
    b2Vec2 forceUp;
    b2Vec2 forceDown;
    b2Body* body;

    sf::Text text1;
    sf::Text text2;

    void Init() {}

    static Player* Create(sf::Color color,
        sf::Vector2f size,
        sf::Vector2f position,
        b2World& pyshicsWorld,
        sf::Font& font) {

        sf::RectangleShape shape(size);
        shape.setFillColor(color);
        shape.setPosition(position);

        Player* gobject = new Player();
        gobject->color = color;
        gobject->shape = shape;
        gobject->position = position;

        gobject->text1.setFont(font);
        gobject->text1.setCharacterSize(10);
        gobject->text2.setFont(font);
        gobject->text2.setCharacterSize(10);

        // dynamic box
        b2BodyDef boxDef;
        boxDef.type = b2_dynamicBody;
        //boxDef.type = b2_kinematicBody;
        b2Vec2 b2BoxShapPos(0, 0.f);
        boxDef.position.Set(0, 0.f);
        gobject->body = pyshicsWorld.CreateBody(&boxDef);

        b2PolygonShape boxShape;
        b2Vec2 b2BoxShapeBox(1.f, 1.f);// 2 x 2
        boxShape.SetAsBox(b2BoxShapeBox.x, b2BoxShapeBox.y);

        b2FixtureDef boxFixture;
        boxFixture.shape = &boxShape;
        boxFixture.density = 1.0f;
        boxFixture.friction = 0.3;
        gobject->body->CreateFixture(&boxFixture);


        gobject->forceRight = b2Vec2(25.f, 0.0);
        gobject->forceLeft = b2Vec2(-25.f, 0.0);
        gobject->forceUp = b2Vec2(0, 25.f);
        gobject->forceDown = b2Vec2(0, -25.f);

        return gobject;
    }

    void ApplyForce(b2Vec2 force) {
        b2Vec2 boxForcePointPos = body->GetWorldCenter();
        body->ApplyForce(force, boxForcePointPos, true);
    }

    void OnMove(GameEvent* gameEvent) {
        // todo make a cast here to get derived event class
        if (gameEvent->GetEvent() == Event::GO_LEFT) {
            ApplyForce(forceLeft);
        }
    }

    void Update(float elapsedTime) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            ApplyForce(forceRight);
            //boxBody->SetLinearVelocity(forceRight);
        }
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
           // ApplyForce(forceLeft);
            //boxBody->SetLinearVelocity(forceLeft);
        //}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            ApplyForce(forceUp);
            //boxBody->SetLinearVelocity(forceUp);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            ApplyForce(forceDown);
            //boxBody->SetLinearVelocity(forceDown);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
           // body->ApplyLinearImpulse(b2Vec2(0, -1.f), boxForcePointPos, true);
        }

        b2Vec2 boxPos = body->GetPosition();
       //printf("velocity: %4.2f\n", body->GetLinearVelocity().y);
        position = sf::Vector2f(boxPos.x * sFactor, (boxPos.y * sFactor));
        
        this->shape.setPosition(position);
        this->text1.setString(sf::String("x:" + std::to_string(position.x)));
        this->text1.setPosition(position);
        this->text2.setString(sf::String("y:" + std::to_string(position.y)));
        this->text2.setPosition(position + sf::Vector2f(0, 10.f));

        // if (std::abs(body->GetLinearVelocity().y) > 0) {
       //     printf("box: %4.2f %4.2f\n", boxPos.x, boxPos.y);
       //     printf("draw: %4.2f %4.2f\n", position.x, position.y);
        //}
    }

    void Draw(sf::RenderTarget& target) {
        target.draw(this->shape);
        target.draw(this->text1);
        target.draw(this->text2);
    }
};

class GameObjectStatic : public Component {
public:

    // render, mesh, material
    sf::Color color;
    sf::RectangleShape shape;

    sf::Vector2f position;
    sf::Vector2f pos = sf::Vector2f(400, 300);

    // physics
    b2Body* body;

    void Init() {}

    static GameObjectStatic* Create(sf::Color color,
        sf::Vector2f size,
        sf::Vector2f position,
        b2World& pyshicsWorld) {

        sf::RectangleShape shape(size);
        shape.setFillColor(color);
        shape.setPosition(position);

        GameObjectStatic* gobject = new GameObjectStatic();
        gobject->color = color;
        gobject->shape = shape;
        gobject->position = position;

        // static
        b2BodyDef groundBodyDef;
        groundBodyDef.type = b2_staticBody;
        b2Vec2 groundBodyPos(pixelToMeter(position.x), pixelToMeter(position.y));
        groundBodyDef.position.Set(groundBodyPos.x, groundBodyPos.y);
        gobject->body = pyshicsWorld.CreateBody(&groundBodyDef);

        b2PolygonShape groundBox;
        //b2Vec2 groundBoxBox(50.f, 1.f);// 100, 2
        b2Vec2 groundBoxBox(pixelToMeter(size.x)/2, pixelToMeter(size.y)/2);// 100, 2
        groundBox.SetAsBox(groundBoxBox.x, groundBoxBox.y);

        gobject->body->CreateFixture(&groundBox, 0.0f);

        return gobject;
    }

    void Update(float elapsedTime) {

        // [400, 300] 
        // [360, 260]
        // da onde esse 40 de diferenca?????

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pos.y += 1;
            printf("ground: %4.2f %4.2f\n", pos.x, pos.y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pos.y -= 1;
            printf("ground: %4.2f %4.2f\n", pos.x, pos.y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            pos.x -= 1;
            printf("ground: %4.2f %4.2f\n", pos.x, pos.y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            pos.x += 1;
            printf("ground: %4.2f %4.2f\n", pos.x, pos.y);
        }
        this->shape.setPosition(pos);
    }

    void Draw(sf::RenderTarget& target) {
        target.draw(this->shape);
    }
};

void Box2dIntegration() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Box2d Integration");
    window.setFramerateLimit(60);

    // Init
    sf::Font font;
    font.loadFromFile("Assets/Font/LEMONMILK-Regular.otf");

    EventManager* eventManager = new EventManager();

    b2World world(gravity);
    MyContactListener* collisionListener = new MyContactListener();
    world.SetContactListener(collisionListener);
    
    std::vector<Component*> gameObjects;
    
   /* auto groundSize = sf::Vector2f(500, 20);
    Component* ground = GameObjectStatic::Create(sf::Color::Green, 
                                       groundSize,
                                       sf::Vector2f(0, 200.f),
                                       world)*/;
    
    Component* block = GameObjectStatic::Create(sf::Color::Yellow,
        sf::Vector2f(100, 100),
        sf::Vector2f(400, 300.f),
        world);

    Player* player = Player::Create(sf::Color::Red,
                                  sf::Vector2f(20, 20), 
                                  sf::Vector2f(50, 50), 
                                  world,
                                  font);

    EventListener playerListener = std::bind(&Player::OnMove, player, std::placeholders::_1);
    eventManager->AddListener(playerListener, Event::GO_LEFT);

    //gameObjects.push_back(ground);
    gameObjects.push_back(block);
    gameObjects.push_back(player);

    sf::Clock loopClock;
    while (window.isOpen()) {
        HandleInput2(window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            eventManager->TriggerEvent(Event::GO_LEFT, new GameEvent(Event::GO_LEFT));
        }

        float elapsedTime = loopClock.restart().asSeconds();
        
        //Update
        world.Step(timeStep, velocityIterations, positionIterations);
        for (Component* component : gameObjects) {
            component->Update(elapsedTime);
        }
      
        // render
        window.clear();

        for (Component* component : gameObjects) {
            component->Draw(window);
        }       

        window.display();

        //sf::sleep(sf::seconds(1));
    }
}