#include "GameOverState.h"
#include "GameManager.h"
#include "SimpleButton.h"
#include "HoverButton.h"
#include "TuggleButton.h"
#include <vector>
#include <memory>

GameOverState::GameOverState(GameManager* gameManager, const std::string& musicName)
    : GameState(gameManager, musicName, 75)
{
    buttonsInit();

    createOverlay();
}

void GameOverState::update(float deltaTime)
{
    if (m_gameManager) m_gameManager->update(deltaTime);

    GameState::updateButtons();
}

void GameOverState::render() const
{
    if (!m_gameManager) return;

    auto& window = m_gameManager->getWindow();

    m_gameManager->renderWalls();
    m_gameManager->render();

    window.setView(window.getDefaultView());
    window.draw(m_overlay);

    GameState::renderButtons();
}

void GameOverState::handleInput(const sf::Event& event)
{
    GameState::handleButtonsInput(event);
}

void GameOverState::createOverlay()
// Creates the semi-transparent overlay for the game over screen.
{
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
    m_overlay.setSize(windowSize);
    m_overlay.setFillColor(sf::Color(0, 0, 0, 128));
    m_overlay.setPosition(0, 0);
}

void GameOverState::buttonsInit()
{
    m_buttons.clear();

    m_buttons.push_back(std::make_unique<HoverButton>(
        ButtonData({ 0.3f, 0.28f }, { 0.35f, 0.35f }, "QuitOff", "QuitOn"),
        std::make_unique<ReturnToMenuCommand>(m_gameManager)
    ));

    createMuteButton();
}
