#include "ProjectileEnemy.h"

bool ProjectileEnemy::m_registerit = GameObjectFactory::registerIt("ProjectileEnemy",
    [](const GameObjectParams& params) -> std::unique_ptr<GameObject>
    {
        return std::make_unique<ProjectileEnemy>(params, params, "", ""); // Will be overridden
    });

namespace { // helper function to initialize the projectile properly
    std::unique_ptr<Projectile> createProjectile(const GameObjectParams& params) {
        auto basePtr = GameObjectFactory::create("Projectile", params);
        return std::unique_ptr<Projectile>(static_cast<Projectile*>(basePtr.release()));
    }
}

ProjectileEnemy::ProjectileEnemy(const GameObjectParams& enemyParams, const GameObjectParams& projectileParams,
    const std::string& projectileSoundName, const std::string& enemySoundName,
    const float projectileVol, const float enemyVol,
    const int projectileStartFrame, const int projectileRenderFrame)
    : Enemy(enemyParams),
    m_projectile(createProjectile(projectileParams)),
    m_enemySoundName(enemySoundName), m_volume(enemyVol),
    m_projectileStartFrame(projectileStartFrame),
    m_projectileRenderFrame(projectileRenderFrame)
{
    if (m_projectile)
    {
        m_projectile->setGetParentPosFunc([this]() { return m_sprite.getPosition(); });
        m_projectile->setSound(projectileSoundName, projectileVol);
    }

    soundInit(enemySoundName, true, m_volume);
}

void ProjectileEnemy::update(const sf::View& view, const float deltaTime)
{
    if (!m_enteredView && m_sprite.getPosition().x <=
        (view.getCenter().x + view.getSize().x / 2.f))
    {
        m_enteredView = true;

        if (m_shouldAnimateOnEnter)
            m_animation.setAnimation(m_enteredViewAnimationParams);
    }

    move(view, deltaTime);
    m_animation.update(deltaTime);

    checkNeedToPlaySound(view);

    if (m_animation.getCurFrameNum() >= m_projectileStartFrame && m_projectile)
    {
        m_projectile->update(view, deltaTime);
        m_projectile->playSound();
    }
}

void ProjectileEnemy::render(sf::RenderWindow& window) const
{
    m_animation.render(window);

    if (m_animation.getCurFrameNum() >= m_projectileRenderFrame && m_projectile)
        m_projectile->render(window);
}

GameObjectParams ProjectileEnemy::getBatDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("Bat", { 0.11f, 0.15f }, pos,
        2, 0, 1, 0.1f, true);
}

GameObjectParams ProjectileEnemy::getPiranhaDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("Piranha", { 0.6f, 0.9f }, pos,
        9, 0, 8, 0.2f, false);
}

const sf::Sprite& ProjectileEnemy::getSprite() const
{
    if (m_projectile) return m_projectile->getSprite();
    else return m_sprite;
}

void ProjectileEnemy::move(const sf::View& view, const float deltaTime)
{
    (void)view;
    sf::Vector2f curPos = m_sprite.getPosition();
    m_sprite.setPosition(curPos.x - 200.f * deltaTime, curPos.y);
}

void ProjectileEnemy::checkNeedToPlaySound(const sf::View& view)
{
    float rightEdgeView = view.getCenter().x + GraphicUtilities::getWindowSize().x / 2.f;
    Enemy::checkNeedToPlaySound(m_sprite.getPosition().x, rightEdgeView);
}
