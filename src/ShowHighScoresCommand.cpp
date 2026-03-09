#include "ShowHighScoresCommand.h"
#include "GameManager.h"

void ShowHighScoresCommand::execute()
{
    GameManager::requestState(GameManager::StateRequest::scoreBorad);  // change state to scoreBoard
}
