#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "Consts.h"

// * GraphicUtilities Class
// * ----------------------
// * A static utility class for managing and querying window-related graphics data.
//
// * Functionality:
// * --------------
// * - Computes dynamic scaling for game objects and backgrounds based on window size.
// * - Provides global layout measurements such as:
// *     - Ceiling Y position
// *     - Floor Y position
// *     - Wave level height
// * - Creates responsive text elements scaled to the window resolution.
//
// * Purpose:
// * --------
// * To centralize logic for resolution-independent rendering and layout,
// * ensuring consistent visual scaling across all screen sizes.

class GraphicUtilities
{
public:
	static sf::Vector2f getGameObjectScale(const sf::Vector2f& windowScale,
										   const sf::IntRect& shapeRect);

	// Updated: scale for backgrounds to fit the window (stretch to fit, may distort aspect ratio)
	static sf::Vector2f getBackgroundScale(const std::string& textureName);

	static void setWindowSize(const sf::Vector2f& size);

	static sf::Vector2f getWindowSize();

	static float getCeilingY();
	
	static float getFloorY();

	static float getWavesY();

	static sf::Text createNormalizedText(
		const std::string& str,
		float yOffSet,
		float xOffSet,
		float fontSizeOffset = 0.035f,
		sf::Color color = sf::Color::White
	);

private:

	static float m_ceilingY;

	static float m_floorY;

	static float m_wavesY;

	static sf::Vector2f m_windowSize;
};
