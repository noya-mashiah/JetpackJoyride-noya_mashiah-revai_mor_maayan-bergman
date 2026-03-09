#include "HelpCommand.h"
#include "GameManager.h"

void HelpCommand::execute()
{
	GameManager::requestState(GameManager::StateRequest::Help);  //change to help state
}
