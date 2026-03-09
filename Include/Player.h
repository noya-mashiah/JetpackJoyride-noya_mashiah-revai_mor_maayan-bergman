/**
 * Player.h
 *  Main player character class, manages state, input, and interactions.
 *
 * The Player class represents the main controllable character, managing its current state,
 * input handling, rendering, coin collection, and transitions between different player states.
 * Inherits from MovingObject and delegates behavior to PlayerState subclasses.
 */
#pragma once
#include "MovingObject.h"
#include "PlayerState.h"
#include "RegularPlayerState.h"
#include "UpsideDownPlayerState.h"
#include "RobotPlayerState.h"
#include "DiePlayerState.h"
#include "BirdPlayerState.h"
#include "DinosaurPlayerState.h"
#include "SurferPlayerState.h"

class Player : public MovingObject
{
public:
    Player()= default;
    
    Player(const GameObjectParams& params);

    virtual void render(sf::RenderWindow& window) const override;

    virtual void handleInput(const sf::Event& event);
   
    virtual void update(const sf::View& view, const float deltaTime) override;

    void processHit();

    void changeToRegularState();
    
    void changeToRobotState();
   
    void changeToUpsideDownState();
    
    void changeToBirdState();
    
    void changeToDinosaurState();

    void changeToSurferState();

    void onGasTankCollected();

    void onMeatCollected();
    
    void onCoinCollected();

    void onPearlCollected();

    void onShellCollected();

    bool canCollectPowerUpBox() const;

    void setState(std::unique_ptr<PlayerState> newState);

    std::unique_ptr<Pickables> addStateGift(const sf::Vector2f& scrollOffset);

    void reset();

    int getCoinsCounter() const;

    float getViewSpeedMultiplier() const;

    bool isInvincible() const;

    void onEnter();

    void onExit();

    void saveSoundState();

    void restoreSoundState();

private:

    virtual void move(const sf::View& view, const float deltaTime) override;

    std::unique_ptr<PlayerState> m_state;

    int m_coinsCounter = 0;

};
