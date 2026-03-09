#include "ResumeCommand.h"
#include "GameManager.h"

void ResumeCommand::execute()
{
    if (m_gameManager) GameManager::requestState(GameManager::StateRequest::Resume); // change state to resume
}
