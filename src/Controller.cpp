#include "Controller.h"

Controller::Controller()
: m_player(RegularPlayerState::getDefaultValues()) {}

void Controller::update(const sf::View& view, const float deltaTime)
{
	m_player.update(view, deltaTime);

	m_gameObjectsManager.updateAll(view, deltaTime, m_player);
}

void Controller::render(sf::RenderWindow& window) const
{
	m_gameObjectsManager.renderAll(window);

	m_player.render(window);
}

void Controller::handleInput(const sf::Event& event)
{
	m_player.handleInput(event);
}

void Controller::createObjects(const sf::Vector2f& scrollOffSet,
							   const float deltaTime)
{
	m_gameObjectsManager.createObjects(scrollOffSet, deltaTime, m_player);
}

void Controller::reset()
{
	m_player.reset();
	m_gameObjectsManager.reset();
}

int Controller::getCoinsAmount() const
{
	return m_player.getCoinsCounter();
}

float Controller::getDistancePassed() const
{
	return m_player.getPosition().x;
}

float Controller::getViewSpeedMultiplier() const
{
	return m_player.getViewSpeedMultiplier();
}

void Controller::clearAllButLamps()
{
	m_gameObjectsManager.clearAllButLamps();
}

void Controller::revertPlayerToRegularState()
{
	m_player.changeToRegularState();
}

void Controller::setObjectCreationEnabled(const bool enabled)
{
	m_gameObjectsManager.setObjectCreationEnabled(enabled);
}

void Controller::onEnter()
{
	m_player.onEnter();
}

void Controller::onExit()
{
	m_player.onExit();
}

void Controller::saveSoundState()
{
	m_player.saveSoundState();
}

void Controller::restoreSoundState()
{
	m_player.restoreSoundState();
}
