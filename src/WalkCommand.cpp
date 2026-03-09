#include "WalkCommand.h"

void WalkCommand::execute(const sf::View& view, const float deltaTime)
{
	(void)deltaTime;
	float fixedPlayerX = view.getCenter().x - (view.getSize().x / 2) +
			(GraphicUtilities::getWindowSize().x * playerRelativeX);

	m_sprite.setPosition(fixedPlayerX, m_sprite.getPosition().y);
}

bool WalkCommand::shouldSwitchToWalk() const
{
	return false;
}
