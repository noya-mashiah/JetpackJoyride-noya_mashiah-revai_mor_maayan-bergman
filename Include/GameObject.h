/**
 *  GameObject.h
 *  Abstract base class for all game objects in the game world.
 *
 * The GameObject class defines the interface and shared logic for all interactive and drawable objects,
 * including rendering, updating, collision detection, and sprite management.
 *
 *  Provides utility functions for sprite setup, scaling, and position handling.
 */
#pragma once 
#include <functional>
#include "Consts.h"
#include "Animation.h"
#include "GameObjectParams.h"
#include "GameObjectFactory.h"

class GameObject
{
public:
	GameObject() = default;

	GameObject(const GameObjectParams& params);

	virtual ~GameObject() = default;

	virtual void render(sf::RenderWindow& window) const = 0;

	virtual void update(const sf::View& view, const float deltaTime) = 0;

	virtual bool isOutOfWindowView(const sf::View& view) const;

	void rotateSprite(const float angle);

	sf::FloatRect getLocalBounds() const;

	sf::FloatRect getGlobalBounds() const;

	virtual bool isCollidedWith(const sf::FloatRect& objectBounds) const;

	sf::Vector2f getPosition() const;

	void setScale(const sf::Vector2f& scale);

	virtual const sf::Sprite& getSprite() const;

	virtual sf::Vector2f getScaledSize() const;

protected:

	void spriteInit(const std::string& textureName, const sf::Vector2f& position);

	void scaleSetUp(const sf::Vector2f& windowScale);

	sf::Sprite m_sprite;
};
