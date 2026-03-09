#include "HelpLeftCommand.h"
#include "GameManager.h"

void HelpLeftCommand::execute()
{
	if (m_gameManager) m_gameManager->moveHelpLeft(); 
}
