#pragma once
#include "Pickables.h"
#include <unordered_map>

/*
* Represents a collectible PowerUpBox that can be picked up by the player
*/

class PowerUpBox : public Pickables
{
public:
	PowerUpBox() = default;

	PowerUpBox(const GameObjectParams& params);

	virtual void update(const sf::View& view, const float deltaTime) override;

	static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

	virtual void applyToPlayer(Player& player) override;

	static void playPickedSound();

private:
	
	static bool m_registerit;

	static int m_curState;
};
