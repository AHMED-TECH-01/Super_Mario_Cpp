#include "Player.h"\n#include <cmath>

namespace
{
    const float PLAYER_SPEED = 280.f;
    const float GRAVITY = 1500.f;
    const float JUMP_SPEED = -620.f;
    const float HISTORY_INTERVAL = 0.10f;
    const float REWIND_INTERVAL = 0.05f;
}

Player::Player()
    : velocity(0.f, 0.f), onGround(false), questionBlockHit(false),
      animationTimer(0.f), animationFrame(0),
      historyTimer(0.f), rewindTimer(0.f)
{
    texture.loadFromFile("Assets/player_sprites.png");
    texture.setSmooth(false);

    body.setSize({ 40.f, 50.f });
    body.setTexture(&texture);
    body.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 24 }));
    body.setPosition({ 60.f, 500.f });
}

void Player::update(float deltaTime,
                    const std::vector<sf::RectangleShape>& platforms,
                    const std::vector<sf::RectangleShape>& questionBlocks)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
    {
        rewindTimer += deltaTime;
        if (rewindTimer >= REWIND_INTERVAL && !positionHistory.empty())
        {
            body.setPosition(positionHistory.top());
            positionHistory.pop();
            velocity = { 0.f, 0.f };
            rewindTimer = 0.f;
        }
        return;
    }

    rewindTimer = 0.f;

    historyTimer += deltaTime;
    if (historyTimer >= HISTORY_INTERVAL)
    {
        positionHistory.push(body.getPosition());
        historyTimer = 0.f;
    }

    velocity.x = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        velocity.x = -PLAYER_SPEED;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        velocity.x = PLAYER_SPEED;

    velocity.y += GRAVITY * deltaTime;

    const sf::Vector2f oldPosition = body.getPosition();
    body.move({ velocity.x * deltaTime, velocity.y * deltaTime });

    // Hitting a question block from below stops the jump and activates it.
    if (velocity.y < 0.f)
    {
        for (const auto& block : questionBlocks)
        {
            if (body.getGlobalBounds().findIntersection(block.getGlobalBounds()))
            {
                const float oldTop = oldPosition.y;
                const float blockBottom = block.getPosition().y + block.getSize().y;
                if (oldTop >= blockBottom - 5.f)
                {
                    body.setPosition({ body.getPosition().x, blockBottom });
                    velocity.y = 0.f;
                    questionBlockHit = true;
                    break;
                }
            }
        }
    }

    onGround = false;
    for (const auto& platform : platforms)
    {
        const auto overlap = body.getGlobalBounds().findIntersection(
            platform.getGlobalBounds());

        if (overlap && velocity.y >= 0.f)
        {
            const float oldBottom = oldPosition.y + body.getSize().y;
            const float platformTop = platform.getPosition().y;

            if (oldBottom <= platformTop + 5.f)
            {
                body.setPosition({ body.getPosition().x,
                                   platformTop - body.getSize().y });
                velocity.y = 0.f;
                onGround = true;
            }
        }
    }

    // Question blocks can also be stood on.
    for (const auto& block : questionBlocks)
    {
        const auto overlap = body.getGlobalBounds().findIntersection(block.getGlobalBounds());
        if (overlap && velocity.y >= 0.f)
        {
            const float oldBottom = oldPosition.y + body.getSize().y;
            const float blockTop = block.getPosition().y;
            if (oldBottom <= blockTop + 5.f)
            {
                body.setPosition({ body.getPosition().x, blockTop - body.getSize().y });
                velocity.y = 0.f;
                onGround = true;
            }
        }
    }

    if (body.getPosition().x < 0.f)
        body.setPosition({ 0.f, body.getPosition().y });

    // Two-frame running animation, with a separate jump frame.
    if (velocity.y < -20.f || velocity.y > 20.f)
        body.setTextureRect(sf::IntRect({ 48, 0 }, { 16, 24 }));
    else if (std::abs(velocity.x) > 0.f)
    {
        animationTimer += deltaTime;
        if (animationTimer >= 0.14f)
        {
            animationFrame = 1 - animationFrame;
            animationTimer = 0.f;
        }
        body.setTextureRect(sf::IntRect({ animationFrame == 0 ? 16 : 32, 0 },
                                        { 16, 24 }));
    }
    else
        body.setTextureRect(sf::IntRect({ 0, 0 }, { 16, 24 }));
}

bool Player::jump()
{
    if (onGround)
    {
        velocity.y = JUMP_SPEED;
        onGround = false;
        return true;
    }
    return false;
}

void Player::draw(sf::RenderWindow& window) const
{
    window.draw(body);
}

void Player::reset(sf::Vector2f startPosition)
{
    body.setPosition(startPosition);
    velocity = { 0.f, 0.f };
    onGround = false;
    questionBlockHit = false;
    animationTimer = 0.f;
    historyTimer = 0.f;
    rewindTimer = 0.f;
    positionHistory = std::stack<sf::Vector2f>();
}

bool Player::consumeQuestionBlockHit()
{
    const bool result = questionBlockHit;
    questionBlockHit = false;
    return result;
}

sf::FloatRect Player::getBounds() const { return body.getGlobalBounds(); }
sf::Vector2f Player::getPosition() const { return body.getPosition(); }
