/**
 * GameOverState.h
 *  Defines the GameOverState, which manages the game over screen and its UI.
 *
 * The GameOverState class handles the display of the game over overlay, buttons, and transitions
 * back to the main menu. Inherits from GameState and manages its own overlay and button initialization.
 */
#pragma once
#include "GameState.h"

class GameOverState : public GameState
{
public:
    GameOverState(GameManager* gameManager,
        const std::string& musicName = "GameOverMusic");

    void update(float deltaTime) override;
    void render() const override;
    void handleInput(const sf::Event& event) override;

private:
    virtual void buttonsInit() override;
    void createOverlay();

    sf::RectangleShape m_overlay;

    const int m_numButtons = 1;
};
