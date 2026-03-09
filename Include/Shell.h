#pragma once
#include "Pickables.h"
#include "Animation.h"
#include "Pearl.h"

/*
* Represents a collectible shell that can be picked up by the player
*/

class Shell : public Pickables
{
public:
	Shell() = default;

	Shell(const GameObjectParams& params);

	virtual void update(const sf::View& view, const float deltaTime) override;

	virtual void render(sf::RenderWindow& window) const override;

	static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

	virtual void applyToPlayer(Player& player) override;

	virtual std::vector<std::unique_ptr<Pickables>> addBonusGift(const sf::Vector2f& scrollOffset) const override;

	static void playPickedSound();

private:

	static bool m_registerit;

	Animation m_animation;
};
