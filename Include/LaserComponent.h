/*
* LaserComponent.h
* Defines the LaserComponent obstacle class.
*
* LaserComponent represents a part of a laser obstacle(beam or head).
* It uses an Animation object for visual effects and provides static functions
* for default parameter generation for different laser parts.
*
* The class is designed to be used as part of a composite laser obstacle.
*/ 
#pragma once

#include "Obstacles.h"
#include "Animation.h"



class LaserComponent : public Obstacles
{
public:
    LaserComponent() = default;

    LaserComponent(const GameObjectParams& params);

    virtual void update(const sf::View& view, const float deltaTime) override;

    virtual void render(sf::RenderWindow& window) const override;

    // Two separate static functions for default params
    static GameObjectParams getLaserBeamDefaultParams(const sf::Vector2f& pos);
    static GameObjectParams getLaserHeadDefaultParams(const sf::Vector2f& pos);

private:
    Animation m_animation;

    static bool m_registerit;
};
