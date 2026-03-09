#include "PlayerState.h"
#include "Player.h"

PlayerState::PlayerState(sf::Sprite& sprite, Animation& animation)
    : m_sprite(sprite), m_animation(animation) {}

void PlayerState::onGasTankCollected() {}

void PlayerState::onMeatCollected() {}

void PlayerState::onShellCollected() {}

void PlayerState::onCoinCollected(int& coinCounter)
{
    coinCounter += 1;
}

void PlayerState::onPearlCollected(int& coinCounter) 
{
    coinCounter += 5;
}

void PlayerState::processHit(Player& player) 
{ 
    if (m_isLanding) return;

    player.setState(std::make_unique<RegularPlayerState>(m_sprite, m_animation));
}

std::unique_ptr<Pickables> PlayerState::addGift(const sf::Vector2f& scrollOffset) 
{
    (void)scrollOffset;
    return nullptr;
}

bool PlayerState::isInvincible() const
{
    return m_invincible;
}

float PlayerState::getViewSpeedMultiplier() const
{
    return m_viewSpeedMultiplier;
}

void PlayerState::onExit()
{
    m_soundState.stop();
}

void PlayerState::onEnter(){}

void PlayerState::saveSoundState()
{
    m_soundState.saveState();
    m_isResuming = true;
}

void PlayerState::restoreSoundState()
{
    m_soundState.restoreState();
    m_isResuming = false;
}

bool PlayerState::canCollectPowerUpBox() const { return true; }

void PlayerState::spriteAnimationInit(const GameObjectParams& params)
{
    ResourcesManager& inst = ResourcesManager::getInstance();

    m_sprite.setTexture(inst.getTexture(params._textureName));

    m_animation.setAnimation(params);

    m_sprite.setScale(GraphicUtilities::getGameObjectScale(
        params._windowScale, m_sprite.getTextureRect()));
}

void PlayerState::updateSmoothLanding(const sf::View& view,
                                      float deltaTime)
{
    if (!m_isLanding) return;

    sf::Vector2f pos = GeometryPhysicsUtilities::applyVerticalTransition(view,
        m_sprite.getPosition(), m_landingVelocity, 2000.f,
        deltaTime, m_floorY, m_isLanding);

    m_sprite.setPosition(pos);

    if (!m_isLanding) onLandingComplete();
}

void PlayerState::updateTimer(const float deltaTime)
{
    if (m_invincible)
    {
        m_invincibleTimer -= deltaTime;

        if (m_invincibleTimer <= 0.f)
        {
            m_invincibleTimer = 0.f;
            m_invincible = false;
            onInvincibilityEnd();
        }
    }
}

void PlayerState::onInvincibilityEnd() {}
// Creates a cluster of swirl items around the player, sets their offsets, and assigns sound if needed.
void PlayerState::initializeSwirlItems(std::vector<std::unique_ptr<SwirlItem>>& vec,
                                        const GameObjectParams& params, const bool wantSound, const std::string& soundName)
{
    vec.clear();

    int numItems = 9;

    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

    float clusterWidth = windowSize.x * 0.1f;  // X-spread of the cluster
    float clusterHeight = windowSize.y * 0.1f; // Y-spread of the cluster

    float baseXOffset = -windowSize.x * 0.08f;
    float baseYOffset = -windowSize.y * 0.01f;

    std::vector<sf::Vector2f> swirlOffsets = GeometryPhysicsUtilities::generateSwirlPositions(
        numItems,
        windowSize,
        clusterWidth,
        clusterHeight,
        baseXOffset,
        baseYOffset
    );

    for (size_t i = 0; i < swirlOffsets.size(); ++i)
    {
        vec.push_back(std::make_unique<SwirlItem>(
            params,
            [this]() { return m_sprite.getPosition(); }
        ));

        vec.back()->setOffset(swirlOffsets[i].x, swirlOffsets[i].y);

        if (wantSound)
            vec.back()->setSound(soundName);
    }
}
