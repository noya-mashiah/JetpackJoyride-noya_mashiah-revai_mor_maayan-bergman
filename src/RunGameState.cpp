#include "RunGameState.h"
#include "GameManager.h"
#include "SimpleButton.h"
#include "HoverButton.h"
#include "TuggleButton.h"
#include <vector>
#include <memory>

RunGameState::RunGameState(GameManager* gameManager,
							const std::string& musicName,
							const float soundVol)
	: GameState(gameManager, musicName, soundVol)
{
	buttonsInit();
}

void RunGameState::handleInput(const sf::Event& event)
{
	if (m_gameManager) m_gameManager->handleInput(event);

	GameState::handleButtonsInput(event);
}

void RunGameState::onEnter()
{
	m_gameManager->onEnter();
	GameState::onEnter();
}

void RunGameState::onExit()
{
	m_gameManager->onExit();
	GameState::onExit();
}

void RunGameState::pause()
{
	m_gameManager->onExit();
}

// for the option button on the playing screen 
void RunGameState::buttonsInit()
{
	m_buttons.clear();

	m_buttons.push_back(std::make_unique<SimpleButton>(
		ButtonData({ 0.06f, 0.1f }, { 0.92f, 0.02f }, "GameSettingButton"),
		std::make_unique<PauseCommand>(m_gameManager)
	));
}
