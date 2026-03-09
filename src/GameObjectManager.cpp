#include "GameObjectManager.h"
#include "Exceptions.h"

void GameObjectManager::renderAll(sf::RenderWindow& window) const
{
	renderList(m_lamps, window);
	renderList(m_decoratives, window);
	renderList(m_pickables, window);
	renderList(m_obstacles, window);
	renderList(m_enemies, window);
}

void GameObjectManager::updateAll(const sf::View& view, const float deltaTime, 
								  Player& player)
{
	checkCollisions(view, player);

	cleanupAll(view);

	updateList(m_decoratives, view, deltaTime);
	updateList(m_lamps, view, deltaTime);
	updateList(m_pickables, view, deltaTime);
	updateList(m_obstacles, view, deltaTime);
	updateList(m_enemies, view, deltaTime);
}

void GameObjectManager::addObstcales(const sf::Vector2f& scrollOffSet, const float deltaTime)
// Adds a new obstacle to the game if created.
{
	auto newObstacle = GameObjectFactory::createNewObstacles(scrollOffSet, deltaTime);

	if (newObstacle) m_obstacles.push_back(std::move(newObstacle));
}

void GameObjectManager::addPickables(const sf::Vector2f& scrollOffSet, const float deltaTime)
{
	auto newPickablesVec = GameObjectFactory::createNewPickables(scrollOffSet, deltaTime);

	if (!newPickablesVec.empty())
		m_pickables.insert(m_pickables.end(),
			std::make_move_iterator(newPickablesVec.begin()), std::make_move_iterator(newPickablesVec.end()));
}

void GameObjectManager::addDecor(const sf::Vector2f& scrollOffSet, const float deltaTime)
{
	addLamps(scrollOffSet, deltaTime);

	addNewMovingDecor(scrollOffSet, deltaTime);
}

void GameObjectManager::addLamps(const sf::Vector2f& scrollOffSet, const float deltaTime)
{
	auto newLampVec = GameObjectFactory::createNewLamps(scrollOffSet, deltaTime);

	if (!newLampVec.empty())
		m_lamps.insert(m_lamps.end(),
			std::make_move_iterator(newLampVec.begin()), std::make_move_iterator(newLampVec.end()));
}

void GameObjectManager::addNewMovingDecor(const sf::Vector2f& scrollOffSet, const float deltaTime)
{
	auto newDecorVec = GameObjectFactory::createNewDecoratives(scrollOffSet, deltaTime);

	if (!newDecorVec.empty())
		m_decoratives.insert(m_decoratives.end(),
			std::make_move_iterator(newDecorVec.begin()), std::make_move_iterator(newDecorVec.end()));
}

void GameObjectManager::addEnemies(const sf::Vector2f& playerPos, const sf::Vector2f& scrollOffSet, const float deltaTime)
{
	auto newEnemiesVec = GameObjectFactory::createNewEnemies(playerPos, scrollOffSet, deltaTime);

	if (!newEnemiesVec.empty())
		m_enemies.insert(m_enemies.end(),
			std::make_move_iterator(newEnemiesVec.begin()), std::make_move_iterator(newEnemiesVec.end()));
}

void GameObjectManager::reset()
{
	m_lamps.clear();
	clearAllButLamps();
	m_createObjects = true;
}

void GameObjectManager::createObjects(const sf::Vector2f& scrollOffSet, const float deltaTime,
									  Player& player)
{
	if (!m_createObjects) return;

	addDecor(scrollOffSet, deltaTime);
	addObstcales(scrollOffSet, deltaTime);
	addPickables(scrollOffSet, deltaTime);
	addEnemies(player.getPosition(), scrollOffSet, deltaTime);

	addGiftAccordingToState(scrollOffSet, player);
}

void GameObjectManager::clearAllButLamps()
// Clears all objects except for lamps.
{
	m_decoratives.clear();
	m_obstacles.clear();
	m_pickables.clear();
	m_enemies.clear();
}

void GameObjectManager::setObjectCreationEnabled(const bool enabled)
{
	m_createObjects = enabled;
}

void GameObjectManager::checkCollisions(const sf::View& view, Player& player)
// Checks for collisions between the player and all objects, and processes them.
{
	if (!m_createObjects) return;

	auto intersectsPlayer = [&](auto& obj)
		{
			if (Collision::pixelPerfectTest(player.getSprite(), obj->getSprite(), 128))
			{
				try {
					processCollision(player, *obj);
					
					if (auto shellPtr = dynamic_cast<Shell*>(obj.get())) 
					{
						addSpecialGift(shellPtr, view); 

						return false; // we want the shell to open and reveal a beautiful pearl, 
									  // not to disappear :)
					}

					return true;
				}
				catch (const UnknownCollisionException&) {
					return false;
				}
			}

			return false;
		};

	cleanListByCondition(m_pickables, intersectsPlayer);
	cleanListByCondition(m_enemies, intersectsPlayer);
	cleanListByCondition(m_obstacles, intersectsPlayer);
}

void GameObjectManager::addSpecialGift(const Shell* shellPtr, const sf::View& view)
//Adds a special gift depending on the player status
{
	if (!shellPtr) return;
	auto newGifts = shellPtr->addBonusGift(view.getCenter());
	if (!newGifts.empty()) {
		m_pickables.insert(
			m_pickables.end(),
			std::make_move_iterator(newGifts.begin()),
			std::make_move_iterator(newGifts.end())
		);
	}
}

void GameObjectManager::cleanupAll(const sf::View& view)
{
	auto outOfView = [&](const auto& obj) { return obj->isOutOfWindowView(view); };

	cleanListByCondition(m_decoratives, outOfView);
	cleanListByCondition(m_lamps, outOfView);
	cleanListByCondition(m_pickables, outOfView);
	cleanListByCondition(m_obstacles, outOfView);
	cleanListByCondition(m_enemies, outOfView);
}

void GameObjectManager::addGiftAccordingToState(const sf::Vector2f& scrollOffSet, Player& player)
{
	std::unique_ptr<Pickables> newGift = player.addStateGift(scrollOffSet);

	if (newGift)   //check for states with no special gifts 
		m_pickables.push_back(std::move(newGift));
}
