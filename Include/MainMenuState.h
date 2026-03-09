/**
 *  MainMenuState.h
 * Defines the MainMenuState, which manages the main menu screen .
 *
 * The MainMenuState class handles the display of the main menu background, buttons,
 * and transitions to other game states. Inherits from GameState and manages its own button initialization.
 */
#pragma once
#include "GameState.h"

class MainMenuState : public GameState
{
public:
    MainMenuState() = default;

    MainMenuState(GameManager* gameManager);

    void update(float deltaTime) override;

    void render() const override;
    
    void handleInput(const sf::Event& event) override;

	virtual void quit() override;

private:
    
    virtual void buttonsInit() override;

    sf::Sprite m_background;

    const int m_numOfButtons = 3;
};
