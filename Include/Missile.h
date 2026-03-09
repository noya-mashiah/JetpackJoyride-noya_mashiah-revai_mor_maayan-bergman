#pragma once
/**
 * Missile.h
 * Defines the Missile enemy class.
 *
 * Missile is an enemy that moves horizontally and displays an alarm before entering the view.
 * Inherits from Enemy and uses a unique_ptr to a MissileAlarm object for warning effects.
 *
 */
#include "Enemy.h"
#include "MissileAlarm.h"

class Missile : public Enemy
{
public:
	Missile() = default;

	Missile(const GameObjectParams& params);

	virtual void update(const sf::View& view, const float deltaTime) override;

	virtual void render(sf::RenderWindow& window) const override;

	static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

	static void playExplodeSound();

private:

	std::unique_ptr<MissileAlarm> m_alarm;
	
	virtual void move(const sf::View& view, const float deltaTime) override;

	void checkNeedToPlaySound(const float viewRightEdge);

	static bool m_registerit;
};
