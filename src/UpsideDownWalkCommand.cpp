#include "UpsideDownWalkCommand.h"
#include "GraphicUtilities.h"

void UpsideDownWalkCommand::execute(const sf::View& view, const float deltaTime)
{
    float fixedX = view.getCenter().x - view.getSize().x / 2 +
        (GraphicUtilities::getWindowSize().x * playerRelativeX);

    if (m_isTransitioning)
    {
        // Apply vertical motion during floor-ceiling transition
        sf::Vector2f pos = GeometryPhysicsUtilities::applyVerticalTransition(view,
            m_sprite.getPosition(), m_velocityY, m_accelerationY,
            deltaTime, m_targetY, m_isTransitioning);

        // If transition ended, update ceiling state flag
        if (!m_isTransitioning)
            m_onCeiling = (m_targetY == GraphicUtilities::getCeilingY());

        m_sprite.setPosition(pos);
    }
    else
    {
        float fixedY = m_onCeiling ? GraphicUtilities::getCeilingY()
                                    : GraphicUtilities::getFloorY();
        m_sprite.setPosition(fixedX, fixedY);
    }
}

// Initiates a vertical transition between floor and ceiling
void UpsideDownWalkCommand::startTransition(const float targetY, const float acceleration)
{
    m_isTransitioning = true;
    m_targetY = targetY;
    m_velocityY = 0.f;
    m_accelerationY = acceleration;
    m_floorY = GraphicUtilities::getFloorY();
    m_ceilingY = GraphicUtilities::getCeilingY();

    auto scale = m_sprite.getScale();
    m_sprite.setScale(scale.x, -scale.y); // flip

    m_onCeiling = (targetY == GraphicUtilities::getCeilingY());
}

bool UpsideDownWalkCommand::isWalkingOnCeiling() const
{
    return m_onCeiling;
}

bool UpsideDownWalkCommand::shouldSwitchToWalk() const
{
    return !m_isTransitioning;
}
