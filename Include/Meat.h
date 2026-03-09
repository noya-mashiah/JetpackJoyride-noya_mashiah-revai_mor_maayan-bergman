#pragma once
#include "Pickables.h"

/*
* Represents a special gift for DinosaurState
*/

class Meat : public Pickables
{
public:

	Meat() = default;

	Meat(const GameObjectParams& params);

	virtual void update(const sf::View& view, const float deltaTime) override;

	static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

	virtual void applyToPlayer(Player& player) override;

private:

	static bool m_registerit;
};
