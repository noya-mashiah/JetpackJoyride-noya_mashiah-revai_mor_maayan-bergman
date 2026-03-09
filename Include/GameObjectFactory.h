/**
 * GameObjectFactory.h
 * Factory for creating all game objects, enemies, obstacles, and pickables.
 *
 * The GameObjectFactory class provides static methods to create all types of game objects,
 * using a registration map and context to control what is generated.
 * Supports dynamic, random, and pattern-based creation for gameplay variety.
 */
#pragma once
#include <vector>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include <map>
#include <string>
#include <functional>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "GeometryPhysicsUtilities.h"

// Forward declarations for classes used in this header
struct GameObjectParams;
class Obstacles;
class StaticObject;
class LaserComponent;
struct LaserConfig;
class Pickables;
class LaserObstacle;
class GameObject;
class Enemy;
class MovingObject;
class DecorativeMovingObject;

// Type definition for the factory map
typedef std::unordered_map<std::string, std::unique_ptr<GameObject>(*)(const GameObjectParams& params)> mymap;

class GameObjectFactory
{
public:

	enum class GameContext { Land, Sea};

	enum class MissilePattern { Single, ParallelPair, FollowingPair, ParallelQuad, FollowingQuad};

	static void setContext(GameContext ctx);

	static std::unique_ptr<GameObject> create(const std::string& name, const GameObjectParams& params);

	static bool registerIt(const std::string& name, std::unique_ptr<GameObject>(*f)(const GameObjectParams& params));

	// Methods to create various game elements, using scrollOffset and deltaTime for dynamic generation
	static std::vector<std::unique_ptr<Pickables>> createNewPickables(const sf::Vector2f& scrollOffset, const float deltaTime);
	static std::unique_ptr<LaserObstacle> createNewObstacles(const sf::Vector2f& scrollOffset, const float deltaTime);
	static std::vector<std::unique_ptr<Enemy>> createNewEnemies(const sf::Vector2f& playerPos, const sf::Vector2f& scrollOffset, const float deltaTime);
	static std::vector<std::unique_ptr<StaticObject>> createNewLamps(const sf::Vector2f& scrollOffset, const float deltaTime);
	static std::vector<std::unique_ptr<DecorativeMovingObject>> createNewDecoratives(const sf::Vector2f& scrollOffset, const float deltaTime);

	//--- Special gift related
	static std::unique_ptr<Pickables> createSpecialGift(const sf::Vector2f& scrollOffset,
		const GameObjectParams& params);
	
	//--- Pearl related
	static std::vector<std::unique_ptr<Pickables>> createPearls(const sf::Vector2f& shellPos, const sf::Vector2f& scrollOffset);

private:
	
	static GameContext m_context;

	//--- Moving Decoratives related
	static std::vector<std::unique_ptr<DecorativeMovingObject>> createDecoratives(const sf::Vector2f& scrollOffset,
																				  GameObjectParams& params,
																				  std::function<sf::Vector2f(const sf::Vector2f&)> getPosFunc,
																				  int range);

	static void createDecorative(std::vector<std::unique_ptr<DecorativeMovingObject>>& newScientists,
		const sf::Vector2f& scrollOffset, const float xOffSet, GameObjectParams& params,
		std::function<sf::Vector2f(const sf::Vector2f&)> getPosFunc);

	//--- Wall Lamp related
	static std::unique_ptr<StaticObject> createWallLamp(const sf::Vector2f& scrollOffset);

	//--- PowerUpBox related
	static std::vector<std::unique_ptr<Pickables>> createPowerUpBox(const sf::Vector2f& scrollOffset);

	//--- Coin related (these are now wrappers that call GeometryPhysicsUtilities for positions)
	static std::vector<std::unique_ptr<Pickables>> createCoinCircle(const sf::Vector2f& scrollOffset);
	static std::vector<std::unique_ptr<Pickables>> createCoinHeart(const sf::Vector2f& scrollOffset);
	static std::vector<std::unique_ptr<Pickables>> createCoinLine(const sf::Vector2f& scrollOffset);

