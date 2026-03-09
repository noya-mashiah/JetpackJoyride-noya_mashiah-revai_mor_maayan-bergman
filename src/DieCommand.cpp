#include "DieCommand.h"

void DieCommand::execute(const sf::View& view, const float deltaTime)
{
    if (!m_isLanding) return;

    // If not yet reached the floor, apply falling physics
    if (m_sprite.getPosition().y < m_floorY)
    {
        sf::Vector2f pos = GeometryPhysicsUtilities::applyVerticalTransition(
            view, m_sprite.getPosition(), m_velocity.y,
            m_gravity, deltaTime, m_floorY, m_isLanding);

        m_sprite.setPosition(pos);
    }
}

bool DieCommand::shouldSwitchToWalk() const
{
	return false;
}
