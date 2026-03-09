#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Consts.h"
#include "GeometryPhysicsUtilities.h"

/*
* an abstract class for the player commands
*/

class PlayerCommand
{
public:
	PlayerCommand() = default;

	PlayerCommand(sf::Sprite& playerSprite, const float gravity = 0.f,
		const float jumpForce = 0.f,
		const float floor = 0.f, const float ceiling = 0.f,
		const sf::Vector2f& velocity = { 0.f, 0.f });

	virtual ~PlayerCommand() = default;

	virtual void execute(const sf::View& view, const float deltaTime) = 0;

	virtual void resetVelocity();

	virtual sf::Vector2f getVelocity() const;

	virtual bool shouldSwitchToWalk() const = 0;

	bool getIsLanding() const;

	void setSpacePressed(bool isPressed);

	virtual int getAnimationPhase() const;

	virtual bool isWalkingOnCeiling() const;

	virtual void startTransition(const float targetY, const float acceleration);

	virtual bool shouldPlaySound();

protected:

	sf::Sprite& m_sprite;

	sf::Vector2f m_velocity = { 0.f, 0.f };

	float m_gravity = 2000.f;

	float m_jumpForce = 0.f; // How strong the upward push is

	float m_floorY = 0.f;

	float m_ceilingY = 0.f;

	bool m_isLanding = true;

	bool m_spacePressed = false;
};

