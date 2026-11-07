#pragma once

#include <SFML/Graphics.hpp>
#include <stack>
#include <vector>

class Player
{
private:
    sf::Texture texture;
    sf::RectangleShape body;
    sf::Vector2f velocity;
    bool onGround;
    bool questionBlockHit;
    float animationTimer;
    int animationFrame;

    // Stack: earlier positions are saved so the player can rewind with R.
    std::stack<sf::Vector2f> positionHistory;
    float historyTimer;
    float rewindTimer;

public:
    Player();

    void update(float deltaTime,
                const std::vector<sf::RectangleShape>& platforms,
                const std::vector<sf::RectangleShape>& questionBlocks);
    bool jump();
    void draw(sf::RenderWindow& window) const;
    void reset(sf::Vector2f startPosition);

    bool consumeQuestionBlockHit();
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
};
