#pragma once
/**
 *  Shark.h
 * Defines the Shark enemy class.
 *
 * Shark is a fast-moving aquatic enemy with a bite sound effect.
 *
 */
#include "Enemy.h"

class Shark :public Enemy
{
public:
	Shark() = default;

	Shark(const GameObjectParams& params);

	virtual void update(const sf::View& view, const float deltaTime) override;

	static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

	static void playBiteSound();

private:
	virtual void move(const sf::View& view, const float deltaTime) override;

	void checkNeedToPlaySound(const sf::View& view);

	static bool m_registerit;
};
