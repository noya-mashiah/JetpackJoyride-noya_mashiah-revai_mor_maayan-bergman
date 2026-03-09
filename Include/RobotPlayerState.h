/**
 *RobotPlayerState.h
* Defines the Robot player state (flying, sparkles, gas tank gifts).
 *
 * The RobotPlayerState class implements the player's behavior when in robot mode,
 * including flying, collecting gas tanks, and visual effects like sparkles.
 * Inherits from PlayerState and manages a cluster of sparkles and an hourglass effect.
 */
#pragma once
#include "PlayerState.h"
#include "GasTank.h"
#include "Hourglass.h"
#include <memory>

class RobotPlayerState :public PlayerState
{
public:
    RobotPlayerState() = default;

	RobotPlayerState(sf::Sprite& sprite, Animation& animation);

    virtual void handleInput(const sf::Event& event) override;

    virtual void update(const sf::View& view, const float deltaTime) override;

    virtual void render(sf::RenderWindow& window) const override;

    virtual void move(const sf::View& view, const float deltaTime) override;

    static GameObjectParams getDefaultValues();

    virtual void onGasTankCollected() override;

    void processHit(Player& player) override;

    std::unique_ptr<Pickables> addGift(const sf::Vector2f& scrollOffset) override;

private:

    void init();

    void fly();

    void walk();
    void playWalk();

    virtual void onLandingComplete() override;

    std::vector<std::unique_ptr<PlayerEffect>> m_sparkles;

    void initializeSparkles();

    Hourglass m_hourglass;
};
