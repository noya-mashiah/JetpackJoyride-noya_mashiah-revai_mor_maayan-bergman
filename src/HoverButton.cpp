#include "HoverButton.h"

HoverButton::HoverButton(const ButtonData& data, std::unique_ptr<CommandButton> command)
	: BaseButton(data, std::move(command)), m_OffTexName(data._offTextureName), 
	  m_OnTexName(data._onTextureName) 
{
    setSound();
}

void HoverButton::update(const sf::RenderWindow& window)
{
    sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);  // Convert to world coordinates based on view
    bool hovered = Collision::singlePixelTest(m_sprite, mousePos, 127); // check collision 

    if (hovered != m_isHovered)
    {
        m_isHovered = hovered;

        std::string tName = (m_isHovered) ? m_OnTexName : m_OffTexName;

        m_sprite.setTexture(ResourcesManager::getInstance().getTexture(tName));
    }
}

void HoverButton::setSound()
{
    m_sound.setBuffer(ResourcesManager::getInstance().getSound("HoverButtonSound"));
    m_soundDuration = 400;
}
