#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
private:
    sf::RectangleShape body;
    float speed;
    float leftLimit;
    float rightLimit;
    float animationTimer;
    int animationFrame;

public:
    Enemy(sf::Vector2f startPosition, float leftBoundary, float rightBoundary,
          const sf::Texture& texture);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
};
