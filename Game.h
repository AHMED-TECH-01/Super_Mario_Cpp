#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string>

#include "GameWorld.h"
#include "Player.h"

class Game
{
private:
    enum class GameState
    {
        Playing,
        Paused,
        GameOver,
        Victory
    };

    sf::RenderWindow window;
    sf::Clock frameClock;
    sf::View cameraView;
    sf::Font font;
    sf::Music backgroundMusic;

    sf::SoundBuffer jumpBuffer;
    sf::SoundBuffer coinBuffer;
    sf::SoundBuffer hurtBuffer;
    sf::SoundBuffer gameOverBuffer;
    sf::SoundBuffer menuBuffer;
    sf::SoundBuffer enemyDeathBuffer;
    sf::SoundBuffer victoryBuffer;

    std::unique_ptr<sf::Sound> jumpSound;
    std::unique_ptr<sf::Sound> coinSound;
    std::unique_ptr<sf::Sound> hurtSound;
    std::unique_ptr<sf::Sound> gameOverSound;
    std::unique_ptr<sf::Sound> menuSound;
    std::unique_ptr<sf::Sound> enemyDeathSound;
    std::unique_ptr<sf::Sound> victorySound;

    Player player;
    GameWorld world;

    GameState state;
    int lives;
    bool restartSelected;

    void loadAudio();
    void play(std::unique_ptr<sf::Sound>& sound);
    void handleEvents();
    void update(float deltaTime);
    void render();
    void restartGame();
    void loseLife();
    void drawInterface();
    void drawMessage(const std::string& message, float y, unsigned int size);

public:
    Game();
    void run();
};
