#include "Chicken.h"

bool Chicken::m_registerit = GameObjectFactory::registerIt("Chicken", 
    [](const GameObjectParams& params) -> std::unique_ptr<GameObject>
    {
        return std::make_unique<Chicken>(params);
    });

Chicken::Chicken(const GameObjectParams& params)
    : Enemy(params), m_egg(nullptr)
{
    sf::Vector2f scale = m_sprite.getScale();
    m_sprite.setScale(-scale.x, scale.y);
    soundInit("ChickenSound", false, 100);
}

void Chicken::update(const sf::View& view, const float deltaTime)
{
    move(view, deltaTime);
    m_animation.update(deltaTime);

    initEggDropPosition(view);
    tryDropEgg();

    if (m_egg) m_egg->update(view, deltaTime);
}

void Chicken::initEggDropPosition(const sf::View& view)
// Sets a random X position in the view for the chicken to drop its egg.
{
    if (m_eggPosX.has_value()) return;

    float rightViewCorner = view.getCenter().x + (view.getSize().x / 2);

    if (m_sprite.getPosition().x < rightViewCorner)
    {
        checkNeedToPlaySound();

        sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

        float minEggX = view.getCenter().x + windowSize.x * EggDropMinRelativeX;
        float maxEggX = view.getCenter().x + windowSize.x * EggDropMinRelativeY;
        
        m_eggPosX = minEggX + static_cast<float>(std::rand()) / RAND_MAX * (maxEggX - minEggX);
    }
}

void Chicken::tryDropEgg()
//Drops an egg if the chicken has reached the randomized drop position.
{
    if (!m_eggDropped && m_eggPosX.has_value() && m_sprite.getPosition().x < *m_eggPosX)
    {
        m_egg = std::make_unique<Egg>(Egg::getDefaultParams(sf::Vector2f(*m_eggPosX, m_sprite.getPosition().y)));
        m_eggDropped = true;
    }
}

void Chicken::checkNeedToPlaySound()
{
    if (m_playedSound) return;

    m_playedSound = true;
    m_sound.play();
}

void Chicken::render(sf::RenderWindow& window) const
{
    m_animation.render(window);

    if (m_egg) m_egg->render(window);
}

bool Chicken::isOutOfWindowView(const sf::View& view) const
{
    if (m_egg) return m_egg->isOutOfWindowView(view);
    else return Enemy::isOutOfWindowView(view);
}

GameObjectParams Chicken::getDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("Chicken", { 0.08f, 0.11f }, pos,
        3, 0, 2, 0.1f, true);
}

const sf::Sprite& Chicken::getSprite() const
{
    if (m_egg) return m_egg->getSprite();
    else return m_sprite;
}

void Chicken::move(const sf::View& view, const float deltaTime)
{
    (void)view;
    sf::Vector2f curPos = m_sprite.getPosition();
    m_sprite.setPosition(curPos.x - m_moveSpeed * deltaTime, curPos.y);
}
