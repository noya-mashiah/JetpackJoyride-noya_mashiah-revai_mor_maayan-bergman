#include "MovingObject.h"

MovingObject::MovingObject(const GameObjectParams& params)
	: GameObject(params),
	m_animation(m_sprite, params)
{
	scaleSetUp(params._windowScale);
}

void MovingObject::update(const sf::View& view, const float deltaTime)
{
	move(view, deltaTime);            // Move the object (custom logic in derived)
	m_animation.update(deltaTime); // Update animation
}

void MovingObject::render(sf::RenderWindow& window) const
{
	m_animation.render(window);
}

bool MovingObject::isPlaying() const
{
	return m_animation.isPlaying();
}
