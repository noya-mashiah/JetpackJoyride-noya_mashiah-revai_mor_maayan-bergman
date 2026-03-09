#include "Player.h"

using changeStateFunc = std::function<void()>;

Player::Player(const GameObjectParams& params)
	: MovingObject(params)
{
	m_state = std::make_unique<RegularPlayerState>(m_sprite, m_animation);
}

void Player::render(sf::RenderWindow& window) const
{
	MovingObject::render(window);
	
	if (m_state) m_state->render(window);
}

void Player::update(const sf::View& view, const float deltaTime)
{
	move(view, deltaTime); 

	m_animation.update(deltaTime);

	if (m_state) m_state->update(view, deltaTime);
}

void Player::processHit()
{
	if (m_state) m_state->processHit(*this);
}

void Player::changeToRegularState()
{
	m_state->onExit();
	m_state = std::make_unique<RegularPlayerState>(m_sprite, m_animation);
	m_state->onEnter();
}

void Player::changeToRobotState()
{
	m_state->onExit();
	m_state = std::make_unique<RobotPlayerState>(m_sprite, m_animation);
	m_state->onEnter();
}

void Player::changeToUpsideDownState()
{
	m_state->onExit();
	m_state = std::make_unique<UpsideDownPlayerState>(m_sprite, m_animation);
	m_state->onEnter();
}

void Player::changeToBirdState()
{
	m_state->onExit();
	m_state = std::make_unique<BirdPlayerState>(m_sprite, m_animation);
	m_state->onEnter();
}

void Player::changeToDinosaurState()
{
	m_state->onExit();
	m_state = std::make_unique<DinosaurPlayerState>(m_sprite, m_animation);
	m_state->onEnter();
}

void Player::changeToSurferState()
{
	m_state->onExit();
	m_state = std::make_unique<SurferPlayerState>(m_sprite, m_animation);
	m_state->onEnter();
}

void Player::onGasTankCollected()
{
	if (m_state) m_state->onGasTankCollected();
}

void Player::onMeatCollected()
{
	if (m_state) m_state->onMeatCollected();
}

void Player::onCoinCollected()
{
	int tempCounter = m_coinsCounter;

	if (m_state) m_state->onCoinCollected(tempCounter);

	m_coinsCounter = tempCounter;
}

void Player::onPearlCollected()
{
	int tempCounter = m_coinsCounter;

	if (m_state) m_state->onPearlCollected(tempCounter);

	m_coinsCounter = tempCounter;
}

void Player::onShellCollected()
{
	if (m_state) m_state->onShellCollected();
}

bool Player::canCollectPowerUpBox() const
{
	if (!m_state) return false;

	return m_state->canCollectPowerUpBox();
}

void Player::setState(std::unique_ptr<PlayerState> newState)
{
	m_state->onExit();
	m_state = std::move(newState);
	m_state->onEnter();
}

std::unique_ptr<Pickables> Player::addStateGift(const sf::Vector2f& scrollOffset)
{
	std::unique_ptr<Pickables> newGift = m_state->addGift(scrollOffset);
	return std::move(newGift);
}

void Player::reset()
{
	m_state->onExit();
	m_state = std::make_unique<RegularPlayerState>(m_sprite, m_animation);
	m_state->onEnter();
	m_coinsCounter = 0;
	auto params = RegularPlayerState::getDefaultValues();
}

int Player::getCoinsCounter() const
{
	return m_coinsCounter;
}

float Player::getViewSpeedMultiplier() const
{
	return m_state->getViewSpeedMultiplier();
}

bool Player::isInvincible() const
{
	return m_state->isInvincible();
}

void Player::onEnter()
{
	m_state->onEnter();
}

void Player::onExit()
{
	m_state->onExit();
}

void Player::saveSoundState()
{
	if (m_state) m_state->saveSoundState();
}

void Player::restoreSoundState()
{
	if (m_state) m_state->restoreSoundState();
}

void Player::handleInput(const sf::Event& event)
{
	if (m_state) m_state->handleInput(event);
}

void Player::move(const sf::View& view, const float deltaTime)
{
	if (m_state) m_state->move(view, deltaTime);
}
