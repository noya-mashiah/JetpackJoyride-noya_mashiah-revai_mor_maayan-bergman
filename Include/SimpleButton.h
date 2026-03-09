#pragma once
#include "BaseButton.h"

/*
* represent a simple button
*/

class SimpleButton : public BaseButton
{
public:
	using BaseButton::BaseButton;

	virtual void update(const sf::RenderWindow& window) override;
};
