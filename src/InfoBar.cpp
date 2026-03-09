#include "InfoBar.h"

InfoBar::InfoBar()
{
	m_distanceCounter = GraphicUtilities::createNormalizedText("Distance: 0M", 0.01f, 0.01f, 0.022f);
	m_coinsCounter = GraphicUtilities::createNormalizedText("COINS: 0", 0.07f, 0.01f, 0.022f);
}

void InfoBar::render(sf::RenderWindow& window) const
{
	window.draw(m_distanceCounter);
	window.draw(m_coinsCounter);
}

void InfoBar::update(const float distance, const int cointsAmout)
{
	m_distanceCounter.setString("Distance: " + std::to_string((int)distance / 100) + "M");
	m_coinsCounter.setString("COINS: " + std::to_string(cointsAmout));
}
