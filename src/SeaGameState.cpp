#include "SeaGameState.h"
#include "GameManager.h"

SeaGameState::SeaGameState(GameManager* gameManager,
	const std::string& musicName) : RunGameState(gameManager, musicName, 37)
{
	//Creates a text object (timer) with screen-relative size and position
	m_timerText = GraphicUtilities::createNormalizedText("1:00", 0.05f,
								0.45f, 0.035f, sf::Color::Cyan);

	updateTimerText();
}

void SeaGameState::update(const float deltaTime)
{
	if (m_gameManager)
	{
		m_gameManager->update(deltaTime);
		m_gameManager->updateWaves();
		
		m_waterTimer += deltaTime;
		updateTimerText();

		if (m_waterTimer > WaterDuration)    // timer is over - change to land state
			m_gameManager->requestState(GameManager::StateRequest::Land);
	}
}

void SeaGameState::render() const
{
	if (m_gameManager)
	{
		m_gameManager->renderWalls();
		m_gameManager->renderWaves();
		m_gameManager->render();
	}
	renderTextTimer();
	GameState::renderButtons();
}

void SeaGameState::updateTimerText()
{
	int secondsLeft = static_cast<int>(WaterDuration - m_waterTimer);
	if (secondsLeft < 0) secondsLeft = 0;

	// Convert to minutes and seconds
	int minutes = secondsLeft / 60;
	int seconds = secondsLeft % 60;

	// Format as MM:SS
	char buffer[8];
	snprintf(buffer, sizeof(buffer), "%d:%02d", minutes, seconds);

	m_timerText.setString(buffer);
}

void SeaGameState::renderTextTimer() const
{
	if (!m_gameManager) return;

	auto& window = m_gameManager->getWindow();
	auto& view = window.getView();
	window.setView(window.getDefaultView());
	window.draw(m_timerText);
	window.setView(view);
}

void SeaGameState::onEnter()
{
	playMusic();
	RunGameState::onEnter();
}

void SeaGameState::onExit()
{
	ResourcesManager::getInstance().getMusic("SeaWaves").stop();
	RunGameState::onExit();
}

void SeaGameState::playMusic()
{
	auto& musicWaves = ResourcesManager::getInstance().getMusic("SeaWaves");
	musicWaves.setLoop(true);
	musicWaves.play();
}
