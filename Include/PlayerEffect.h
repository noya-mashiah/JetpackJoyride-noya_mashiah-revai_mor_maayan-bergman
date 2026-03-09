/**
 * PlayerEffect.h
 *  Visual effect attached to the player (e.g., sparkles, flames, wings).
 *
 * The PlayerEffect class represents a visual effect that follows the player,
 * such as sparkles, flames, or wings. Handles animation, position offset, and optional visibility logic.
 * Inherits from StaticObject.
 */
#pragma once
#include "StaticObject.h"
#include "Animation.h"

/**
 * @brief Visual effects that follow and enhance the player's appearance
 *
 * The PlayerEffect class represents animated visual effects like sparkles,
 * flames, dinosaur wings, and fire that follow the player at specific
 * offset positions. These effects enhance the visual appeal and provide
 * feedback about the player's current state or power-ups.
 */

class PlayerEffect : public StaticObject
{
public:
    PlayerEffect() = default;

    PlayerEffect(const GameObjectParams& params,
        std::function<sf::Vector2f()> getPlayerPos,
        float xOffset = 0.f, float yOffset = 0.f,
        bool useVisibilityLogic = false);

    virtual void update(const sf::View& view, const float deltaTime) override;

    virtual void render(sf::RenderWindow& window) const override;

    // Four separate static functions for default params
    static GameObjectParams getSparkleDefaultParams(const sf::Vector2f& pos);
    static GameObjectParams getFlameDefaultParams(const sf::Vector2f& pos);
    static GameObjectParams getDinoWingsDefaultParams(const sf::Vector2f& pos);
    static GameObjectParams getDinoFireDefaultParams(const sf::Vector2f& pos);

    void setOffset(float xOffset, float yOffset);

    void setIsVisible(const bool isVisible);

private:
    Animation m_animation;
    std::function<sf::Vector2f()> m_getPlayerPos; // Function to get current player position

    // offset from the player
    float m_xOffset = 0.f;
    float m_yOffset = 0.f;

    // Visibility logic
    bool m_useVisibilityLogic = false; // chose to have it for a multy purpose class
    bool m_visible = true;
};
