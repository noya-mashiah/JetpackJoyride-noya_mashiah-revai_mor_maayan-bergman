#include "HelpRightCommand.h"
#include "GameManager.h"

void HelpRightCommand::execute()
{
	if (m_gameManager) m_gameManager->moveHelpRight();
}
