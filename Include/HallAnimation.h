/**
 *  HallAnimation.h
 *  Handles the animated hall background and its sound effect.
 *
 * The HallAnimation class manages the animation and sound for the hall background,
 * including updating frames, playing sound once, and resetting the animation.
 * Inherits from StaticObject.
 */
#pragma once
#include "StaticObject.h"

class HallAnimation : public StaticObject
{
public:
	HallAnimation() = default;

	HallAnimation(const GameObjectParams& params);

	virtual void update(const sf::View& view, const float deltaTime) override;

	//virtual void render(sf::RenderWindow& window) const override;

	static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

	void reset();

private:

	void soundInit();

	void checkNeedToPlaySound();

	Animation m_animation;

	sf::Sound m_sound;

	bool m_playedSound = false;
};
