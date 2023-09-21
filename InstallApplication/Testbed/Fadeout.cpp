
#include <iostream>
#include <SFML/Graphics.hpp>

class Fade {
private:
    Fade() {}
public:
    sf::Clock clock;
    sf::Color color;
    sf::CircleShape shape;
    int opacity;
    float timeout;

    static Fade* Create(sf::Color color, sf::Vector2f position, float timeoutMs) {
        sf::CircleShape shape(50.f);
        shape.setFillColor(color);
        shape.setPosition(position);
        
        sf::Clock clock;
        
        Fade* fade = new Fade();
        fade->color = color;
        fade->opacity = 255;
        fade->timeout = timeoutMs;
        fade->clock = clock;
        fade->shape = shape;

        return fade;
    }

    void Update(float elapsedTime) {
        float milis = clock.getElapsedTime().asSeconds();
       // printf("milis %.4f\n", milis);
       // printf("elapsed %.4f\n", elapsedTime);

        if (milis >= this->timeout) {
            //std::cout << "tick: " << opacity << std::endl;
            
            this->opacity -= 100;
            if (this->opacity < 0) {
                this->opacity = 255;
            }
            clock.restart();
        }
    }

    void Render(sf::RenderWindow *window) {
        this->color.a = this->opacity;
        shape.setFillColor(color);

        window->draw(this->shape);
    }
};

class Counter {
private:
    Counter() {}
public:
    int count;
    sf::Font font;
    sf::Text text;
    float timeout;

    static Counter* Create(int count, sf::String fontFile) {
        Counter* counter = new Counter();
        counter->count = count;

        if (!counter->font.loadFromFile(fontFile)) {
            printf("error trying to load font %s Error: %s\n", fontFile.toAnsiString(), sf::err);
        }
        counter->text.setFont(counter->font);
        //counter->text.setString(std::to_string(count));
        counter->text.setPosition(400, 400);
        counter->text.setCharacterSize(40);

        return counter;
    }

    void Update(float elapsedTime) {
        timeout += elapsedTime;
        
        if (timeout >= 1) {
            timeout = 0;
            count--;
            if (count <= 0) {
                count = 0;
            }
        }
    }

    void Render(sf::RenderWindow* window) {
        text.setString(std::to_string(count));
        window->draw(text);
    }

    ~Counter() {}
};


std::vector<sf::Uint32> letras;

void HandleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::TextEntered) {
            
            letras.push_back(event.text.unicode);
            //std::cout << txt << std::endl;
        }
    }
}

void Fadeout() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fadeout");
    window.setFramerateLimit(60);

    sf::Clock loopClock;

    auto fade1 = Fade::Create(sf::Color::Red, sf::Vector2f(100, 100), 0.350f);
    auto fade2 = Fade::Create(sf::Color::Green, sf::Vector2f(200, 200), 0.200f);
    auto counter = Counter::Create(10, "Assets/Font/badaboom_bb.ttf");

    sf::Font font;
    font.loadFromFile("Assets/Font/LEMONMILK-Regular.otf");


    while (window.isOpen()) {
        HandleInput(window);

        float elapsedTime = loopClock.restart().asSeconds();
        fade1->Update(elapsedTime);
        fade2->Update(elapsedTime);
        counter->Update(elapsedTime);

        // render
        window.clear();

        fade1->Render(&window);
        fade2->Render(&window);
        counter->Render(&window);

        float lpad = 50.f;
        float hpad = 40.f;
        float newLineSpace = 25.f;
        float fontSize = 20.f;
        float spaceChars = 12.f;
        for (sf::Uint32 v : letras) {
            sf::Text text(v, font, fontSize);
            text.setPosition(lpad, hpad);
            if (v == 13) {// Enter a new line
                hpad += newLineSpace;
                lpad = 50; // reseta a coluna
            }
            else {
                window.draw(text);
                lpad += spaceChars;
            }
        }

        
        window.display();
    }
}