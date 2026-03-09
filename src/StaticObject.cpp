#include "StaticObject.h"

void StaticObject::render(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}
