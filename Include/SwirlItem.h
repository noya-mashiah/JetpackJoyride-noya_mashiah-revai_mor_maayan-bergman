#pragma once
#include "StaticObject.h"
#include "Animation.h"
#include "SoundState.h"

/*
* this represent a swirling item
*/

class SwirlItem : public StaticObject
{
public:
	SwirlItem() = default;

	SwirlItem(const GameObjectParams& params,
		std::function<sf::Vector2f()> getPlayerPos);

	virtual void update(const sf::View& view, const float deltaTime) override;

	virtual void render(sf::RenderWindow& window) const override;

	void setOffset(const float xOffset, const float yOffset);

	void setSound(const std::string& soundName, const bool shouldLoop = false, const float pitch = 1.0f);

	void saveState();

	void restoreState();

	void applyTransparency();

private:

	void randomizeParams();

	void updateSounds();

	Animation m_animation;

	std::function<sf::Vector2f()> m_getPlayerPos;

	// offset from the player
	float m_xOffset = 0.f;

	float m_yOffset = 0.f;

	float m_animRadius = 0.f;
	float m_animSpeed = 0.f;
	float m_animPhase = 0.f;
	bool m_isFigure8 = false;

	SoundState m_soundState;
	bool m_soundPlayedThisCycle = false;
	bool m_isResuming = false;
};
