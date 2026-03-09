/**
 * LaserObstacle.h
 *Defines the LaserObstacle composite obstacle class.
 *
 * LaserObstacle represents a complete laser barrier in the game, composed of multiple LaserComponent parts:
 * a top, bottom, and beam segment. It inherits from Obstacles and manages the update, rendering,
 * collision detection, and sound logic for the entire laser obstacle.
 *
 * Uses composition (unique_ptrs to LaserComponent) to allow flexible construction and management of the laser's parts.
*/
#pragma once

#include "LaserConfig.h"
#include "LaserComponent.h"



class LaserObstacle : public Obstacles
{
public:
	LaserObstacle() = default;

	LaserObstacle(std::unique_ptr<LaserComponent> top, std::unique_ptr<LaserComponent> bottom,
		std::unique_ptr<LaserComponent> beam);

	virtual void update(const sf::View& view, const float deltaTime) override;

	virtual void render(sf::RenderWindow& window) const override;

	virtual bool isOutOfWindowView(const sf::View& view) const override;

	virtual bool isCollidedWith(const sf::FloatRect& objectBounds) const override;

	virtual const sf::Sprite& getSprite() const override;

	void playZappSound();

private:

	std::unique_ptr<LaserComponent> m_top;
	std::unique_ptr<LaserComponent> m_bottom;
	std::unique_ptr<LaserComponent> m_beam;
};
