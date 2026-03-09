#include "DiePlayerState.h"
#include "GameManager.h"
#include "HighScoresManager.h"
#include <thread>        // For std::this_thread
#include <chrono>        // For std::chrono::millisec

DiePlayerState::DiePlayerState(sf::Sprite& sprite, Animation& animation)
	: PlayerState(sprite, animation)
{
	spriteAnimationInit(DiePlayerState::getDefaultValues());
	init();
}

void DiePlayerState::handleInput(const sf::Event& event) { (void)event; }

void DiePlayerState::update(const sf::View& view, const float deltaTime)
// Updates movement, triggers death animation, sound, score saving, and game over transition.
{
	move(view, deltaTime);

	if (m_command && !m_command->getIsLanding() && !m_hasRequestedToDie)
	{
		m_hasRequestedToDie = true;
		m_soundState.play();

		m_animation.setAnimation(GameObjectParams("BerryDead", { 0.07f ,0.17f },
			sf::Vector2f(GraphicUtilities::getWindowSize().x * playerRelativeX,
				GraphicUtilities::getFloorY()),
			1, 0, 0, 6.f, false));

		int distanceInMeters = static_cast<int>(m_sprite.getPosition().x);
		HighScoresManager::addPlayerScore(distanceInMeters);

		GameManager::requestState(GameManager::StateRequest::GameOver);
	}
}

void DiePlayerState::render(sf::RenderWindow& window) const { (void)window; }

void DiePlayerState::move(const sf::View& view, const float deltaTime) 
{
	if (m_command) m_command->execute(view, deltaTime);
}

GameObjectParams DiePlayerState::getDefaultValues()
{
	return GameObjectParams("BerryHit", { 0.07f ,0.17f },
		sf::Vector2f(GraphicUtilities::getWindowSize().x * playerRelativeX,
			GraphicUtilities::getFloorY()),
		4, 0, 3, 0.2f, false);
}

void DiePlayerState::processHit(Player& player) { (void)player; }

bool DiePlayerState::canCollectPowerUpBox() const { return false; }

void DiePlayerState::init()
// Initializes floor / ceiling positions, die command, and sound.
{
	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

	m_floorY = GraphicUtilities::getFloorY() + windowSize.x * 0.05f;
	m_ceilingY = GraphicUtilities::getCeilingY();

	m_command = std::make_unique<DieCommand>(m_sprite, 800.f, 0.f, m_floorY);
	m_floorSoundName = "HitSound";
	m_soundState = SoundState(m_floorSoundName);
	m_soundState.setVolume(80);
}

