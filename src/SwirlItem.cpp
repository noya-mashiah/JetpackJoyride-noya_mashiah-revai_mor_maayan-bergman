#include "SwirlItem.h"
#include <random>

SwirlItem::SwirlItem(const GameObjectParams& params, std::function<sf::Vector2f()> getPlayerPos)
    : StaticObject(params), m_animation(m_sprite, params), m_getPlayerPos(getPlayerPos)
{
    scaleSetUp(params._windowScale);

    randomizeParams();
}

void SwirlItem::update(const sf::View& view, const float deltaTime)
{
    (void)view;
    static float globalTime = 0.f;
    globalTime += deltaTime;

    sf::Vector2f playerPos = m_getPlayerPos();

    float t = globalTime * m_animSpeed + m_animPhase;

    float x, y;

    if (m_isFigure8) {
        // infinity shape (8 figure) parametric equation
        x = m_animRadius * std::sin(t);
        y = m_animRadius * std::sin(t) * std::cos(t);
    }
    else {
        // Circle shape
        x = m_animRadius * std::cos(t);
        y = m_animRadius * std::sin(t);
    }

    m_sprite.setPosition(playerPos.x + m_xOffset + x, playerPos.y + m_yOffset + y);
    m_animation.update(deltaTime);
    updateSounds();
}

void SwirlItem::render(sf::RenderWindow& window) const
{
    m_animation.render(window);
}

void SwirlItem::setOffset(const float xOffset, const float yOffset)
{
    m_xOffset = xOffset;
    m_yOffset = yOffset;
}

void SwirlItem::setSound(const std::string& soundName, const bool shouldLoop, const float pitch)
{
    m_soundState.setSound(soundName, shouldLoop, pitch);
    m_soundState.setVolume(60);
}

void SwirlItem::saveState()
{
    m_soundState.saveState();
    m_isResuming = true;
    m_soundState.stop();
}

void SwirlItem::restoreState()
{
    m_soundState.restoreState();
    m_isResuming = false;
}

void SwirlItem::applyTransparency()
{
    static sf::Color semiTransparent(255, 255, 255, 220);
    m_sprite.setColor(semiTransparent);
}

// Randomizes animation and movement parameters for swirling item effect
void SwirlItem::randomizeParams()
{
    // Randomize animation parameters for cluster effect
    static std::mt19937 rng(std::random_device{}());
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

    float minRadius = windowSize.x * 0.012f;
    float maxRadius = windowSize.x * 0.018f;
    std::uniform_real_distribution<float> radiusDist(minRadius, maxRadius);

    std::uniform_real_distribution<float> speedDist(0.4f, 0.8f); // Movement speed, usually fine as-is
    std::uniform_real_distribution<float> phaseDist(0.f, 2 * 3.14159f); // Start angle
    std::bernoulli_distribution figure8Dist(0.5);   // 50% chance
    std::uniform_real_distribution<float> frameTimeDist(0.1f, 0.3f); // Animation frame time

    m_animRadius = radiusDist(rng);
    m_animSpeed = speedDist(rng);
    m_animPhase = phaseDist(rng);
    m_isFigure8 = figure8Dist(rng);
    m_animation.setFrameTime(frameTimeDist(rng));
}

void SwirlItem::updateSounds()
{
    if (m_animation.isAtLastFrame()) {
        if (!m_soundPlayedThisCycle) {
            m_soundState.play();
            m_soundPlayedThisCycle = true;
        }
    }
    else {
        m_soundPlayedThisCycle = false;
    }
}
