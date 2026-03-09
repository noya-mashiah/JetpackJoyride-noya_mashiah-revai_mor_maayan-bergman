#pragma once
#include "GameState.h"

/*
* represent the pause state of the game
*/

class PauseState : public GameState
{
public:
    PauseState(GameManager* gameManager);

    void update(const float deltaTime) override;
    void render() const override;
    void handleInput(const sf::Event& event) override;

    virtual void onEnter() override;
    virtual void onExit() override;

    virtual void mute() override;
    virtual void unmute() override;
    virtual void quit() override;

private:
    virtual void buttonsInit() override;

    void createOverlay();

    sf::RectangleShape m_overlay;
    int m_numButtons = 3;
};
