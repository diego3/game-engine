#include <iostream>

#include <Engine/Common/Math.hpp>

// https://whimsical.com/game-overview-SPN4geWWQrNtgBzDcCQ1FF

void Experiment2() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Game");
    window.setFramerateLimit(60);
   
    sf::Texture arrowTexture;
    if (!arrowTexture.loadFromFile("Assets/Images/arrow.png")) {
        std::cout << "error trying to load texture: " << sf::err << std::endl;
    }
   
    auto rotation = 0;
    auto blockPosition = sf::Vector2f(400, 300);
    auto speed = 2.f; // px por segundo?

    sf::RectangleShape block;
    //block.setOutlineThickness(1);
   // block.setOutlineColor(sf::Color::Red);
    block.setSize(sf::Vector2f(100, 50));
    block.setTexture(&arrowTexture);
    block.setOrigin(50, 25);
    block.setPosition(blockPosition);

    sf::Vector2f direction;

    auto targetPosition = sf::Vector2f(700, 20);
    sf::CircleShape target;
    target.setRadius(20);
    target.setPosition(targetPosition);
    target.setFillColor(sf::Color::Magenta);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                targetPosition += sf::Vector2f(10, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                targetPosition -= sf::Vector2f(10, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                targetPosition -= sf::Vector2f(0, 10);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                targetPosition += sf::Vector2f(0, 10);
            }
            

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //
                direction = targetPosition - blockPosition;
                direction = Normalize(direction);
                //DebugVector2f(direction);
            }
            
            //std::cout << "mx:" <<
            //    event.mouseMove.x << " my:" << 
            //    event.mouseMove.y << std::endl;
        }

       // block.setRotation(rotation);
        //block.setPosition(direction + blockPosition);
        //auto movePerSecond = (speed * clock.getElapsedTime().asSeconds());
       // std::cout << "mps: " << movePerSecond << std::endl;

       // blockPosition += sf::Vector2f(speed, 0);
        direction = targetPosition - blockPosition;
        float distance = VectorMag(direction);
        direction = Normalize(direction);
        if (distance >= 100) {
            blockPosition += direction * speed;
            if (blockPosition.x > 800 || blockPosition.x < 0) {
                speed = speed * -1;
            }
        }
        //DebugVector2f(blockPosition);
        std::cout << "distance: " << distance << std::endl;

        block.setPosition(blockPosition);

        target.setPosition(targetPosition);





        window.clear();

        window.draw(block);
        window.draw(target);

        window.display();

        clock.restart();
    }
}

