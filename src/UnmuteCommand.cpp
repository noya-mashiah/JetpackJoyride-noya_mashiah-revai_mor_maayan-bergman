#include "UnmuteCommand.h"
#include "GameManager.h"

void UnmuteCommand::execute()
{
	if (m_gameManager) m_gameManager->unmute();
}
