#include "Enemy.h"

Enemy::Enemy(sf::Vector2f startPosition, float leftBoundary, float rightBoundary,
             const sf::Texture& texture)
    : speed(100.f), leftLimit(leftBoundary), rightLimit(rightBoundary),
      animationTimer(0.f), animationFrame(0)
{
    body.setSize({ 42.f, 42.f });
    body.setTexture(&texture);
    body.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 16 }));
    body.setPosition(startPosition);
}

void Enemy::update(float deltaTime)
{
    body.move({ speed * deltaTime, 0.f });

    if (body.getPosition().x + body.getSize().x > rightLimit)
    {
        body.setPosition({ rightLimit - body.getSize().x, body.getPosition().y });
        speed = -speed;
    }
    else if (body.getPosition().x < leftLimit)
    {
        body.setPosition({ leftLimit, body.getPosition().y });
        speed = -speed;
    }

    animationTimer += deltaTime;
    if (animationTimer >= 0.22f)
    {
        animationFrame = 1 - animationFrame;
        body.setTextureRect(sf::IntRect({ animationFrame * 16, 0 }, { 16, 16 }));
        animationTimer = 0.f;
    }
}

void Enemy::draw(sf::RenderWindow& window) const { window.draw(body); }
sf::FloatRect Enemy::getBounds() const { return body.getGlobalBounds(); }
