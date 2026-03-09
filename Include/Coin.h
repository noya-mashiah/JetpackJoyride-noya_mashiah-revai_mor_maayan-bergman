#pragma once
#include "Pickables.h"
#include "Animation.h"

/*
* Represents a collectible coin that can be picked up by the player
*/

class Coin : public Pickables
{
public:
	Coin() = default;

	Coin(const GameObjectParams& params);

	virtual void update(const sf::View& view, const float deltaTime) override;

	virtual void render(sf::RenderWindow& window) const override;

	static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

	virtual void applyToPlayer(Player& player) override;

	static sf::Vector2f getSize(const sf::Vector2f& windowScale);


private:
	Animation m_animation;

	static bool m_registerit;
};
