#include "GameWorld.h"

#include <algorithm>
#include <cmath>

GameWorld::GameWorld()
    : score(0), currentLevel(1), worldWidth(2200.f), checkpointX(2100.f),
      coinCollectedThisFrame(false), questionActivatedThisFrame(false)
{
    backgroundTextures[0].loadFromFile("Assets/background_level1.png");
    backgroundTextures[1].loadFromFile("Assets/background_level2.png");
    backgroundTextures[2].loadFromFile("Assets/background_level3.png");
    brickTextures[0].loadFromFile("Assets/brick_level1.png");
    brickTextures[1].loadFromFile("Assets/brick_level2.png");
    brickTextures[2].loadFromFile("Assets/brick_level3.png");
    questionTexture.loadFromFile("Assets/question_block.png");
    coinTexture.loadFromFile("Assets/coin.png");
    enemyTexture.loadFromFile("Assets/enemy_sprites.png");

    for (auto& texture : backgroundTextures) texture.setSmooth(false);
    for (auto& texture : brickTextures) texture.setSmooth(false);
    questionTexture.setSmooth(false);
    coinTexture.setSmooth(false);
    enemyTexture.setSmooth(false);

    backgroundTile.setSize({ 900.f, 600.f });
    checkpoint.setSize({ 24.f, 150.f });
    checkpoint.setFillColor(sf::Color(40, 190, 80));
    loadLevel(1);
}

void GameWorld::addPlatform(float x, float y, float width)
{
    sf::RectangleShape platform({ width, 30.f });
    platform.setPosition({ x, y });
    platforms.push_back(platform);
}

void GameWorld::addQuestionBlock(float x, float y)
{
    sf::RectangleShape block({ 40.f, 40.f });
    block.setPosition({ x, y });
    questionBlocks.push_back(block);
    questionBlockUsed.push_back(false);
}

void GameWorld::addCoin(float x, float y)
{
    sf::CircleShape coin(12.f);
    coin.setPosition({ x, y });
    coins.push_back(coin);
}

void GameWorld::resetGame()
{
    score = 0;
    loadLevel(1);
}

void GameWorld::loadLevel(int level)
{
    currentLevel = level;
    platforms.clear();
    questionBlocks.clear();
    questionBlockUsed.clear();
    coins.clear();
    enemies.clear();
    enemySpawnQueue = std::queue<sf::Vector2f>();
    coinCollectedThisFrame = false;
    questionActivatedThisFrame = false;

    addPlatform(0.f, 550.f, worldWidth);
    checkpoint.setPosition({ checkpointX, 400.f });

    if (level == 1) loadLevelOne();
    else if (level == 2) loadLevelTwo();
    else loadLevelThree();

    spawnClock.restart();
}

void GameWorld::loadLevelOne()
{
    addPlatform(250.f, 455.f, 150.f);
    addPlatform(520.f, 385.f, 150.f);
    addPlatform(820.f, 455.f, 160.f);
    addPlatform(1120.f, 375.f, 160.f);
    addPlatform(1450.f, 455.f, 160.f);
    addPlatform(1760.f, 390.f, 160.f);

    addQuestionBlock(350.f, 390.f);
    addQuestionBlock(900.f, 365.f);
    addQuestionBlock(1510.f, 390.f);

    addCoin(300.f, 415.f);
    addCoin(570.f, 345.f);
    addCoin(880.f, 415.f);
    addCoin(1180.f, 335.f);
    addCoin(1510.f, 415.f);
    addCoin(1820.f, 350.f);

    enemySpawnQueue.push({ 430.f, 508.f });
    enemySpawnQueue.push({ 1050.f, 508.f });
    enemySpawnQueue.push({ 1650.f, 508.f });
}

void GameWorld::loadLevelTwo()
{
    addPlatform(200.f, 445.f, 130.f);
    addPlatform(440.f, 350.f, 140.f);
    addPlatform(720.f, 420.f, 130.f);
    addPlatform(990.f, 330.f, 150.f);
    addPlatform(1280.f, 430.f, 140.f);
    addPlatform(1550.f, 345.f, 150.f);
    addPlatform(1840.f, 430.f, 150.f);

    addQuestionBlock(270.f, 375.f);
    addQuestionBlock(790.f, 350.f);
    addQuestionBlock(1600.f, 275.f);

    addCoin(240.f, 405.f);
    addCoin(485.f, 310.f);
    addCoin(765.f, 380.f);
    addCoin(1040.f, 290.f);
    addCoin(1330.f, 390.f);
    addCoin(1600.f, 305.f);
    addCoin(1890.f, 390.f);

    enemySpawnQueue.push({ 360.f, 508.f });
    enemySpawnQueue.push({ 850.f, 508.f });
    enemySpawnQueue.push({ 1200.f, 508.f });
    enemySpawnQueue.push({ 1750.f, 508.f });
}

