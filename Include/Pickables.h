#pragma once
#include "StaticObject.h"
class Player;

/*
* abstract class represnts a pickable object in the game
*/

class Pickables : public StaticObject
{
public:
	Pickables() = default;

	using StaticObject::StaticObject;

	virtual ~Pickables() = default;

	virtual void applyToPlayer(Player& player) = 0;

	virtual std::vector<std::unique_ptr<Pickables>> addBonusGift(const sf::Vector2f& scrollOffset) const;

	static void playPickupSound();

	static void playPickupSoundSpecialGift();

	static void stopSpecialGiftSound();

private:
	static sf::Sound m_specialGiftSound;
};
