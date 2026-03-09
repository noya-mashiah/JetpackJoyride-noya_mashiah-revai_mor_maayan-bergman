#include "Projectile.h"

bool Projectile::m_registerit = GameObjectFactory::registerIt("Projectile", 
    [](const GameObjectParams& params) -> std::unique_ptr<GameObject>
    {
        return std::make_unique<Projectile>(params);
    });

Projectile::Projectile(const GameObjectParams& params)
    : StaticObject(params), m_animation(m_sprite, params)
{
    offsetsInit();
    scaleSetUp(params._windowScale);
}

void Projectile::update(const sf::View& view, const float deltaTime)
{
    (void)view;

    sf::Vector2f parentPos = m_getParentPos();

    float X = (m_sprite.getPosition().x) - 700.f * deltaTime;
    float Y = parentPos.y + m_yOffset;

    m_sprite.setPosition(X, Y);

    m_animation.update(deltaTime);

    checkNeedToPlaySound(view);
}

void Projectile::render(sf::RenderWindow& window) const
{
    m_animation.render(window);
}

GameObjectParams Projectile::getWavesDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("Waves", { 0.09f ,0.18f }, pos,
        3, 0, 2, 0.1f, true);
}

GameObjectParams Projectile::getLightBallDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("Light", { 0.9f ,1.2f }, pos);
}

void Projectile::setGetParentPosFunc(std::function<sf::Vector2f()> func)
{
    m_getParentPos = std::move(func);
    setPosAndScale(getWavesDefaultParams(m_getParentPos()));
}

void Projectile::setSound(const std::string& soundName, const float vol)
{
    m_volume = vol;
    soundInit(soundName);
}

void Projectile::playSound()
{
    if (m_playedSound) return;
    m_sound.setVolume(m_volume);
    m_sound.play();
    m_playedSound = true;
}

void Projectile::setPosAndScale(const GameObjectParams& params)
{
    scaleSetUp(params._windowScale);

    sf::Vector2f parentPos = m_getParentPos();

    m_sprite.setPosition(
        parentPos.x - m_xOffset,
        parentPos.y + m_yOffset
    );
}

void Projectile::offsetsInit()
{
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
    m_xOffset = windowSize.x * WavesRelativeX;
    m_yOffset = windowSize.y * WavesRelativeY;
}

void Projectile::soundInit(const std::string& soundName)
{
    m_sound.setBuffer(ResourcesManager::getInstance().getSound(soundName));
    m_sound.setVolume(m_volume);
}

void Projectile::checkNeedToPlaySound(const sf::View& view)
{
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
    float rightEdgeView = view.getCenter().x + windowSize.x / 2.f;

    if (!m_playedSound && m_getParentPos().x - windowSize.x * 0.3 <= rightEdgeView)
    {
        m_sound.play();
        m_playedSound = true;
    }
}
