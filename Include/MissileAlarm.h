#pragma once
#include "StaticObject.h"
#include "Animation.h"
#include "GameObjectFactory.h"

/*
* Represnt a static object - an alarm before a missile incoming
*/

class MissileAlarm : public StaticObject
{
public:
	MissileAlarm() = default;

	MissileAlarm(const GameObjectParams& params);

	virtual void update(const sf::View& view, const float deltaTime) override;

	virtual void render(sf::RenderWindow& window) const;

	static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

	void setIsVisible(const bool visible);

	void changeAlarmState();

private:

	void scaleInit();

	void playAlarmSound();

	void checkNeedToPlaySound();

	bool m_playedAlready = false;

	Animation m_animation;

	static bool m_registerit;

	bool m_visible = true;

	sf::Vector2f m_windowScale;
};
