#include "WaveSurfCommand.h"
#include "GeometryPhysicsUtilities.h"
#include "GraphicUtilities.h"
#include <algorithm>

WaveSurfCommand::WaveSurfCommand(sf::Sprite& playerSprite, const float gravity,
    const float jumpForce, const float floor,
    const float ceiling, const sf::Vector2f& velocity)
    : PlayerCommand(playerSprite, gravity, jumpForce, floor, ceiling, velocity)
{
    m_waveY = m_floorY * 0.7f;
}

void WaveSurfCommand::execute(const sf::View& view, const float deltaTime)
{
    float fixedX = view.getCenter().x - view.getSize().x / 2 +
        (GraphicUtilities::getWindowSize().x * playerRelativeX);

    sf::Vector2f currentPos = m_sprite.getPosition();
    currentPos.x = fixedX;

    switch (m_wavePhase)
    {
    case WAVE_IDLE:
        handleIdlePhase(currentPos);
        break;
    case WAVE_DIVING:
        handleDivingPhase(currentPos, deltaTime);
        break;
    case WAVE_ASCENDING:
        handleAscendingPhase(currentPos, deltaTime);
        break;
    case WAVE_DESCENDING:
        handleDescendingPhase(currentPos, deltaTime);
        break;
    }

    m_sprite.setPosition(currentPos);
}

bool WaveSurfCommand::shouldSwitchToWalk() const
{
    return false;
}

int WaveSurfCommand::getAnimationPhase() const
{
    if (m_wavePhase == WAVE_DIVING && m_sprite.getPosition().y >= m_floorY)
        return WAVE_ON_FLOOR;

    return (int)m_wavePhase;
}

// Handles the idle phase of wave surfing
void WaveSurfCommand::handleIdlePhase(sf::Vector2f& currentPos)
{
    currentPos.y = m_waveY;

    if (m_spacePressed)
    {
        m_wavePhase = WAVE_DIVING;
        m_startDiveY = currentPos.y;
        m_currentVerticalSpeed = DIVE_VELOCITY;
    }
}

void WaveSurfCommand::handleDivingPhase(sf::Vector2f& currentPos, const float deltaTime)
{
    currentPos.y += m_currentVerticalSpeed * deltaTime; // Move the player downwards.

    // Clamp the player's Y position at m_floorY (cannot go below the floor).
    if (currentPos.y >= m_floorY)
    {
        currentPos.y = m_floorY;

        // If spacebar is still pressed, player stays at the floor.
        if (!m_spacePressed)
        {
            // Spacebar released while at or below floor, initiate ascent to ceiling.
            m_wavePhase = WAVE_ASCENDING;
            m_diveDistance = m_floorY - m_waveY; // Max dive distance achieved
            m_peakY = m_ceilingY; // Special case: jump to ceiling if dove to floor
            m_currentVerticalSpeed = -ASCEND_VELOCITY; // Set upward speed (negative Y)
        }
    }
    else if (!m_spacePressed)
    {
        // Spacebar released before hitting the floor, initiate ascent based on dive distance.
        m_wavePhase = WAVE_ASCENDING;
        m_diveDistance = currentPos.y - m_waveY; // Calculate actual dive distance
        m_peakY = m_waveY - m_diveDistance; // Calculate peak Y as reflection above wave line
        // Ensure peakY does not go below the ceiling boundary.
        if (m_peakY < m_ceilingY) m_peakY = m_ceilingY;
        m_currentVerticalSpeed = -ASCEND_VELOCITY; // Set upward speed (negative Y)
    }
}

void WaveSurfCommand::handleAscendingPhase(sf::Vector2f& currentPos, const float deltaTime)
{
    currentPos.y += m_currentVerticalSpeed * deltaTime; // Move the player upwards.

    // Check if peak Y has been reached or surpassed.
    if (currentPos.y <= m_peakY)
    {
        currentPos.y = m_peakY; // Snap to peak Y
        m_wavePhase = WAVE_DESCENDING; // Transition to descending
        m_currentVerticalSpeed = DESCENT_VELOCITY; // Set downward speed (positive Y)
    }
}

void WaveSurfCommand::handleDescendingPhase(sf::Vector2f& currentPos, const float deltaTime)
{
    currentPos.y += m_currentVerticalSpeed * deltaTime; // Move the player downwards back towards the wave line.

    // Check if the player has reached or passed the wave line.
    if (currentPos.y >= m_waveY)
    {
        currentPos.y = m_waveY; // Snap to wave line
        m_wavePhase = WAVE_IDLE; // Transition back to idle state
        m_currentVerticalSpeed = 0.f; // Stop vertical movement
    }
}
