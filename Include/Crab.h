#pragma once
/**
 *  Crab.h
 *  Defines the Crab enemy class.
 *
 * Crab is a ground enemy with a unique pinch sound effect.
 * Inherits from Enemy and implements its own movement and sound logic.
 */
#include "Enemy.h"

class Crab :public Enemy
{
public:
    Crab() = default;

	Crab(const GameObjectParams& params);

    virtual void update(const sf::View& view, const float deltaTime) override;

    static GameObjectParams getDefaultParams(const sf::Vector2f& pos);

    static void playPinchSound();

private:

    virtual void move(const sf::View& view, const float deltaTime) override;

    void checkNeedToPlaySound(const sf::View& view);

    static bool m_registerit;

    float m_moveSpeed = 100.f;
};
