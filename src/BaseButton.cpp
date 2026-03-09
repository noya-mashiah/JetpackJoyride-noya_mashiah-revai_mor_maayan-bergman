#include "BaseButton.h"

BaseButton::BaseButton(const ButtonData& data, std::unique_ptr<CommandButton> command)
	: m_command(std::move(command))
{
	spriteInit(data);
	soundInit();
}

void BaseButton::render(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

void BaseButton::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		// Convert mouse position to world coordinates
		sf::Vector2f mousePos = window.mapPixelToCoords({ event.mouseButton.x,
														event.mouseButton.y });

		// If mouse overlaps sprite pixels (non-transparent), register click
		if (Collision::singlePixelTest(m_sprite, mousePos, PixelAlphaLimit))
			m_click = true;
		executeClick();
	}
}

// flip horizontally 
void BaseButton::flipScale()
{
	sf::Vector2f scale = m_sprite.getScale();
	m_sprite.setScale(-scale.x, scale.y);
}

void BaseButton::setCommand(std::unique_ptr<CommandButton> newCommand)
{
	m_command = std::move(newCommand);
}

void BaseButton::soundInit()
{
	m_sound.setBuffer(ResourcesManager::getInstance().getSound("ButtonSound"));
	m_sound.setVolume(ButtonSoundVolume);
}

void BaseButton::playSound()
{
	m_sound.play();
	std::this_thread::sleep_for(std::chrono::milliseconds(m_soundDuration));
}

void BaseButton::executeClick()
{
	if (m_command && m_click)
	{
		playSound();
		m_command->execute();
		m_click = false;
	}
}

bool BaseButton::isClickedOn()
{
	return m_click;
}

void BaseButton::setPosition(const sf::Vector2f& pos)
{
	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

	float xPos = pos.x * windowSize.x;
	float yPos = pos.y * windowSize.y;

	m_sprite.setPosition(xPos, yPos);
}

void BaseButton::spriteInit(const ButtonData& data)
{
	setPosition(data._pos);
	m_sprite.setTexture(ResourcesManager::getInstance().getTexture(data._offTextureName));
	m_sprite.setScale(GraphicUtilities::getGameObjectScale(data._windowScale,
		m_sprite.getTextureRect()));
}
