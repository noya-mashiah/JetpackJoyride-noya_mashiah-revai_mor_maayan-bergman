#include "ReturnToMenuCommand.h"
#include "GameManager.h"

void ReturnToMenuCommand::execute()
{
	GameManager::requestState(GameManager::StateRequest::Menu);  // change state to menu
}
