#pragma once
#include "Pickables.h"

/*
* Represent a special present of RobotState
*/

class GasTank : public Pickables
{
public:
	GasTank() = default;

	GasTank(const GameObjectParams& params);

	virtual void update(const sf::View& view, const float deltaTime) override;

	static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

	virtual void applyToPlayer(Player& player) override;

private:

	static bool m_registerit;
};
