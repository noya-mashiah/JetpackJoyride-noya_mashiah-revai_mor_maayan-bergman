#include "LandGameState.h"
#include "GameManager.h"

LandGameState::LandGameState(GameManager* gameManager, 
							const std::string& musicName)
	: RunGameState(gameManager, musicName, 55) {}

void LandGameState::update(const float deltaTime)
{
	if (m_gameManager) m_gameManager->update(deltaTime);
}

void LandGameState::render() const
{
	if (m_gameManager)
	{
		m_gameManager->renderWalls();
		m_gameManager->render();
	}

	GameState::renderButtons();
}
