/**
 *  HighScoresState.h
 *  Defines the HighScoresState, which manages the high scores screen 
 *
 * The HighScoresState class handles the display of top scores, player score, and related UI.
 * Inherits from GameState and manages its own background, score texts, and button initialization.
 */
#pragma once
#include "GameState.h"
#include "HighScoresManager.h"
#include <vector>
#include <SFML/Graphics.hpp>

class HighScoresState : public GameState
{
public:
    HighScoresState(GameManager* gameManager);

    void update(float deltaTime) override;
    void render() const override;
    void handleInput(const sf::Event& event) override;

private:
    virtual void buttonsInit() override;
    void initScoreTexts();
    void berryInit();

    sf::Sprite m_background;

    std::vector<int> m_topScores;

    // Text members
    std::vector<sf::Text> m_scoreTexts;
    sf::Text m_noScoresText;
    sf::Text m_yourScoreText;
    const int m_numHighestScores = 5;

    sf::Sprite m_berry;

    sf::Vector2f m_berryNoScoresPos = { 0.f, 0.f };
    sf::Vector2f m_berryScoresPos = { 0.f, 0.f };
};