void GameWorld::loadLevelThree()
{
    // Slightly lower platforms make this level reachable with the current jump.
    addPlatform(230.f, 460.f, 120.f);
    addPlatform(470.f, 390.f, 130.f);
    addPlatform(730.f, 450.f, 120.f);
    addPlatform(990.f, 380.f, 130.f);
    addPlatform(1250.f, 455.f, 120.f);
    addPlatform(1510.f, 390.f, 130.f);
    addPlatform(1780.f, 450.f, 150.f);

    addQuestionBlock(300.f, 385.f);
    addQuestionBlock(1060.f, 305.f);
    addQuestionBlock(1580.f, 315.f);

    addCoin(270.f, 420.f);
    addCoin(515.f, 350.f);
    addCoin(770.f, 410.f);
    addCoin(1035.f, 340.f);
    addCoin(1290.f, 415.f);
    addCoin(1555.f, 350.f);
    addCoin(1835.f, 410.f);

    enemySpawnQueue.push({ 380.f, 508.f });
    enemySpawnQueue.push({ 800.f, 508.f });
    enemySpawnQueue.push({ 1150.f, 508.f });
    enemySpawnQueue.push({ 1500.f, 508.f });
    enemySpawnQueue.push({ 1900.f, 508.f });
}

bool GameWorld::update(float deltaTime, Player& player)
{
    coinCollectedThisFrame = false;
    questionActivatedThisFrame = false;

    if (!enemySpawnQueue.empty() &&
        spawnClock.getElapsedTime().asSeconds() >= 2.5f)
    {
        enemies.emplace_back(enemySpawnQueue.front(), 0.f, worldWidth, enemyTexture);
        enemySpawnQueue.pop();
        spawnClock.restart();
    }

    bool playerWasHit = false;
    for (auto& enemy : enemies)
    {
        enemy.update(deltaTime);
        if (player.getBounds().findIntersection(enemy.getBounds()))
            playerWasHit = true;
    }

    for (auto coin = coins.begin(); coin != coins.end(); )
    {
        if (player.getBounds().findIntersection(coin->getGlobalBounds()))
        {
            coin = coins.erase(coin);
            ++score;
            coinCollectedThisFrame = true;
        }
        else ++coin;
    }

    if (player.consumeQuestionBlockHit())
    {
        // Activate the closest unused question block.
        int bestIndex = -1;
        float bestDistance = 100000.f;
        for (int i = 0; i < static_cast<int>(questionBlocks.size()); ++i)
        {
            if (questionBlockUsed[i]) continue;
            float distance = std::abs(player.getPosition().x -
                                      questionBlocks[i].getPosition().x);
            if (distance < bestDistance)
            {
                bestDistance = distance;
                bestIndex = i;
            }
        }

        if (bestIndex != -1 && bestDistance < 100.f)
        {
            questionBlockUsed[bestIndex] = true;
            ++score;
            questionActivatedThisFrame = true;
        }
    }

    return playerWasHit;
}

void GameWorld::draw(sf::RenderWindow& window) const
{
    backgroundTile.setTexture(&backgroundTextures[currentLevel - 1]);
    for (float x = 0.f; x < worldWidth; x += 900.f)
    {
        backgroundTile.setPosition({ x, 0.f });
        window.draw(backgroundTile);
    }

    const sf::Texture& brick = brickTextures[currentLevel - 1];
    for (const auto& platform : platforms)
    {
        const sf::Vector2f pos = platform.getPosition();
        const sf::Vector2f size = platform.getSize();

        for (float y = 0.f; y < size.y; y += 16.f)
        {
            for (float x = 0.f; x < size.x; x += 16.f)
            {
                sf::RectangleShape tile({ std::min(16.f, size.x - x),
                                          std::min(16.f, size.y - y) });
                tile.setTexture(&brick);
                tile.setPosition({ pos.x + x, pos.y + y });
                window.draw(tile);
            }
        }
    }

    for (std::size_t i = 0; i < questionBlocks.size(); ++i)
    {
        sf::RectangleShape block({ 40.f, 40.f });
        block.setTexture(&questionTexture);
        block.setTextureRect(sf::IntRect({ questionBlockUsed[i] ? 16 : 0, 0 },
                                         { 16, 16 }));
        block.setPosition(questionBlocks[i].getPosition());
        window.draw(block);
    }

    for (const auto& coin : coins)
    {
        sf::RectangleShape sprite({ 24.f, 24.f });
        sprite.setTexture(&coinTexture);
        sprite.setPosition(coin.getPosition());
        window.draw(sprite);
    }

    for (const auto& enemy : enemies) enemy.draw(window);

    window.draw(checkpoint);
}

const std::vector<sf::RectangleShape>& GameWorld::getPlatforms() const { return platforms; }
const std::vector<sf::RectangleShape>& GameWorld::getQuestionBlocks() const { return questionBlocks; }

bool GameWorld::consumeCoinCollected()
{
    bool result = coinCollectedThisFrame;
    coinCollectedThisFrame = false;
    return result;
}

bool GameWorld::consumeQuestionActivated()
{
    bool result = questionActivatedThisFrame;
    questionActivatedThisFrame = false;
    return result;
}

int GameWorld::getScore() const { return score; }
int GameWorld::getCurrentLevel() const { return currentLevel; }
float GameWorld::getWorldWidth() const { return worldWidth; }
float GameWorld::getCheckpointX() const { return checkpointX; }
