#include "PauseState.h"
#include "GameManager.h"
#include "SimpleButton.h"
#include "HoverButton.h"
#include "TuggleButton.h"
#include <vector>
#include <memory>
#include "Pickables.h"

PauseState::PauseState(GameManager* gameManager)
    : GameState(gameManager)
{
    buttonsInit();
    createOverlay();
}

void PauseState::update(const float deltaTime)
{
    (void)deltaTime;
    GameState::updateButtons();
}

void PauseState::render() const
{
    if (!m_gameManager) return;

    auto& window = m_gameManager->getWindow();

    if (m_gameManager->isPaused())
        m_gameManager->renderPausedState();

    window.setView(window.getDefaultView());
    window.draw(m_overlay);

    GameState::renderButtons();
}

void PauseState::handleInput(const sf::Event& event)
{
    GameState::handleButtonsInput(event);
}

void PauseState::onEnter()
{
   if (m_gameManager) m_gameManager->onEnter();
}

void PauseState::onExit()
{
    if (m_gameManager) m_gameManager->stopPausedStateSounds();
}

void PauseState::mute()
{
    if (m_gameManager) m_gameManager->mutePausedState();
}

void PauseState::unmute()
{
    if (m_gameManager) m_gameManager->unmutePausedState();
}

void PauseState::quit()
{
    if (m_gameManager)
    {
        m_gameManager->stopPausedStateSounds();
        m_gameManager->resetGame();
    }
    Pickables::stopSpecialGiftSound();
    GameManager::requestState(GameManager::StateRequest::Menu);  // change to menu state
}

// Creates a semi-transparent black overlay covering the entire window
void PauseState::createOverlay()
{
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
    m_overlay.setSize(windowSize);
    m_overlay.setFillColor(sf::Color(0, 0, 0, 128));
    m_overlay.setPosition(0, 0);
}

void PauseState::buttonsInit()
{
    m_buttons.clear();

    // Resume button
    m_buttons.push_back(std::make_unique<SimpleButton>(
        ButtonData({ 0.25f, 0.25f }, { 0.2f, 0.37f }, "ResumeButton"),
        std::make_unique<ResumeCommand>(m_gameManager)
    ));

    m_buttons.push_back(std::make_unique<SimpleButton>(
        ButtonData({ 0.25f, 0.25f }, { 0.55f, 0.37f }, "QuitButton"),
        std::make_unique<QuitButtonCommand>(m_gameManager)
    ));

    createMuteButton();
}
