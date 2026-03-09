#include "FlyCommand.h"

void FlyCommand::execute(const sf::View& view, const float deltaTime)
{
    m_velocity.y += m_gravity * deltaTime;

    // If space is pressed, reset vertical velocity (fly upward)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        resetVelocity();

    sf::Vector2f currentPos = m_sprite.getPosition();
    sf::Vector2f newPosition = currentPos;
    newPosition.y += m_velocity.y * deltaTime;

    // Check boundaries
    if (newPosition.y > m_floorY)  // Hit the floor
    {
        newPosition.y = m_floorY;  // Snap to floor
        m_velocity.y = 0.0f;     // Stop falling
    }
    else if (newPosition.y < m_ceilingY)  // Hit the ceiling
    {
        newPosition.y = m_ceilingY;  // Snap to ceiling
        m_velocity.y = 0.0f;       // Stop rising
    }

    newPosition.x = view.getCenter().x - (view.getSize().x / 2) +
                    (GraphicUtilities::getWindowSize().x * playerRelativeX);

    m_sprite.setPosition(newPosition);
}

bool FlyCommand::shouldSwitchToWalk() const
{
    return (m_sprite.getPosition().y >= m_floorY &&
            m_velocity.y == 0.f);
}
