/**
 *  GameObjectManager.h
 *  Handles creation, updating, rendering, and cleanup of all dynamic game objects.
 *
 * The GameObjectManager class manages collections of enemies, obstacles, pickables, lamps, and decorative objects.
 * It is responsible for their lifecycle, including creation, updates, rendering, collision detection, and removal.
 *
 *  Uses std::list and unique_ptr for efficient object management and memory safety.
 * Provides utility functions for batch operations on all managed objects.
 */
#pragma once
#include <list>
#include <memory>
#include <functional>
#include "MovingObject.h"
#include "StaticObject.h"
#include "GameObjectFactory.h"
#include "Coin.h"
#include "LaserObstacle.h"
#include "Missile.h"
#include "PowerUpBox.h"
#include "Shell.h"
#include "CollisionManager.h"
#include "Collision.h"
#include "Player.h"
#include "DecorativeMovingObject.h"
#include "ProjectileEnemy.h"

class GameObjectManager
{
public:
	GameObjectManager() = default;

	void renderAll(sf::RenderWindow& window) const;

	void updateAll(const sf::View& view, const float deltaTime,
				   Player& player); 
	void reset();

	void createObjects(const sf::Vector2f& scrollOffSet, const float deltaTime, Player& player);

	void clearAllButLamps();

	void setObjectCreationEnabled(const bool enabled);
	
private:

	void addObstcales(const sf::Vector2f& scrollOffSet, const float deltaTime);
	
	void addPickables(const sf::Vector2f& scrollOffSet, const float deltaTime);	
	
	void addDecor(const sf::Vector2f& scrollOffSet, const float deltaTime);
	
	void addLamps(const sf::Vector2f& scrollOffSet, const float deltaTime);

	void addNewMovingDecor(const sf::Vector2f& scrollOffSet, const float deltaTime);

	void addEnemies(const sf::Vector2f& playerPos, const sf::Vector2f& scrollOffSet,
					const float deltaTime);

	template<typename TContainer, typename TPredicate>
	inline void cleanListByCondition(TContainer& list, TPredicate shouldRemove);

	template<typename TContainer>
	void updateList(TContainer& list, const sf::View& view, const float deltaTime);

	template<typename TContainer>
	void renderList(const TContainer& list, sf::RenderWindow& window) const;

	void checkCollisions(const sf::View& view, Player& player);

	void addSpecialGift(const Shell* shellPtr, const sf::View& view);

	void cleanupAll(const sf::View& view);

	void addGiftAccordingToState(const sf::Vector2f& scrollOffSet, Player& player);

	std::list<std::unique_ptr<Pickables>> m_pickables; 
	std::list<std::unique_ptr<LaserObstacle>> m_obstacles;
	std::list<std::unique_ptr<Enemy>> m_enemies;
	std::list<std::unique_ptr<StaticObject>> m_lamps;
	std::list<std::unique_ptr<DecorativeMovingObject>> m_decoratives;
	
	bool m_createObjects = true;
};

template<typename TContainer, typename TPredicate>
inline void GameObjectManager::cleanListByCondition(TContainer& list, TPredicate shouldRemove)
{
	for (auto it = list.begin(); it != list.end(); )
	{
		if (shouldRemove(*it))
			it = list.erase(it);
		else
			++it;
	}
}

template<typename TContainer>
inline void GameObjectManager::updateList(TContainer& list, const sf::View& view, const float deltaTime)
{
	for (auto& item : list)
		item->update(view, deltaTime);
}

template<typename TContainer>
inline void GameObjectManager::renderList(const TContainer& list, sf::RenderWindow& window) const
{
	for (const auto& item : list)
		item->render(window);
}
