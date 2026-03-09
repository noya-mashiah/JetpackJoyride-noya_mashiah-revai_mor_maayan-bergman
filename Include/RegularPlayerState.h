#pragma once
#include "PlayerState.h"

/*
* Represent the regular state of the player in the game
*/

class RegularPlayerState : public PlayerState
{
public:
    RegularPlayerState() = default;

    RegularPlayerState(sf::Sprite& sprite, Animation& animation);

    virtual void handleInput(const sf::Event& event) override;

    virtual void update(const sf::View& view, const float deltaTime) override;

    virtual void render(sf::RenderWindow& window) const  override;

    virtual void move(const sf::View& view, const float deltaTime) override;

    static GameObjectParams getDefaultValues();

    virtual void processHit(Player& player) override;

private:

    void init();

    void fly();

    void walk();
    void playWalk();

    virtual void onLandingComplete() override;

    PlayerEffect m_flame;
};
