#include "PauseCommand.h"
#include "GameManager.h"

void PauseCommand::execute()
{
    if (m_gameManager) GameManager::requestState(GameManager::StateRequest::Pause); // change to pause state
}
