/**
 *  Controller.h
 *  Manages the main game logic, player, and game objects.
 *
 * The Controller class acts as the central coordinator for gameplay.
 * It manages the player character, handles input, updates and renders all game objects,
 * and controls object creation and game state transitions.
 *
 *  Uses composition to manage both the player and the GameObjectManager.
 */
#pragma once
#include "GameObjectManager.h"

#include "Pickables.h"

class Controller
{
public:
	Controller();

	void update(const sf::View& view, const float deltaTime);

	void render(sf::RenderWindow& window) const;

	void handleInput(const sf::Event& event);

	void createObjects(const sf::Vector2f& scrollOffSet, const float deltaTime);

	void reset();

	int getCoinsAmount() const;

	float getDistancePassed() const;

	float getViewSpeedMultiplier() const;

	void clearAllButLamps();

	void revertPlayerToRegularState();

	void setObjectCreationEnabled(const bool enabled);

	void onEnter();

	void onExit();

	void saveSoundState();

	void restoreSoundState();

private:

	Player m_player;

	GameObjectManager m_gameObjectsManager;
};
