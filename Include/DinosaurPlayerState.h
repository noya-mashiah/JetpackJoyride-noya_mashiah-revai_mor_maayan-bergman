/**
 * DinosaurPlayerState.h
 * Defines the Dinosaur player state (invincible, can jump and walk).
 *
 * The DinosaurPlayerState class implements the player's behavior when in dinosaur mode,
 * including invincibility, special effects, and unique movement and gift logic- meat.
 * Inherits from PlayerState and adds fire, wings, and hourglass effects.
 */
#pragma once
#include "PlayerState.h"
#include "Meat.h"
#include "Hourglass.h"

class DinosaurPlayerState: public PlayerState
{
public:

    DinosaurPlayerState() = default;

    DinosaurPlayerState(sf::Sprite& sprite, Animation& animation);

    virtual void handleInput(const sf::Event& event) override;

    virtual void update(const sf::View& view, const float deltaTime) override;

    virtual void render(sf::RenderWindow& window) const  override;

    virtual void move(const sf::View& view, const float deltaTime) override;

    virtual void onMeatCollected() override;

    static GameObjectParams getDefaultValues();

    std::unique_ptr<Pickables> addGift(const sf::Vector2f& scrollOffset) override;

    void processHit(Player& player) override;

private:

    virtual void onInvincibilityEnd();

    void init();

    void soundInit();

    virtual void onLandingComplete() override;

    void walk();
    void playWalk();

    void jump();
    void playJump();

    PlayerEffect m_fire;

    PlayerEffect m_wings;

    float m_time = 0;
    bool m_startMulti = false;

    Hourglass m_hourglass;
};
