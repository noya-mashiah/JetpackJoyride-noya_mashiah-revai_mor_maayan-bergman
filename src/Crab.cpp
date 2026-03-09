#include "Crab.h"

bool Crab::m_registerit = GameObjectFactory::registerIt("Crab",
    [](const GameObjectParams& params) -> std::unique_ptr<GameObject>
    {
        return std::make_unique<Crab>(params);
    });

Crab::Crab(const GameObjectParams& params)
    :Enemy(params)
{   
    soundInit("CrabSound", true, 100);
}

void Crab::update(const sf::View& view, const float deltaTime)
{
    move(view, deltaTime);
    m_animation.update(deltaTime);
    checkNeedToPlaySound(view);
}


GameObjectParams Crab::getDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("Crab", { 0.17f, 0.32f }, pos, 
        9, 0, 8, 0.2f, true);
}

void Crab::playPinchSound()
{
    static sf::Sound sound;
    static bool initialized = false;

    if (!initialized)
    {
        sound.setBuffer(ResourcesManager::getInstance().getSound("OuchSound"));
        sound.setVolume(100);
        initialized = true;
    }

    sound.play();
}

void Crab::move(const sf::View& view, const float deltaTime)
{
    (void)view;
    sf::Vector2f curPos = m_sprite.getPosition();
    m_sprite.setPosition(curPos.x - m_moveSpeed * deltaTime, curPos.y);
}

void Crab::checkNeedToPlaySound(const sf::View& view)
{
    float rightEdgeView = view.getCenter().x + GraphicUtilities::getWindowSize().x / 2.f;

    Enemy::checkNeedToPlaySound(m_sprite.getPosition().x, rightEdgeView);
}
