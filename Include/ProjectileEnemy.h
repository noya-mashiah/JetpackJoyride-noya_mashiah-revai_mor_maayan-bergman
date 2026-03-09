#pragma once
#include "Enemy.h"
#include "Projectile.h"

/**
 *  A unified enemy class that combines an enemy with a projectile effect
 *
 * The ProjectileEnemy class represents enemies (like Bat or Piranha) that have
 * associated projectile effects (like waves or light balls). It manages both
 * the enemy animation/movement and the projectile's behavior, including
 * synchronized sound effects and rendering.
 */

class ProjectileEnemy : public Enemy
{
public:
    ProjectileEnemy() = default;
    ProjectileEnemy(const GameObjectParams& enemyParams, const GameObjectParams& projectileParams,
        const std::string& projectileSoundName, const std::string& enemySoundName,
        const float projectileVol = 50, const float enemyVol = 50,
        const int projectileStartFrame = 0, const int projectileRenderFrame = 0);

    virtual void update(const sf::View& view, const float deltaTime) override;
    virtual void render(sf::RenderWindow& window) const override;

    static GameObjectParams getBatDefaultParams(const sf::Vector2f& pos);
    static GameObjectParams getPiranhaDefaultParams(const sf::Vector2f& pos);
    virtual const sf::Sprite& getSprite() const override;

private:
    virtual void move(const sf::View& view, const float deltaTime) override;
    void checkNeedToPlaySound(const sf::View& view);

    std::unique_ptr<Projectile> m_projectile;
    std::string m_enemySoundName;
    bool m_enteredView = false;

    // Animation parameters for when enemy enters view
    GameObjectParams m_enteredViewAnimationParams;
    bool m_shouldAnimateOnEnter = false;

    // Projectile activation conditions
    int m_projectileStartFrame;
    int m_projectileRenderFrame;
    float m_volume;

    static bool m_registerit;
};
