#include "JumpCommand.h"

void JumpCommand::execute(const sf::View& view, const float deltaTime)
{
    handleJumpInput();
    applyGravity(deltaTime);
    updatePosition(view, deltaTime);
    handleLanding();
    clampToCeiling();
}

void JumpCommand::handleJumpInput()
{
    bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if (spacePressed && !m_spaceWasPressed && m_jumpsLeft > 0)
    {
        m_velocity.y = -m_jumpHeight;
        m_isJumping = true;
        m_jumpsLeft--;
        m_justJumped = true;
    }

    m_spaceWasPressed = spacePressed;
}

void JumpCommand::applyGravity(const float deltaTime)
{
    m_velocity.y += m_gravity * deltaTime;
}

void JumpCommand::updatePosition(const sf::View& view, const float deltaTime)
{
    sf::Vector2f pos = m_sprite.getPosition();
    pos.y += m_velocity.y * deltaTime;

    // Horizontal position logic (keep X centered relative to view)
    pos.x = view.getCenter().x - (view.getSize().x / 2) +
        (GraphicUtilities::getWindowSize().x * playerRelativeX);

    m_sprite.setPosition(pos);
}

void JumpCommand::handleLanding()
{
    sf::Vector2f pos = m_sprite.getPosition();
    if (pos.y >= m_floorY)  // check reached or passed the floor
    {
        pos.y = m_floorY;
        m_velocity.y = 0.f;
        m_isJumping = false;
        m_jumpsLeft = m_maxJumps; // Reset jumps when landing
        m_sprite.setPosition(pos);
    }
}

// Prevents the sprite from passing above the ceiling by clamping its position
void JumpCommand::clampToCeiling()
{
    sf::Vector2f pos = m_sprite.getPosition();
    if (pos.y < m_ceilingY)
    {
        pos.y = m_ceilingY;
        m_velocity.y = 0.f;
        m_sprite.setPosition(pos);
    }
}

bool JumpCommand::shouldSwitchToWalk() const
{
    return (m_sprite.getPosition().y >= m_floorY && m_velocity.y == 0.f);
}

bool JumpCommand::shouldPlaySound()
{
    if (m_justJumped)
    {
        m_justJumped = false;
        return true;
    }

    return false;
}
