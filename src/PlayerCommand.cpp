#include "PlayerCommand.h"

PlayerCommand::PlayerCommand(sf::Sprite& playerSprite, const float gravity,
	const float jumpForce, const float floor,
	const float ceiling, const sf::Vector2f& velocity)
	: m_sprite(playerSprite), m_gravity(gravity), m_jumpForce(jumpForce),
	m_floorY(floor), m_ceilingY(ceiling),
	m_velocity(velocity) {}

void PlayerCommand::resetVelocity()
{
	m_velocity.y = m_jumpForce;
}

sf::Vector2f PlayerCommand::getVelocity() const
{
	return m_velocity;
}

bool PlayerCommand::getIsLanding() const
{
	return m_isLanding;
}

void PlayerCommand::setSpacePressed(bool isPressed)
{
	m_spacePressed = isPressed;
}

int PlayerCommand::getAnimationPhase() const { return 0; }

bool PlayerCommand::isWalkingOnCeiling() const { return false; }

void PlayerCommand::startTransition(float targetY, float acceleration)
{ (void)targetY; (void)acceleration; }

bool PlayerCommand::shouldPlaySound() { return false; }
