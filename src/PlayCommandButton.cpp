#include "PlayCommandButton.h"
#include "GameManager.h"

void PlayCommandButton::execute()
{
	if (m_gameManager) m_gameManager->resetGame();
}
