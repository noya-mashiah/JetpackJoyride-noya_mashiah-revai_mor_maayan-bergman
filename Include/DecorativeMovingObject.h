#pragma once
#include "MovingObject.h"

/**
 * @brief A decorative object that moves autonomously in the game world
 *
 * The DecorativeMovingObject class represents background elements like scientists,
 * fish, and other decorative characters that move independently to add life
 * to the game environment. These objects have random movement patterns and
 * can face different directions based on their position.
 */

class DecorativeMovingObject : public MovingObject
{
public:
    DecorativeMovingObject() = default;

    DecorativeMovingObject(const GameObjectParams& params);

    // Static default params for each type
    static GameObjectParams getScientistDefaultParams(const sf::Vector2f& pos);
    static GameObjectParams getScientistSeaDefaultParams(const sf::Vector2f& pos);
    static GameObjectParams getFishDefaultParams(const sf::Vector2f& pos);

private:
    void updatePictureDirection();
    void applyTransparency(const std::string& textureName);
    virtual void move(const sf::View& view, const float deltaTime) override;

    static bool m_registerIt;
    bool m_isFacingRight = false;
    float m_speed = 0.f;
};
