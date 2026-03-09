#pragma once
#include "ResourcesManager.h"
#include "GraphicUtilities.h"

/*
* in charge of the infobar of the game
*/

class InfoBar
{
public:
	InfoBar();

	void render(sf::RenderWindow& window) const;

	void update(const float distance, const int cointsAmout);

private:

	sf::Text m_coinsCounter;
	sf::Text m_distanceCounter;
};
