#pragma once
#include "Obstacles.h"
#include "GeometryPhysicsUtilities.h"

/*
* Represents an obstacle egg that can kill the player
*/

class Egg : public Obstacles
{
public:
    Egg() = default;
    
    Egg(const GameObjectParams& params);

    void setPosAndScale(const GameObjectParams& params);
    
    void update(const sf::View& view, const float deltaTime) override;
    
    void landed(float deltaTime);
    
    void render(sf::RenderWindow& window) const override;
    
    bool hasLanded() const;

    static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

private:
    
    void setBreakAnimation();

    void playEggSound();

    Animation m_animation;

    float m_velocityY = 0.f;
    bool m_landed = false;
    bool m_break = false;

    static bool m_registerit;
    float m_accelerationY = 1200.f;
};
