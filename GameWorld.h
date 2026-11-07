#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <vector>

#include "Enemy.h"
#include "Player.h"

class GameWorld
{
private:
    std::vector<sf::RectangleShape> platforms;
    std::vector<sf::RectangleShape> questionBlocks;
    std::vector<bool> questionBlockUsed;
    std::vector<sf::CircleShape> coins;
    std::vector<Enemy> enemies;

    std::queue<sf::Vector2f> enemySpawnQueue;

    sf::Texture backgroundTextures[3];
    sf::Texture brickTextures[3];
    sf::Texture questionTexture;
    sf::Texture coinTexture;
    sf::Texture enemyTexture;
    mutable sf::RectangleShape backgroundTile;

    sf::Clock spawnClock;
    sf::RectangleShape checkpoint;
    int score;
    int currentLevel;
    float worldWidth;
    float checkpointX;
    bool coinCollectedThisFrame;
    bool questionActivatedThisFrame;

    void addPlatform(float x, float y, float width);
    void addQuestionBlock(float x, float y);
    void addCoin(float x, float y);
    void loadLevelOne();
    void loadLevelTwo();
    void loadLevelThree();

public:
    GameWorld();

    void loadLevel(int level);
    void resetGame();
    bool update(float deltaTime, Player& player);
    void draw(sf::RenderWindow& window) const;

    const std::vector<sf::RectangleShape>& getPlatforms() const;
    const std::vector<sf::RectangleShape>& getQuestionBlocks() const;
    bool consumeCoinCollected();
    bool consumeQuestionActivated();
    int getScore() const;
    int getCurrentLevel() const;
    float getWorldWidth() const;
    float getCheckpointX() const;
};
