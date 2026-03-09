#include "SurferPlayerState.h"
#include "Player.h"
#include "GraphicUtilities.h"
#include "Consts.h"
#include "GameManager.h"

SurferPlayerState::SurferPlayerState(sf::Sprite& sprite, Animation& animation)
	: PlayerState(sprite, animation)
{
	spriteAnimationInit(SurferPlayerState::getDefaultValues());
	init();
	initializeBubbles();
}

void SurferPlayerState::handleInput(const sf::Event& event)
{
	if (!m_command) return;

	if (event.key.code == sf::Keyboard::Space)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			m_command->setSpacePressed(true);
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			m_command->setSpacePressed(false);
		}
	}
}

void SurferPlayerState::update(const sf::View& view, const float deltaTime)
{
	if (m_isLanding) {
		updateSmoothLanding(view, deltaTime);
		return;
	}

	checkIfAnimationUpdateRequired();
	
	// If player is underwater, update bubbles and set semi-transparent color
	if (isUnderWater())
	{
		for (auto& b : m_bubbles)
			b->update(view, deltaTime);

		sf::Color semiTransparent(255, 255, 255, 200);
		m_sprite.setColor(semiTransparent);
	}
	else
		m_sprite.setColor(sf::Color(255, 255, 255, 255)); // If not underwater, set color to fully opaque

	// timer for a gap between gifts
	if (m_curGiftCount < m_maxGiftCount) m_specialGiftTimer += deltaTime;
}

void SurferPlayerState::render(sf::RenderWindow& window) const
{
	if (isUnderWater())
		for (const auto& b : m_bubbles)
			b->render(window);
}

void SurferPlayerState::move(const sf::View& view, const float deltaTime)
{
	if (!m_isLanding && m_command) m_command->execute(view, deltaTime);
}

GameObjectParams SurferPlayerState::getDefaultValues()
{
	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

	return GameObjectParams("Surfing", { 0.15f ,0.25f },
		sf::Vector2f(GraphicUtilities::getWindowSize().x * playerRelativeX,
			GraphicUtilities::getFloorY() - windowSize.x * 0.02f), // Initial position at the floor 
		9, 0, 8, 0.2f, true);
}

std::unique_ptr<Pickables> SurferPlayerState::addGift(const sf::Vector2f& scrollOffset)
{
	if (m_curGiftCount < m_maxGiftCount && m_specialGiftTimer > maxDuration)
	{
		m_curGiftCount++;
		m_specialGiftTimer = 0.f;

		std::unique_ptr<Pickables> newShell = GameObjectFactory::createSpecialGift(scrollOffset,
			Shell::getDefaultParams({ 0.f, 0.f }));
		return newShell;
	}
	else return nullptr;
}

// for collision
void SurferPlayerState::processHit(Player& player)
{
	(void)player;
	GameManager::requestState(GameManager::StateRequest::Land);
}

void SurferPlayerState::onShellCollected()
{
	Shell::playPickedSound();
}

// for pausing
void SurferPlayerState::saveSoundState()
{
	PlayerState::saveSoundState();
	for (auto& b : m_bubbles)
		b->saveState();
}

// for stoping pausing 
void SurferPlayerState::restoreSoundState()
{
	PlayerState::restoreSoundState();
	for (auto& b : m_bubbles)
		b->restoreState();
}

void SurferPlayerState::init()
{
	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

	m_floorY = GraphicUtilities::getFloorY() - windowSize.x * 0.02f;
	m_ceilingY = GraphicUtilities::getCeilingY(); // Get the actual ceiling Y coordinate 

	m_command = std::make_unique<WaveSurfCommand>(m_sprite, 2000.f, -400.f, m_floorY, m_ceilingY);
}

// Sets animation frame range and loop flag based on current surfer movement
void SurferPlayerState::updateAnimationParams(int& firstFrame, int& lastFrame,
											  bool& shouldLoop) const
{
	int currentMovementPhase = m_command->getAnimationPhase();

	switch (currentMovementPhase)
	{
	case WAVE_ON_FLOOR:
		break;
	case WAVE_ASCENDING:
	{
		firstFrame = 1;
		lastFrame = 2;
		break;
	}
	case WAVE_DIVING:
	case WAVE_DESCENDING:
	{
		firstFrame = 3;
		lastFrame = 7;
		break;
	}
	case WAVE_IDLE:
	default:
		// Fallback or error handling for unexpected phases 
		lastFrame = 8;
		shouldLoop = true;
		break;
	}
}

void SurferPlayerState::checkIfAnimationUpdateRequired()
{
	bool shouldLoop = false;
	int firstFrame = 0;
	int lastFrame = 0;

	updateAnimationParams(firstFrame, lastFrame, shouldLoop);

	// Only update animation parameters if the effective animation phase OR its parameters have changed
	// This prevents redundant setAnimation calls and allows animation to play through.
	if (firstFrame != m_currentFirstFrame ||
		lastFrame != m_currentLastFrame ||
		shouldLoop != m_currentShouldLoop)
	{
		// Store current animation parameters
		m_currentFirstFrame = firstFrame;
		m_currentLastFrame = lastFrame;
		m_currentShouldLoop = shouldLoop;

		m_animation.setAnimation(GameObjectParams("Surfing", { 0.15f ,0.25f },
			m_sprite.getPosition(), 9, firstFrame, lastFrame, 0.2f, shouldLoop));
	}
}

void SurferPlayerState::initializeBubbles()
{
	initializeSwirlItems(m_bubbles, GameObjectParams("Bubble", { 0.03f ,0.07f }, m_sprite.getPosition(),
						 8, 0, 7, 0.7f, true), true, "BubbleSound");

	for (auto& b : m_bubbles)
		b->applyTransparency();
}

bool SurferPlayerState::isUnderWater() const
{
	return (m_sprite.getPosition().y > m_floorY * 0.7f);
}
