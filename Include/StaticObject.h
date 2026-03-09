#pragma once
#include "GameObject.h"

/*
* an abstract class represent a static object
*/

class StaticObject : public GameObject
{
public:
	StaticObject() = default;

	using GameObject::GameObject;

	virtual ~StaticObject() = default;

	virtual void render(sf::RenderWindow& window) const override;
};
