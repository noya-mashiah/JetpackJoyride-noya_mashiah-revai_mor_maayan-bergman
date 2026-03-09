/**
 *  DiePlayerState.h
 *  Defines the Die player state (player is dying or dead).
 *
 * The DiePlayerState class implements the player's behavior when dying,
 * including animation, sound, and transition to the game over state.
 * Inherits from PlayerState and uses a DieCommand for movement.
 */
#pragma once
#include "PlayerState.h"
#include "DieCommand.h"

class DiePlayerState : public PlayerState
{
public:

    DiePlayerState() = default;

    DiePlayerState(sf::Sprite& sprite, Animation& animation);

    virtual void handleInput(const sf::Event& event) override;

    // Called every frame to update state logic (movement, input, etc.)
    virtual void update(const sf::View& view, const float deltaTime) override;

    // Render any state-specific effects (optional)
    virtual void render(sf::RenderWindow& window) const override;

    virtual void move(const sf::View& view, const float deltaTime) override;

    static GameObjectParams getDefaultValues();

    virtual void processHit(Player& player) override;

    virtual void onExit() override {} // in order to not stop sound

    virtual bool canCollectPowerUpBox() const override;

private:

    void init();

    bool m_hasRequestedToDie = false;
};
