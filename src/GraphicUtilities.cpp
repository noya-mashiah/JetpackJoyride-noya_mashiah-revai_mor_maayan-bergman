#include "GraphicUtilities.h"

// Static member initialization
sf::Vector2f GraphicUtilities::m_windowSize = { 0.f, 0.f };

float GraphicUtilities::m_ceilingY = 0.f;

float GraphicUtilities::m_floorY = 0.f;

float GraphicUtilities::m_wavesY = 0.f;

// Calculates a scale factor to resize a game object proportionally
sf::Vector2f GraphicUtilities::getGameObjectScale(const sf::Vector2f& windowScale, 
                                                  const sf::IntRect& shapeRect)
{
    sf::Vector2f scale;

    scale.x = (m_windowSize.x * windowScale.x) / 
              static_cast<float>(shapeRect.width);
    
    scale.y = (m_windowSize.y * windowScale.y) / 
              static_cast<float>(shapeRect.height);

    return scale;
}

// Calculates scale factors to stretch a background texture to fill the window
sf::Vector2f GraphicUtilities::getBackgroundScale(const std::string& textureName)
{
    const auto& texSize = ResourcesManager::getInstance().getTexture(textureName).getSize();

    if (texSize.x == 0 || texSize.y == 0)
        throw std::runtime_error("Warning: texture '" + textureName + "' has zero size!");

    return {
        m_windowSize.x / static_cast<float>(texSize.x),
        m_windowSize.y / static_cast<float>(texSize.y)
    };
}

void GraphicUtilities::setWindowSize(const sf::Vector2f& size)
{
    m_windowSize = size;

    m_ceilingY = playerRelativeYCeiling * m_windowSize.y;

    m_floorY = playerRelativeYFloor * m_windowSize.y;

    m_wavesY = (float)m_floorY * 0.7f;
}

sf::Vector2f GraphicUtilities::getWindowSize()
{
    return m_windowSize;
}

float GraphicUtilities::getCeilingY()
{
    return m_ceilingY;
}

float GraphicUtilities::getFloorY()
{
    return m_floorY;
}

float GraphicUtilities::getWavesY()
{
    return m_wavesY;
}

// Creates a text object scaled and positioned relative to the window size
sf::Text GraphicUtilities::createNormalizedText(const std::string& str, float yOffSet,
                                                float xOffSet, float fontSizeOffset, sf::Color color)
{
    sf::Text t;
    t.setFont(ResourcesManager::getInstance().getFont());

    float fontSize = m_windowSize.x * fontSizeOffset;
    t.setCharacterSize((unsigned)fontSize);
    t.setOutlineThickness(fontSize * 0.1f);
    t.setOutlineColor(sf::Color::Black);

    // Compute screen-relative position
    float posX = m_windowSize.x * xOffSet;
    float posY = m_windowSize.y * yOffSet;
    t.setPosition(posX, posY);

    t.setFillColor(color);
    t.setString(str);

    return t;
}
