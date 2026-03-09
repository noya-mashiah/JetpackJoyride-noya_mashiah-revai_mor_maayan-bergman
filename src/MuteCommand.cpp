#include "MuteCommand.h"
#include "GameManager.h"

void MuteCommand::execute()
{
	if (m_gameManager) m_gameManager->mute();
}
