#include "UpsideDownPlayerState.h"
#include "Player.h"

UpsideDownPlayerState::UpsideDownPlayerState(sf::Sprite& sprite, Animation& animation)
    : PlayerState(sprite, animation)
{
    spriteAnimationInit(UpsideDownPlayerState::getDefaultValues());
    init();
}

void UpsideDownPlayerState::init()
{
    m_floorY = GraphicUtilities::getFloorY();
    m_ceilingY = GraphicUtilities::getCeilingY();

    m_command = std::make_unique<UpsideDownWalkCommand>(m_sprite);

    sf::Vector2f scale = m_sprite.getScale();
    m_sprite.setScale(scale.x, -scale.y);

    m_floorSoundName = "RegularStateRunSound";
    m_airSoundName = "FlipDown";
    m_airDownSoundName = "FlipUp";
    m_soundState.setSound(m_floorSoundName, true, 0.8f);
}

// Handles spacebar input to flip the player between floor and ceiling
void UpsideDownPlayerState::handleInput(const sf::Event& event)
{
    if (m_isLanding) return;

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        if (m_command->isWalkingOnCeiling())
        {
            // Transition from ceiling to floor
            m_command->startTransition(m_floorY, 2000.f);
            m_soundState = SoundState(m_airSoundName);
        }
        else
        {
            // Transition from floor to ceiling
            m_command->startTransition(m_ceilingY, -2000.f);
            m_soundState = SoundState(m_airDownSoundName);
        }
        m_soundState.setVolume(50);
        m_soundState.play();
        
        m_changeToWalk = false;
    }
    else
        m_changeToWalk = true;

}

void UpsideDownPlayerState::update(const sf::View& view, const float deltaTime)
{
    if (m_isLanding) updateSmoothLanding(view, deltaTime);
}

void UpsideDownPlayerState::render(sf::RenderWindow& window) const { (void)window; }

void UpsideDownPlayerState::move(const sf::View& view, const float deltaTime)
{
    if (m_isLanding || !m_command) return;

    static bool playedWalkSoundOnce = false; // to ensure sound plays only once per transition

    m_command->execute(view, deltaTime);

    if (m_command->shouldSwitchToWalk() && m_changeToWalk)
    {
        if (!playedWalkSoundOnce)
        {
            playedWalkSoundOnce = true;
            m_soundState.setSound(m_floorSoundName, true, 0.8f);
            m_soundState.setVolume(60);
            m_soundState.play();
        }
    }
    else
        playedWalkSoundOnce = false;
}

GameObjectParams UpsideDownPlayerState::getDefaultValues()
{
    return GameObjectParams(
        "upsideDownState", { 0.07f ,0.17f },
        sf::Vector2f(GraphicUtilities::getWindowSize().x * playerRelativeX,
            GraphicUtilities::getFloorY()),
        4, 0, 3, 0.2f, true);
}
