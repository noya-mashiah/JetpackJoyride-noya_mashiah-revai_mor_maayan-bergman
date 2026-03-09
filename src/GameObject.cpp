#include "GameObject.h"

GameObject::GameObject(const GameObjectParams& params)
{
	spriteInit(params._textureName, params._position);
}

bool GameObject::isOutOfWindowView(const sf::View& view) const
// Returns true if the object is outside the left edge of the view.
{
	float objectRightEdge = m_sprite.getGlobalBounds().left + 
							m_sprite.getGlobalBounds().width;

	float viewLeftEdge = view.getCenter().x - view.getSize().x / 2;

	return objectRightEdge < viewLeftEdge;
}

void GameObject::rotateSprite(const float angle)
{
	m_sprite.rotate(angle);
}

sf::FloatRect GameObject::getLocalBounds() const
{
	return m_sprite.getLocalBounds();
}

sf::FloatRect GameObject::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

bool GameObject::isCollidedWith(const sf::FloatRect& objectBounds) const
{
	return getGlobalBounds().intersects(objectBounds);
}

sf::Vector2f GameObject::getPosition() const
{
	return m_sprite.getPosition();
}

void GameObject::setScale(const sf::Vector2f& scale)
{
	m_sprite.setScale(scale);
}

const sf::Sprite& GameObject::getSprite() const
{
	return m_sprite;
}

sf::Vector2f GameObject::getScaledSize() const
{
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	return sf::Vector2f(bounds.width, bounds.height);
}

void GameObject::spriteInit(const std::string& textureName, const sf::Vector2f& position)
{
	ResourcesManager& inst = ResourcesManager::getInstance();

	if (textureName != " ")
		m_sprite.setTexture(inst.getTexture(textureName));

	m_sprite.setPosition(position);
}

void GameObject::scaleSetUp(const sf::Vector2f& windowScale)
// Sets up the sprite's scale and origin based on the window scale.
{
	setScale(GraphicUtilities::getGameObjectScale(windowScale,
		m_sprite.getTextureRect()));

	m_sprite.setOrigin(
		m_sprite.getLocalBounds().width / 2,
		m_sprite.getLocalBounds().height / 2
	);
}
