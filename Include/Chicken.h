#pragma once
/**
 * Chicken.h
 * Defines the Chicken enemy class.
 *
 * Chicken is an enemy that can drop eggs at specific positions.
 * It uses an optional egg drop position and a unique_ptr to an Egg object.
 *
 * The egg drop logic is encapsulated in tryDropEgg and initEggDropPosition.
 * The class tracks whether an egg has been dropped to prevent multiple drops.
 */
#include "Enemy.h"
#include <optional>
#include "Egg.h"

class Chicken : public Enemy
{
public:
    Chicken(const GameObjectParams& params);

    virtual void update(const sf::View& view, const float deltaTime) override;
    
    virtual void render(sf::RenderWindow& window) const override;
    
    virtual bool isOutOfWindowView(const sf::View& view) const override;
    
    static GameObjectParams getDefaultParams(const sf::Vector2f& pos);
    
    virtual const sf::Sprite& getSprite() const override;

private:
    
    virtual void move(const sf::View& view, const float deltaTime) override;

    void initEggDropPosition(const sf::View& view);
    
    void tryDropEgg();

    void checkNeedToPlaySound();

    float m_moveSpeed = 700.f;

    static bool m_registerit;
    
    bool m_eggDropped = false;
    
    std::optional<float> m_eggPosX;

    std::unique_ptr<Egg> m_egg;
};
