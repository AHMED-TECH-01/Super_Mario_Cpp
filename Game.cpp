#include "Game.h"

#include <algorithm>
#include <optional>

Game::Game()
    : window(sf::VideoMode({ 900, 600 }), "Super Adventure"),
      state(GameState::Playing), lives(3), restartSelected(true)
{
    window.setFramerateLimit(60);
    cameraView = window.getDefaultView();

    if (!font.openFromFile("Assets/DejaVuSans.ttf"))
        window.setTitle("Super Adventure - font file not found");

    loadAudio();
}

void Game::loadAudio()
{
    // Sound buffers stay alive for as long as their sf::Sound objects use them.
    if (jumpBuffer.loadFromFile("Assets/Audio/jump-1.wav"))
        jumpSound = std::make_unique<sf::Sound>(jumpBuffer);
    if (coinBuffer.loadFromFile("Assets/Audio/coin-1.wav"))
        coinSound = std::make_unique<sf::Sound>(coinBuffer);
    if (hurtBuffer.loadFromFile("Assets/Audio/player-hurt-1.wav"))
        hurtSound = std::make_unique<sf::Sound>(hurtBuffer);
    if (gameOverBuffer.loadFromFile("Assets/Audio/game-over.wav"))
        gameOverSound = std::make_unique<sf::Sound>(gameOverBuffer);
    if (menuBuffer.loadFromFile("Assets/Audio/menu-select.wav"))
        menuSound = std::make_unique<sf::Sound>(menuBuffer);
    if (enemyDeathBuffer.loadFromFile("Assets/Audio/enemy-death-1.wav"))
        enemyDeathSound = std::make_unique<sf::Sound>(enemyDeathBuffer);
    if (victoryBuffer.loadFromFile("Assets/Audio/victory.wav"))
        victorySound = std::make_unique<sf::Sound>(victoryBuffer);

    if (backgroundMusic.openFromFile("Assets/Audio/background-loop.wav"))
    {
        backgroundMusic.setLooping(true);
        backgroundMusic.setVolume(22.f);
        backgroundMusic.play();
    }
}

void Game::play(std::unique_ptr<sf::Sound>& sound)
{
    if (sound)
        sound->play();
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();

        float deltaTime = frameClock.restart().asSeconds();
        deltaTime = std::min(deltaTime, 0.05f);

        if (state == GameState::Playing)
            update(deltaTime);

        render();
    }
}

void Game::handleEvents()
{
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            if (state == GameState::Playing)
            {
                if (key->code == sf::Keyboard::Key::P)
                {
                    state = GameState::Paused;
                    backgroundMusic.pause();
                }
                else if (key->code == sf::Keyboard::Key::Space)
                {
                    if (player.jump()) play(jumpSound);
                }
            }
            else if (state == GameState::Paused)
            {
                if (key->code == sf::Keyboard::Key::P ||
                    key->code == sf::Keyboard::Key::Enter)
                {
                    state = GameState::Playing;
                    backgroundMusic.play();
                }
            }
            else if (state == GameState::GameOver || state == GameState::Victory)
            {
                if (key->code == sf::Keyboard::Key::Up ||
                    key->code == sf::Keyboard::Key::Down)
                {
                    restartSelected = !restartSelected;
                    play(menuSound);
                }
                else if (key->code == sf::Keyboard::Key::Enter)
                {
                    play(menuSound);
                    if (restartSelected) restartGame();
                    else window.close();
                }
                else if (key->code == sf::Keyboard::Key::Escape)
                    window.close();
            }
        }
    }
}

