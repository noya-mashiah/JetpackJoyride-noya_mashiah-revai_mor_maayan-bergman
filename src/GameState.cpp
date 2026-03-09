
#include "GameState.h"
#include "GameManager.h"

GameState::GameState(GameManager* gameManager, const std::string& musicName, const float soundVol)
	: m_gameManager(gameManager), m_musicName(musicName), m_soundVolume(soundVol) {}

void GameState::mute()
{
	if (m_musicName == " ") return;
	ResourcesManager::getInstance().getMusic(m_musicName).pause();
}

void GameState::unmute()
{
	if (m_musicName == " ") return;
	ResourcesManager::getInstance().getMusic(m_musicName).play();
}

void GameState::onEnter()
{
	if (m_musicName == " ") return;
	auto& music = ResourcesManager::getInstance().getMusic(m_musicName);
	music.setLoop(true);
	music.setVolume(m_soundVolume);

	if (!m_gameManager->isMuted()) music.play();
}

void GameState::onExit()
{
	if (m_musicName == " ") return;
	ResourcesManager::getInstance().getMusic(m_musicName).stop();
}

void GameState::pause()
{
	mute();
}

void GameState::resume()
{
	if (!m_gameManager->isMuted())
		ResourcesManager::getInstance().getMusic(m_musicName).play();
}

void GameState::updateButtons()
{
	if (m_gameManager)
		for (auto& b : m_buttons)
			b->update(m_gameManager->getWindow());
}

void GameState::renderButtons() const
{
	if (m_gameManager)
		for (const auto& b : m_buttons)
			b->render(m_gameManager->getWindow());
}

void GameState::handleButtonsInput(const sf::Event& event)
{
	if (m_gameManager)
		for (auto& b : m_buttons)
			b->handleEvent(event, m_gameManager->getWindow());
}

void GameState::backgroundInit(sf::Sprite& background, const std::string& textureName)
{
	background.setPosition({ 0, 0 });
	auto& inst = ResourcesManager::getInstance();
	background.setTexture(inst.getTexture(textureName));
	background.setScale(GraphicUtilities::getBackgroundScale(textureName));
}

void GameState::createMuteButton(const sf::Vector2f& windowScale, const sf::Vector2f& pos)
{
	if (!m_gameManager) return;

	if (!m_gameManager->isMuted())
	{
		createTuggleButton(windowScale, pos,
			"MuteOff", "MuteOn",
			std::make_unique<UnmuteCommand>(m_gameManager),
			std::make_unique<MuteCommand>(m_gameManager));
	}
	else
	{
		createTuggleButton(windowScale, pos,
			"MuteOn", "MuteOff",
			std::make_unique<MuteCommand>(m_gameManager),
			std::make_unique<UnmuteCommand>(m_gameManager));
	}
}

void GameState::createTuggleButton(const sf::Vector2f& windowScale, const sf::Vector2f& pos,
									const std::string& offName, const std::string& onName,
									std::unique_ptr<CommandButton> commandOff, 
									std::unique_ptr<CommandButton> commandOn)
	// Creates a toggle button with custom on/off states and commands.
{
	m_buttons.push_back(std::make_unique<ToggleButton>(
		ButtonData(windowScale, pos, offName, onName),
		std::move(commandOff), std::move(commandOn)));
}
