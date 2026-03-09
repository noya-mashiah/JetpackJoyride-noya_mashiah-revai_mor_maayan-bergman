#include "WallLamp.h"

// Static member initialization
bool WallLamp::m_registerit = GameObjectFactory::registerIt("WallLamp", [](const GameObjectParams& params)
    -> std::unique_ptr<GameObject>
    {
        return std::make_unique<WallLamp>(params);
    });

WallLamp::WallLamp(const GameObjectParams& params)
    : StaticObject(params), m_animation(m_sprite, params)
{
    setScale(GraphicUtilities::getGameObjectScale(params._windowScale, 
                                                  m_sprite.getTextureRect()));
}

void WallLamp::update(const sf::View& view, const float deltaTime)
{
    (void)view;
    m_animation.update(deltaTime);
}

void WallLamp::render(sf::RenderWindow& window) const
{
    m_animation.render(window);
}

GameObjectParams WallLamp::getDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("WallLamp", { 0.2f, 0.3f }, pos,
        6, 0, 5, 0.1f, true);
}
