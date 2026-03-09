#pragma once
#include "PlayerCommand.h"
#include "GraphicUtilities.h"

// Enum to represent the different phases of the wave surfing movement
enum WaveMovementPhase {
    WAVE_IDLE,
    WAVE_DIVING,
    WAVE_ASCENDING,
    WAVE_DESCENDING,
    WAVE_ON_FLOOR
};

/*
* represent the command of the surfer movement
*/

class WaveSurfCommand : public PlayerCommand
{
public:
    WaveSurfCommand(sf::Sprite& playerSprite, const float gravity = 2000.f,
        const float jumpForce = -400.f,
        const float floor = 0.f, const float ceiling = 0.f,
        const sf::Vector2f& velocity = { 0.f, 0.f });

    virtual void execute(const sf::View& view, const float deltaTime) override;

    virtual bool shouldSwitchToWalk() const override;

    virtual int getAnimationPhase() const override; // This will return the core movement phase

private:
    void handleIdlePhase(sf::Vector2f& currentPos);
    void handleDivingPhase(sf::Vector2f& currentPos, const float deltaTime);
    void handleAscendingPhase(sf::Vector2f& currentPos, const float deltaTime);
    void handleDescendingPhase(sf::Vector2f& currentPos, const float deltaTime);

    float m_waveY = 0.f;
    float m_startDiveY = 0.f;
    float m_diveDistance = 0.f;
    float m_peakY = 0.f;
    float m_currentVerticalSpeed = 0.f;

    WaveMovementPhase m_wavePhase = WAVE_IDLE;

    static constexpr float DIVE_VELOCITY = 400.f;
    static constexpr float ASCEND_VELOCITY = 800.f;
    static constexpr float DESCENT_VELOCITY = 300.f;
};
