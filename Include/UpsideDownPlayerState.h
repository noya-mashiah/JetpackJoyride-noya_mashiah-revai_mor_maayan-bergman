#pragma once
#include "PlayerState.h"
#include "UpsideDownWalkCommand.h"

/*
* represent a special given state - upside down
*/

class UpsideDownPlayerState : public PlayerState
{
public:
    UpsideDownPlayerState() = default;

    UpsideDownPlayerState(sf::Sprite& sprite, Animation& animation);

    virtual void handleInput(const sf::Event& event) override;

    virtual void update(const sf::View& view, const float deltaTime) override;
    
    virtual void render(sf::RenderWindow& window) const override;
    
    virtual void move(const sf::View& view, const float deltaTime) override;

    static GameObjectParams getDefaultValues();

private:

    void init();

    bool m_changeToWalk = true;

    std::string m_airDownSoundName = " ";

};
