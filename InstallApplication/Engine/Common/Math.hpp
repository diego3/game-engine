#ifndef MATH_H
#define MATH_H

#include <iostream>

float VectorMag(sf::Vector2f& v2) {
    float x2 = v2.x * v2.x;
    float y2 = v2.y * v2.y;
    return std::sqrt(x2 + y2);
}

sf::Vector2f Normalize(sf::Vector2f& v2) {
    float mag = VectorMag(v2);
    return sf::Vector2f(v2.x / mag, v2.y / mag);
}

void DebugRectf2(sf::FloatRect rect) {
    std::cout << "x:" << rect.getPosition().x << " " << "y:" << rect.getPosition().y << std::endl;
}

void DebugRecti2(sf::IntRect rect) {
    std::cout << "x:" << rect.getPosition().x << " " << "y:" << rect.getPosition().y << std::endl;
}

void DebugVector2f2(sf::Vector2f& vector2) {
    std::cout << "x:" << vector2.x << " " << "y:" << vector2.y << std::endl;
}

#endif