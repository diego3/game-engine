#include <iostream>
#include <iterator>

//#include <Engine/Common/Math.hpp>

// https://whimsical.com/game-overview-SPN4geWWQrNtgBzDcCQ1FF

sf::RectangleShape CreateBlock(sf::Vector2f position) {
    sf::RectangleShape block;
    block.setFillColor(sf::Color(110, 110, 110));
    block.setOutlineColor(sf::Color(50, 50, 50));
    block.setOutlineThickness(2.f);
    block.setSize(sf::Vector2f(50, 50));
   // block.setOrigin(block.getSize().x / 2, block.getSize().y / 2);
    block.setPosition(position);
    return block;
}

sf::RectangleShape CreateFireBlock(sf::Vector2f position) {
    sf::RectangleShape block;
    block.setFillColor(sf::Color(200, 0, 0, 150));
    block.setSize(sf::Vector2f(50, 50));
    block.setPosition(position);
    return block;
}

enum class BombState {
    LAUNCHED,
    EXPLODED
};

class Bomb {
private: 
    bool explode;
    float timeToExplode;
    float explodeTimer;
    BombState state;
public:
    sf::CircleShape shape;
    //Bomb() {
   //     explode = false;
   // }
    static Bomb* Create(sf::Vector2f position, float explodeDelay) {
        Bomb* bomb = new Bomb();
        
        bomb->shape.setRadius(20);
        bomb->shape.setPosition(position);
        bomb->shape.setFillColor(sf::Color::Black);
        bomb->timeToExplode = explodeDelay;
        bomb->explodeTimer = 0;

        return bomb;
    }

    void Explode() {
        explode = true;
    }

    void Update(float elapsedTime) {
        if (explode) {
            explodeTimer += elapsedTime;
        }
        else {
            //explodeTimer = 0;
        }
    }

    void Render(sf::RenderWindow &window) {
        if (explode && explodeTimer >= timeToExplode) {
            this->shape.setFillColor(sf::Color::Red);

            auto front1 = this->shape.getPosition() + sf::Vector2f(50, 0);
            auto bottom1 = this->shape.getPosition() + sf::Vector2f(0, 50);
            window.draw(CreateFireBlock(this->shape.getPosition()));
            window.draw(CreateFireBlock(front1));
            window.draw(CreateFireBlock(bottom1));
        } else {
            window.draw(this->shape);
        }
    }
};


void HandleInput(sf::RenderWindow &window, Bomb *bomb) {
    auto player1Position = sf::Vector2f(100, 100);

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player1Position += sf::Vector2f(10, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player1Position -= sf::Vector2f(10, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player1Position -= sf::Vector2f(0, 10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player1Position += sf::Vector2f(0, 10);
        }


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            bomb->Explode();
        }

        //std::cout << "mx:" <<
        //    event.mouseMove.x << " my:" << 
        //    event.mouseMove.y << std::endl;
    }
}

void Bomberman() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bomberman");
    window.setFramerateLimit(30);

    int level1[256] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0,
        0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        //0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
       // 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    

    Bomb* bomb = Bomb::Create(sf::Vector2f(50, 50), 3.f);

    sf::Clock loopClock;
    while (window.isOpen()) {
       
        HandleInput(window, bomb);

        float elapsedTime = loopClock.restart().asSeconds();
        //Update
        bomb->Update(elapsedTime);

        // Render
        window.clear(sf::Color(0, 100, 0, 1));

        auto rowSize = 16;
        auto row = 0;
        auto column = 0;
        for (int i = 0; i < std::size(level1); i++) {
            if (i > 0 && i % rowSize == 0) {
                row += 50;
                column = 0;
            } 
            auto blockPos = sf::Vector2f(column * 50, row);
            column++;

            if (level1[i] == 0) {
                window.draw(CreateBlock(blockPos));
            }
        }


        bomb->Render(window);

        window.display();
    }
}

