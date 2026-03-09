#pragma once
#include "PlayerCommand.h"

/*
* represent the command of jumping
*/

class JumpCommand : public PlayerCommand
{
public:
    using PlayerCommand::PlayerCommand;

    virtual void execute(const sf::View& view, const float deltaTime) override;
    
    virtual bool shouldSwitchToWalk() const override;

    virtual bool shouldPlaySound() override;
    
private:

    void handleJumpInput();
   
    void applyGravity(const float deltaTime);
    
    void updatePosition(const sf::View& view, const float deltaTime);
    
    void handleLanding();
    
    void clampToCeiling();

    float m_jumpHeight = 800.f;
    
    bool m_isJumping = false;

    int m_maxJumps = 3;      // Default: allowed maximum double jump
    
    int m_jumpsLeft = 3;     // counter of jumps left
    
    bool m_spaceWasPressed = false;

    bool m_justJumped = false;
};
