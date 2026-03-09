#pragma once
#include "BaseButton.h"

/*
* represents an hover button
*/

class HoverButton : public BaseButton
{
public:
	HoverButton(const ButtonData& data, std::unique_ptr<CommandButton> command);

	virtual void update(const sf::RenderWindow& window) override;

private:

	void setSound();

	bool m_isHovered = false;

	std::string m_OnTexName;

	std::string m_OffTexName;
};
