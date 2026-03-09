#include "LaserComponent.h"

bool LaserComponent::m_registerit = GameObjectFactory::registerIt("LaserComponent", [](const GameObjectParams& params)
    -> std::unique_ptr<GameObject>
    {
        return std::make_unique<LaserComponent>(params);
    });

LaserComponent::LaserComponent(const GameObjectParams& params)
    : Obstacles(params), m_animation(m_sprite, params)
{
    // Set custom origin point for proper rotation and positioning
    // Origin is set to 1/8 of texture width and center of height
    sf::Vector2f origin((float)m_sprite.getTexture()->getSize().x / 8,
        (float)m_sprite.getTexture()->getSize().y / 2);

    m_sprite.setOrigin(origin);

    // Apply proper scaling based on window scale and texture rectangle
    setScale(GraphicUtilities::getGameObjectScale(params._windowScale,
        m_sprite.getTextureRect()));
}

void LaserComponent::update(const sf::View& view, const float deltaTime)
{
    (void)view;
    m_animation.update(deltaTime);
}

void LaserComponent::render(sf::RenderWindow& window) const
{
    m_animation.render(window);
}

GameObjectParams LaserComponent::getLaserBeamDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("LaserBeam", { 0.05f, 0.08f }, pos, 4, 0, 3, 0.1f, true);
}

GameObjectParams LaserComponent::getLaserHeadDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("LaserHead", { 0.05f, 0.08f }, pos, 4, 0, 3, 0.3f, true);
}
