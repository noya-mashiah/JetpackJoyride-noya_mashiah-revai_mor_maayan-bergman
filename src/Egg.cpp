#include "Egg.h"

// Static member initialization
bool Egg::m_registerit = GameObjectFactory::registerIt("Egg",
    [](const GameObjectParams& params) -> std::unique_ptr<GameObject>
    {
        return std::make_unique<Egg>(params);
    });

Egg::Egg(const GameObjectParams& params)
    : Obstacles(params), m_animation(m_sprite, params)
{
    setScale(GraphicUtilities::getGameObjectScale(params._windowScale, m_sprite.getTextureRect()));
}

void Egg::setPosAndScale(const GameObjectParams& params)
{
    scaleSetUp(params._windowScale);
}

// If the egg has landed, triggers landing behavior
// Otherwise, applies gravity and updates position
void Egg::update(const sf::View& view, const float deltaTime)
{
    m_animation.update(deltaTime);

    if (m_landed) {
        landed(deltaTime);
        return;
    }

    sf::Vector2f curPos = m_sprite.getPosition();
    
    // Egg still falling - calculate new Y position
    bool stillFalling = !m_landed;
    float newY = GeometryPhysicsUtilities::applyVerticalTransition(
        view,
        curPos,
        m_velocityY,
        m_accelerationY,
        deltaTime,
        GraphicUtilities::getFloorY(),
        stillFalling
    ).y;

    m_landed = !stillFalling;
    m_sprite.setPosition(curPos.x, newY);
}

void Egg::landed(float deltaTime)
{
    (void)deltaTime;
    if (!m_break)
    if (!m_break)   // so it will happen only once
    {
        setBreakAnimation();
        m_break = true;
        playEggSound();
    }
}

void Egg::setBreakAnimation()
{
    m_animation.setAnimation(GameObjectParams( "Egg", { 0.04f, 0.09f },
        m_sprite.getPosition(), 4, 1, 3, 0.2f, false));
}

void Egg::playEggSound()
{
    static sf::Sound sound;
    static bool initialized = false;

    if (!initialized)
    {
        sound.setBuffer(ResourcesManager::getInstance().getSound("EggSound"));
        sound.setVolume(100);
        initialized = true;
    }

    sound.play();
}

void Egg::render(sf::RenderWindow& window) const
{
    m_animation.render(window);
}

bool Egg::hasLanded() const
{
    return m_landed;
}

GameObjectParams Egg::getDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("Egg", { 0.04f, 0.09f }, pos, 4);
}
