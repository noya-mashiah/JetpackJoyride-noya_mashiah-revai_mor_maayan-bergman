#pragma once
#include "PlayerCommand.h"

/*
* represent the command of the upside down movement 
*/

class UpsideDownWalkCommand : public PlayerCommand
{
public:
    
    using PlayerCommand::PlayerCommand;

    virtual void execute(const sf::View& view, const float deltaTime) override;

    virtual void startTransition(const float targetY, const float acceleration)  override;

    virtual bool isWalkingOnCeiling() const override;

    virtual bool shouldSwitchToWalk() const override;

private:
    
    bool m_isTransitioning = false;

    float m_targetY = 0.f;
    
    float m_velocityY = 0.f;
    
    float m_accelerationY = 0.f;
    
    bool m_onCeiling = false;
};