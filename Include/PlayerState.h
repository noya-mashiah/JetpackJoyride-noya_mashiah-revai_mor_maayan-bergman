/**
 *  PlayerState.h
 *  Abstract base class for all player states (e.g., walking, flying, surfing).
 *
 * The PlayerState class defines the interface and shared logic for different play behaviors and abilities.
 * Each specific state (e.g., Regular, Bird, Dinosaur) inherits from this class and implements its own movement,
 * input handling, rendering, and state-specific effects.
 *
 * Design note: Enables the State design pattern for flexible and extensible player behavior.
 * Provides utility functions and protected members for use by derived states.
 */
#pragma once
#include <memory>
#include "Animation.h"
#include "WalkCommand.h"
#include "FlyCommand.h"
#include "JumpCommand.h"
#include "WaveSurfCommand.h"
#include "GameObjectParams.h"
#include "SwirlItem.h"
#include "SoundState.h"
#include "PlayerEffect.h" 

class Player;

class PlayerState
{
public:
    PlayerState() = default;

    PlayerState(sf::Sprite& sprite, Animation& animation);
        
    virtual ~PlayerState() = default;

	virtual void handleInput(const sf::Event& event) = 0;

    virtual void update(const sf::View& view, const float deltaTime) = 0;

    virtual void render(sf::RenderWindow& window) const = 0;

	virtual void move(const sf::View& view, const float deltaTime) = 0;

    virtual void onGasTankCollected();

    virtual void onMeatCollected();

    virtual void onShellCollected();

    virtual void onCoinCollected(int& coinCounter);

    virtual void onPearlCollected(int& coinCounter);

    virtual void processHit(Player& player);

    virtual std::unique_ptr<Pickables> addGift(const sf::Vector2f& scrollOffset);

    virtual bool isInvincible() const;

    float getViewSpeedMultiplier() const;

    virtual void onExit();

    virtual void onEnter();

    virtual void saveSoundState();

    virtual void restoreSoundState();

    virtual bool canCollectPowerUpBox() const;

protected:
    virtual void onLandingComplete() {};

    void spriteAnimationInit(const GameObjectParams& params);

    void updateSmoothLanding(const sf::View& view, float deltaTime);

    void updateTimer(const float deltaTime);

    virtual void onInvincibilityEnd();

    void initializeSwirlItems(std::vector<std::unique_ptr<SwirlItem>>& vec,
                              const GameObjectParams& params, const bool wantSound = false,
                              const std::string& soundName = " ");

    sf::Sprite& m_sprite;
    
    Animation& m_animation;

	std::unique_ptr<PlayerCommand> m_command;

    bool m_isResuming = false;

    float m_floorY = 0.f;
    
    float m_ceilingY = 0.f;

    bool m_isLanding = true;

    float m_landingVelocity = 0.f;

    int m_maxGiftCount = 3;

    int m_curGiftCount = 0;

    bool m_invincible = false;

    float m_invincibleTimer = 0.f;

    float m_specialGiftTimer = 5.f; // starts at 5 but the duration is 10 sec

    static constexpr float maxDuration = 10.0f;
    static constexpr float maxDurationGift = 13.0f;

    float m_viewSpeedMultiplier = 1.f;

    SoundState m_soundState;

    std::string m_floorSoundName = " ";
    std::string m_airSoundName = " ";
};
