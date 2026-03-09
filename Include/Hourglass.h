#pragma once
#include "StaticObject.h"
#include "Animation.h"

/*
* Represnt a static object - an HourGlass 
*/

class Hourglass : public StaticObject
{
public:

	Hourglass(const GameObjectParams& params);

	virtual void render(sf::RenderWindow& window) const override;

	virtual void update(const sf::View& view, const float deltaTime) override;

	static GameObjectParams getDefaultParams();

	void reset();

private:

	Animation m_animation;
};
