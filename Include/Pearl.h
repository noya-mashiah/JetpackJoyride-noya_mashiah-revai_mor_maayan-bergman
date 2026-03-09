#pragma once
#include "Pickables.h"

/*
* Represents a collectible Pearl that can be picked up by the player 
*/

class Pearl : public Pickables
{
public:
	Pearl() = default;

	Pearl(const GameObjectParams& params);

	virtual void update(const sf::View& view, const float deltaTime) override;

	static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

	virtual void applyToPlayer(Player& player) override;

	static sf::Vector2f getSize(const sf::Vector2f& windowScale);

private:

	static bool m_registerit;
};
