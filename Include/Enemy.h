#pragma once
/**
 *  Enemy.h
 *  Abstract base class for all enemy types in the game.
 *
 * Enemy provides a common interface and shared functionality for all enemy objects,
 * such as sound management and movement. All specific enemy types (Bat, Chicken, Shark...)
 * should inherit from this class and implement their own movement and rendering logic..
 */
#include "MovingObject.h"

class Enemy : public MovingObject
{
public:
	Enemy() = default;

	using MovingObject::MovingObject;

	virtual ~Enemy() = default;

protected:

	void soundInit(const std::string& soundName, const bool shouldLoop = false, const float volume = 50);

	void checkNeedToPlaySound(const float objPos, const float limitPos);

	bool m_playedSound = false;

	sf::Sound m_sound;
};
