#include "PlayerEffect.h"
#include "GraphicUtilities.h"
#include "Consts.h"

PlayerEffect::PlayerEffect(const GameObjectParams& params,
    std::function<sf::Vector2f()> getPlayerPos,
    float xOffset, float yOffset,
    bool useVisibilityLogic)
    : StaticObject(params), m_animation(m_sprite, params),
    m_getPlayerPos(getPlayerPos), m_xOffset(xOffset), m_yOffset(yOffset),
    m_useVisibilityLogic(useVisibilityLogic)
{
    scaleSetUp(params._windowScale);
}


void PlayerEffect::update(const sf::View& view, const float deltaTime)
{
    (void)view;

    sf::Vector2f playerPos = m_getPlayerPos();

    float posX = playerPos.x + m_xOffset;
    float posY = playerPos.y + m_yOffset;

    m_sprite.setPosition(posX, posY);

    if (m_useVisibilityLogic)
        m_visible = (playerPos.y < GraphicUtilities::getFloorY());

    m_animation.update(deltaTime);
}

void PlayerEffect::render(sf::RenderWindow& window) const
{
    if (m_visible)
    {
        m_animation.render(window);
    }
}

GameObjectParams PlayerEffect::getSparkleDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("Sparkle", { 0.03f, 0.04f }, pos, 3, 0, 2, 0.1f, true);
}

GameObjectParams PlayerEffect::getFlameDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("Flame", { 0.018f, 0.07f }, pos, 6, 0, 5, 0.1f, true);
}

GameObjectParams PlayerEffect::getDinoWingsDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("DinoWings", { 0.3f, 0.5f }, pos, 6, 0, 5, 0.1f, true);
}

GameObjectParams PlayerEffect::getDinoFireDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("DinoFire", { 0.12f, 0.2f }, pos, 8, 0, 7, 0.1f, true);
}

void PlayerEffect::setOffset(float xOffset, float yOffset)
{
    m_xOffset = xOffset;
    m_yOffset = yOffset;
}

void PlayerEffect::setIsVisible(const bool visible)
{
    m_visible = visible;
}
