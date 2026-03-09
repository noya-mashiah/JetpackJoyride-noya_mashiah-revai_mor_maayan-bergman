/**
 * HelpState.h
 *  Defines the HelpState, which manages the help/instructions screen and its UI.
 *
 * The HelpState class handles the display of help pages, navigation between them,
 * and related UI. Inherits from GameState and manages its own background, page logic, and buttons.
 */
#pragma once
#include "GameState.h"
#include "SimpleButton.h"
#include "HoverButton.h"
#include "TuggleButton.h"
#include <vector>
#include <memory>

class HelpState : public GameState {
public:
    HelpState() = default;

    HelpState(GameManager* gameManager);

    void update(float deltaTime) override;

    void render() const override;

    void handleInput(const sf::Event& event) override;

    virtual void moveHelpLeft() override;

    virtual void moveHelpRight() override;

private:

    enum button_type_t { returnToMenu_t, left_t, right_t, mute_t };

    void updateBackground();

    virtual void buttonsInit() override;

    sf::Sprite m_background;

    int m_curPage = 0;

    const int m_maxNumPages = 5;

    const int m_numButtons = 4;
};
