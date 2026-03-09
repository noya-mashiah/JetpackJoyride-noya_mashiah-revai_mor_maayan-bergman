#pragma once
#include "StaticObject.h"
#include "Animation.h"

/*
* represent the lamp on the wall of the game
*/

class WallLamp : public StaticObject
{
public:
	WallLamp() = default;

	WallLamp(const GameObjectParams& params);

	virtual void update(const sf::View& view, const float deltaTime) override;

	virtual void render(sf::RenderWindow& window) const override;

	static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

private:
	Animation m_animation;

	static bool m_registerit;
};
