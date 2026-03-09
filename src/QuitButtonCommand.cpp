#include "QuitButtonCommand.h"
#include "GameManager.h"

void QuitButtonCommand::execute()
{
	if (m_gameManager) m_gameManager->quit();
}