	//--- Missile related
	static std::vector<std::unique_ptr<Enemy>> createSingleMissile(const sf::Vector2f& playerPos,
		const sf::Vector2f& scrollOffset);
	static std::vector<std::unique_ptr<Enemy>> CreateParallelMissilePair(const sf::Vector2f& playerPos,
		const sf::Vector2f& scrollOffset);
	static std::vector<std::unique_ptr<Enemy>> CreateFollowingMissilePair(const sf::Vector2f& playerPos,
		const sf::Vector2f& scrollOffset);
	static std::vector<std::unique_ptr<Enemy>> CreateParallelMissileQuad(const sf::Vector2f& playerPos,
		const sf::Vector2f& scrollOffset);
	static std::vector<std::unique_ptr<Enemy>> CreateFollowingMissileQuad(const sf::Vector2f& playerPos,
		const sf::Vector2f& scrollOffset);

	static std::vector<std::unique_ptr<Enemy>> createMissilePattern( const sf::Vector2f& playerPos,
		const sf::Vector2f& scrollOffset, MissilePattern pattern);

	static std::unique_ptr<Enemy> createMissile(const sf::Vector2f& playerPos,
		const sf::Vector2f& scrollOffset,
		const sf::Vector2f& addition);

	//--- Animal Enenies related
	static std::vector<std::unique_ptr<Enemy>> createBat(const sf::Vector2f& playerPos,
		const sf::Vector2f& scrollOffset);
	static std::vector<std::unique_ptr<Enemy>> createPiranha(const sf::Vector2f& playerPos,
		const sf::Vector2f& scrollOffset);
	static std::vector<std::unique_ptr<Enemy>> createProjectileEnemy(const GameObjectParams& enemyParams,
		const GameObjectParams& projectileParams, const std::string& projectileSoundName, const std::string& enemySoundName,
		const float projectileVol = 50, const float enemyVol = 50,
		const int startFrame = 0, const int renderFrame = 0);
	static std::vector<std::unique_ptr<Enemy>> createChicken(const sf::Vector2f& playerPos,
		const sf::Vector2f& scrollOffset);
	static std::vector<std::unique_ptr<Enemy>> createCrab(const sf::Vector2f& playerPos,
		const sf::Vector2f& scrollOffset);
	static std::vector<std::unique_ptr<Enemy>> createShark(const sf::Vector2f& playerPos,
		const sf::Vector2f& scrollOffset);
	static std::vector<std::unique_ptr<Enemy>> createEnemy(const GameObjectParams& params);

	//--- Lazer related
	static std::unique_ptr<LaserObstacle> createVerticalLazer(const struct LazerConfig& Laserparams);
	static std::unique_ptr<LaserObstacle> createHorizontalLazer(const struct LazerConfig& Laserparams);
	static std::unique_ptr<LaserObstacle> createDiagonalLazerLeft(const struct LazerConfig& Laserparams);
	static std::unique_ptr<LaserObstacle> createDiagonalLazerRight(const struct LazerConfig& Laserparams);
	static std::unique_ptr<LaserComponent> createLaserHead(const sf::Vector2f& headPos,
		const float angle, const float additionToAngle, const bool needToRotate);
	static std::unique_ptr<LaserComponent> createLaserBeam(const sf::Vector2f& topHeadPos, const sf::Vector2f& bottomHeadPos,
		const bool needToRotate, const float angle);

	//--- helpers
	static std::string getFishName();
	static sf::Vector2f getRandomPos(const sf::Vector2f& scrollOffset);
	static sf::Vector2f getUnderWaterPos(const sf::Vector2f& scrollOffset);
	static sf::Vector2f floorPos(const sf::Vector2f& scrollOffset);
	static sf::Vector2f wavesPos(const sf::Vector2f& scrollOffset);
	static void initializePearlHeartTemplate(std::vector<sf::Vector2f>& outTemplateVector,
											const sf::Vector2f& shellPosForTemplate);

	static mymap& getMap()
	{
		static mymap map;
		return map;
	}
};
