#pragma once
#include "GameObject.h"

/**
 *  Base class for objects that can move and have animations
 *
 * The MovingObject class serves as a base for all game objects that need
 * both movement capabilities and animation support. It provides a common
 * interface for updating position and rendering animated sprites.
 * Derived classes must implement their own movement logic through the
 * pure virtual move() function.
 */

class MovingObject : public GameObject
{
public:
    MovingObject() = default;

    MovingObject(const GameObjectParams& params);

    virtual ~MovingObject() = default;

    virtual void update(const sf::View& view, const float deltaTime) override;

    virtual void render(sf::RenderWindow& window) const override;

    virtual bool isPlaying() const;

protected:

    virtual void move(const sf::View& view, const float deltaTime) = 0;
    
    Animation m_animation;
};