void Game::update(float deltaTime)
{
    player.update(deltaTime, world.getPlatforms(), world.getQuestionBlocks());

    if (player.getPosition().y > 700.f)
    {
        loseLife();
        return;
    }

    if (world.update(deltaTime, player))
    {
        loseLife();
        return;
    }

    if (world.consumeCoinCollected())
        play(coinSound);
    if (world.consumeQuestionActivated())
        play(coinSound);

    if (player.getPosition().x + 40.f >= world.getCheckpointX())
    {
        if (world.getCurrentLevel() < 3)
        {
            world.loadLevel(world.getCurrentLevel() + 1);
            player.reset({ 60.f, 500.f });
        }
        else
        {
            state = GameState::Victory;
            restartSelected = true;
            backgroundMusic.stop();
            play(victorySound);
        }
    }

    float cameraX = player.getPosition().x + 20.f;
    cameraX = std::max(450.f, cameraX);
    cameraX = std::min(world.getWorldWidth() - 450.f, cameraX);
    cameraView.setCenter({ cameraX, 300.f });
}

void Game::loseLife()
{
    --lives;
    play(hurtSound);

    if (lives <= 0)
    {
        state = GameState::GameOver;
        restartSelected = true;
        backgroundMusic.stop();
        play(gameOverSound);
    }
    else
    {
        player.reset({ 60.f, 500.f });
    }
}

void Game::restartGame()
{
    lives = 3;
    world.resetGame();
    player.reset({ 60.f, 500.f });
    state = GameState::Playing;
    restartSelected = true;
    cameraView = window.getDefaultView();
    frameClock.restart();
    backgroundMusic.play();
}

void Game::drawMessage(const std::string& message, float y, unsigned int size)
{
    sf::Text text(font, message, size);
    text.setFillColor(sf::Color::White);
    const sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({ bounds.position.x + bounds.size.x / 2.f,
                     bounds.position.y + bounds.size.y / 2.f });
    text.setPosition({ 450.f, y });
    window.draw(text);
}

void Game::drawInterface()
{
    sf::RectangleShape hudBackground({ 860.f, 48.f });
    hudBackground.setPosition({ 10.f, 8.f });
    hudBackground.setFillColor(sf::Color(15, 20, 35, 205));
    window.draw(hudBackground);

    sf::Text hud(font,
        "COINS: " + std::to_string(world.getScore()) +
        "       LIVES: " + std::to_string(lives) +
        "       WORLD: " + std::to_string(world.getCurrentLevel()) + "/3",
        20);
    hud.setFillColor(sf::Color::White);
    hud.setPosition({ 24.f, 18.f });
    window.draw(hud);

    if (state == GameState::Paused || state == GameState::GameOver ||
        state == GameState::Victory)
    {
        sf::RectangleShape shade({ 900.f, 600.f });
        shade.setFillColor(sf::Color(0, 0, 0, 175));
        window.draw(shade);
    }

    if (state == GameState::Paused)
    {
        drawMessage("PAUSED", 245.f, 48);
        drawMessage("Press P or ENTER to resume", 315.f, 24);
    }
    else if (state == GameState::GameOver)
    {
        drawMessage("GAME OVER", 220.f, 48);
        drawMessage("You lost all 3 lives", 275.f, 24);
        drawMessage(restartSelected ? "> RESTART <" : "RESTART", 355.f, 28);
        drawMessage(!restartSelected ? "> EXIT <" : "EXIT", 405.f, 28);
        drawMessage("Use UP/DOWN and ENTER to select", 475.f, 18);
    }
    else if (state == GameState::Victory)
    {
        drawMessage("YOU WIN!", 220.f, 48);
        drawMessage("You completed all 3 levels!", 285.f, 24);
        drawMessage(restartSelected ? "> PLAY AGAIN <" : "PLAY AGAIN", 370.f, 26);
        drawMessage(!restartSelected ? "> EXIT <" : "EXIT", 425.f, 26);
        drawMessage("Use UP/DOWN and ENTER to select", 485.f, 18);
    }
}

void Game::render()
{
    window.clear(sf::Color::Black);
    window.setView(cameraView);
    world.draw(window);
    player.draw(window);

    window.setView(window.getDefaultView());
    drawInterface();
    window.display();
}
