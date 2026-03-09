#include "LaserObstacle.h"

LaserObstacle::LaserObstacle(std::unique_ptr<LaserComponent> top, std::unique_ptr<LaserComponent> bottom,
	std::unique_ptr<LaserComponent> beam)
	: Obstacles(GameObjectParams{}),
	m_top(std::move(top)),
	m_bottom(std::move(bottom)),
	m_beam(std::move(beam)) {}

void LaserObstacle::update(const sf::View& view, const float deltaTime)
{
	m_beam->update(view, deltaTime);
	m_top->update(view, deltaTime);
	m_bottom->update(view, deltaTime);
}

void LaserObstacle::render(sf::RenderWindow& window) const
{
	m_beam->render(window);
	m_top->render(window);
	m_bottom->render(window);
}

bool LaserObstacle::isOutOfWindowView(const sf::View& view) const
{
	return (m_bottom->isOutOfWindowView(view) && 
			m_top->isOutOfWindowView(view));
}

/**
 *  Checks collision with any part of the laser obstacle
 * param objectBounds The bounds of the object to check collision with
 * return True if collision occurs with any component (top, bottom, or beam)
 */
bool LaserObstacle::isCollidedWith(const sf::FloatRect& objectBounds) const
{
	return (m_top->isCollidedWith(objectBounds) || 
			m_bottom->isCollidedWith(objectBounds) ||
			m_beam->isCollidedWith(objectBounds));
}

const sf::Sprite& LaserObstacle::getSprite() const
{
	return m_beam->getSprite();
}

void LaserObstacle::playZappSound()
{
	static sf::Sound sound;
	sound.setBuffer(ResourcesManager::getInstance().getSound("ZapperSound"));
	sound.setVolume(90);
	sound.play();
}
