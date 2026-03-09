#include "Hourglass.h"

// Static member initialization
Hourglass::Hourglass(const GameObjectParams& params)
	: StaticObject(params), m_animation(m_sprite, params)
{
	scaleSetUp(params._windowScale);
}

// Render the hourglass animation (e.g., fixed UI element)
void Hourglass::render(sf::RenderWindow& window) const
{
	auto& view = window.getView();
	window.setView(window.getDefaultView());
	m_animation.render(window);
	window.setView(view);
}

void Hourglass::update(const sf::View& view, const float deltaTime)
{
	(void)view;
	m_animation.update(deltaTime);
}

GameObjectParams Hourglass::getDefaultParams()
{
	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
	return GameObjectParams("Hourglass", { 0.13f, 0.2f },
		sf::Vector2f(windowSize.x * 0.87f, windowSize.y * 0.075f),
		5, 0, 4, 1.f, true);
}

// Restores the hourglass's animation to its default configuration
void Hourglass::reset()
{
	m_animation.setAnimation(Hourglass::getDefaultParams());
}
