#include "GameObjectFactory.h"
#include <functional>
#include "Coin.h"
#include "LaserObstacle.h"
#include "MissileAlarm.h"
#include "Missile.h"
#include "PowerUpBox.h"
#include "Chicken.h"
#include "GasTank.h"
#include "WallLamp.h"
#include "Meat.h"
#include "Shell.h"
#include "Crab.h"
#include "Shark.h"
#include "Pearl.h"
#include "DecorativeMovingObject.h"
#include "ProjectileEnemy.h"
#include "LaserConfig.h"

GameObjectFactory::GameContext GameObjectFactory::m_context = GameObjectFactory::GameContext::Land;

void GameObjectFactory::setContext(GameContext ctx)
// Sets the current game context(Land or Sea), which determines what types of objects are generated.
{
	m_context = ctx;
}

// Creates a new game object by name using the registered factory map and provided parameters.
std::unique_ptr<GameObject> GameObjectFactory::create(const std::string& name,
                                                      const GameObjectParams& params)
{
    auto it = getMap().find(name);
    
    if (it == getMap().end())
        return nullptr;
    
    return it->second(params);
}

bool GameObjectFactory::registerIt(const std::string& name,
                    std::unique_ptr<GameObject>(*f)(const GameObjectParams& params))
{
	if (!f) return false;

	auto result = getMap().emplace(name, f);
	return result.second;
}

// Randomly creates a new laser obstacle (vertical, horizontal, or diagonal) based on the current context and deltaTime.
std::unique_ptr<LaserObstacle> GameObjectFactory::createNewObstacles(const sf::Vector2f& scrollOffset,
                                                                     const float deltaTime)
{
	if (m_context == GameContext::Sea) return {};

    std::unique_ptr<LaserObstacle> laser;

    LazerConfig laserParams(scrollOffset);

    using CreationFunc = std::unique_ptr<LaserObstacle>(*)(const LazerConfig& params);

    static std::unordered_map<int, CreationFunc> functionCollection =
    {
        {0, static_cast<CreationFunc>(&GameObjectFactory::createVerticalLazer)},
        {1, static_cast<CreationFunc>(&GameObjectFactory::createHorizontalLazer)},
        {2, static_cast<CreationFunc>(&GameObjectFactory::createDiagonalLazerLeft)},
        {3, static_cast<CreationFunc>(&GameObjectFactory::createDiagonalLazerRight)}
    };

    int range = std::max(4, 10 - static_cast<int>(deltaTime / 300.0f)); // Ensures the max range is at least 4
    int randomNumber = std::rand() % range;

	if (functionCollection.empty()) return {};

	auto it = functionCollection.find(randomNumber);
        if (it != functionCollection.end())
		return it->second(scrollOffset);
	return {};
}

// Randomly creates a new set of enemies based on the game context, player position, and deltaTime.
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::createNewEnemies(const sf::Vector2f& playerPos,
                                                                        const sf::Vector2f& scrollOffset,
                                                                        const float deltaTime)
{
	using CreationFunc = std::vector<std::unique_ptr<Enemy>>(*)(const sf::Vector2f&, const sf::Vector2f&);

	static const std::unordered_map<int, CreationFunc> landEnemyMap = {
        {0, static_cast<CreationFunc>(&GameObjectFactory::createSingleMissile)},
        {1, static_cast<CreationFunc>(&GameObjectFactory::CreateParallelMissilePair)},
        {2, static_cast<CreationFunc>(&GameObjectFactory::CreateFollowingMissilePair)},
        {3, static_cast<CreationFunc>(&GameObjectFactory::CreateParallelMissileQuad)},
        {4, static_cast<CreationFunc>(&GameObjectFactory::CreateFollowingMissileQuad)},
        {5, static_cast<CreationFunc>(&GameObjectFactory::createBat)},
		{6,static_cast<CreationFunc>(&GameObjectFactory::createChicken)},
	};

    static const std::unordered_map<int, CreationFunc> seaEnemyMap = {
        {0, static_cast<CreationFunc>(&GameObjectFactory::CreateParallelMissilePair)},
        {1, static_cast<CreationFunc>(&GameObjectFactory::CreateFollowingMissilePair)},
        {2,static_cast<CreationFunc>(&GameObjectFactory::createCrab)},
        {3,static_cast<CreationFunc>(&GameObjectFactory::createShark)},
        {4,static_cast<CreationFunc>(&GameObjectFactory::createPiranha)}
    };

	const auto& map = (m_context == GameContext::Land) ? landEnemyMap : seaEnemyMap;
	if (map.empty()) return {};

    int range;
    static int LastRandom = 0;
	static enum GameContext LastContext = GameContext::Land;

    if (m_context == GameContext::Land)
        range = std::max(7, 14 - static_cast<int>(deltaTime / 300.0f)); // Ensures the max range is at least 7
    else
        range = std::max(5, 14 - static_cast<int>(deltaTime / 300.0f)); // More items in sea state

    int randomNumber = std::rand() % range;

    bool shouldPreventShark = (LastContext == m_context) && (m_context == GameContext::Sea) &&
        (LastRandom == randomNumber) && (LastRandom == SHARK_RANDOM_NUMBER);

    if (randomNumber == LastRandom || shouldPreventShark)
        randomNumber = (randomNumber + 1) % range;
   
    LastRandom = randomNumber;
	LastContext = m_context;

	auto it = map.find(randomNumber);
	if (it != map.end())
		return it->second(playerPos, scrollOffset);
	return {};
}

// Creates a new wall lamp decorative object at a fixed position relative to the scroll offset.
std::vector<std::unique_ptr<StaticObject>> GameObjectFactory::createNewLamps(const sf::Vector2f& scrollOffset,
																					const float deltaTime)
{
    (void)deltaTime;
    std::vector<std::unique_ptr<StaticObject>> newDecor;

    newDecor.push_back(std::move(createWallLamp(scrollOffset)));
    
    return newDecor;
}

// Creates new decorative moving objects(fish/ scientist) based on context and scroll offset.
std::vector<std::unique_ptr<DecorativeMovingObject>> GameObjectFactory::createNewDecoratives(const sf::Vector2f& scrollOffset,
																							const float deltaTime)
{
    (void)deltaTime;
	std::function<sf::Vector2f(const sf::Vector2f&)> getPosFunc;
	GameObjectParams params;
    int range = 5;

	if (m_context == GameContext::Land)
	{
        params = DecorativeMovingObject::getScientistDefaultParams({ 0.f, 0.f });
        getPosFunc = GameObjectFactory::floorPos;
        range = std::rand() % 5;
	}
	else
	{
        std::string objName = getFishName();

        if (objName == "ScientistSwim")
        {
            params = DecorativeMovingObject::getScientistSeaDefaultParams({0.f, 0.f});
            getPosFunc = GameObjectFactory::wavesPos;
            range = std::rand() % 5;
        }
        else
        {
            params = DecorativeMovingObject::getFishDefaultParams({ 0.f, 0.f });
            params._textureName = objName;
		    getPosFunc = GameObjectFactory::getUnderWaterPos;
        }
	}
    
	return createDecoratives(scrollOffset, params, getPosFunc, range);
}

// Randomly creates a new set of pickable objects (coins, power-ups) based on context and scroll offset.
std::vector<std::unique_ptr<Pickables>> GameObjectFactory::createNewPickables(const sf::Vector2f& scrollOffset,
                                                                              const float deltaTime)
{
    (void)deltaTime;
    using CreationFunc = std::vector<std::unique_ptr<Pickables>>(*)(const sf::Vector2f& scrollOffset);

    static std::unordered_map<int, CreationFunc> functionCollection =
    {
        {0,static_cast<CreationFunc>(&GameObjectFactory::createCoinCircle) },
        {1,static_cast<CreationFunc>(&GameObjectFactory::createCoinHeart) },
        {2,static_cast<CreationFunc>(&GameObjectFactory::createCoinLine) },
        {3,static_cast<CreationFunc>(&GameObjectFactory::createPowerUpBox) }
    };

    static int lastRandomNumber = 0; 

	int modulo = (m_context == GameContext::Sea) ? 3 : 4; // In sea state no powerUpBox
	int randomNumber = std::rand() % modulo;

    if ((modulo == 4) && (randomNumber == 3) && (lastRandomNumber == 3)) // only in land state - normalize powerUpBox amount
        randomNumber = (randomNumber + 1) % modulo;
    lastRandomNumber = randomNumber;

	if (functionCollection.empty()) return {};
    auto it = functionCollection.find(randomNumber);
    if (it != functionCollection.end())
	    return it->second(scrollOffset);
	return {};
}

// Creates a vertical laser obstacle with top and bottom heads and a beam.
std::unique_ptr<LaserObstacle> GameObjectFactory::createVerticalLazer(const struct LazerConfig& Laserparams)
{
    sf::Vector2f positionTopHead(Laserparams._xStartPos, Laserparams._yStartPos);
    sf::Vector2f positionBottomHead(Laserparams._xStartPos, Laserparams._yStartPos + Laserparams._laserLength);

    std::unique_ptr<LaserComponent> topHead = createLaserHead(positionTopHead, 0.f, 180.f, true);
    std::unique_ptr<LaserComponent> bottomHead = createLaserHead(positionBottomHead, 0.f, 0.f, false);
    std::unique_ptr<LaserComponent> beam = createLaserBeam(positionTopHead, positionBottomHead, false, 0.f);

    return std::make_unique<LaserObstacle>(
        std::move(topHead),
        std::move(bottomHead),
        std::move(beam));
}

// Creates a horizontal laser obstacle with left and right heads and a beam.
std::unique_ptr<LaserObstacle> GameObjectFactory::createHorizontalLazer(const struct LazerConfig& Laserparams)
{
    sf::Vector2f positionLeftHead(Laserparams._xStartPos, Laserparams._yStartPos);
    sf::Vector2f positionRightHead(Laserparams._xStartPos + Laserparams._laserLength, Laserparams._yStartPos);

    auto topLeftHead = createLaserHead(positionLeftHead, 0.f, 90.f, true);
    auto bottomRightHead = createLaserHead(positionRightHead, 0.f, 270.f, true);
    auto beam = createLaserBeam(positionLeftHead, positionRightHead, true, 90.f);

    return std::make_unique<LaserObstacle>(
        std::move(topLeftHead),
        std::move(bottomRightHead),
        std::move(beam));
}

// Creates a diagonal (left) laser obstacle using calculated positions and angles.
std::unique_ptr<LaserObstacle> GameObjectFactory::createDiagonalLazerLeft(const struct LazerConfig& Laserparams)
{
    std::vector<std::unique_ptr<Obstacles>> newObstacleVec;

    sf::Vector2f positionTopRight(Laserparams._boxTopLeftX + Laserparams._laserLength, Laserparams._boxTopLeftY);
    sf::Vector2f positionBottomLeft(Laserparams._boxTopLeftX, Laserparams._boxTopLeftY + Laserparams._laserLength);

    float angle = GeometryPhysicsUtilities::getAngle(positionTopRight, positionBottomLeft);

    auto topRightHead = createLaserHead(positionTopRight, angle, 90.f, true);
    auto bottomLeftHead = createLaserHead(positionBottomLeft, angle, -90.f, true);
    auto beam = createLaserBeam(positionTopRight, positionBottomLeft, true, 45.f);

    return std::make_unique<LaserObstacle>(
        std::move(topRightHead),
        std::move(bottomLeftHead),
        std::move(beam));
}

// Creates a diagonal (right) laser obstacle using calculated positions and angles.
std::unique_ptr<LaserObstacle> GameObjectFactory::createDiagonalLazerRight(const struct LazerConfig& Laserparams)
{
    std::vector<std::unique_ptr<Obstacles>> newObstacleVec;

    sf::Vector2f positionTopLeft(Laserparams._boxTopLeftX, Laserparams._boxTopLeftY);
    sf::Vector2f positionBottomRight(Laserparams._boxTopLeftX + Laserparams._laserLength,
        Laserparams._boxTopLeftY + Laserparams._laserLength);

    float angle = GeometryPhysicsUtilities::getAngle(positionTopLeft, positionBottomRight);

    auto topLeftHead = createLaserHead(positionTopLeft, angle, 90.f, true);
    auto bottomRightHead = createLaserHead(positionBottomRight, angle, -90.f, true);
    auto beam = createLaserBeam(positionTopLeft, positionBottomRight, true, -45.f);

    return std::make_unique<LaserObstacle>(
        std::move(topLeftHead),
        std::move(bottomRightHead),
        std::move(beam));
}

// Creates a missile pattern(single, pair, quad, etc.) based on the given pattern type.
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::createMissilePattern(const sf::Vector2f& playerPos, 
    const sf::Vector2f& scrollOffset, MissilePattern pattern)
{
    std::vector<std::unique_ptr<Enemy>> m_newEnemies;

    float ceilingY = GraphicUtilities::getCeilingY();
    float floorY = GraphicUtilities::getFloorY();

    switch (pattern)
    {
        case MissilePattern::Single:
        {
            m_newEnemies.push_back(createMissile(playerPos, scrollOffset, {0.f,0.f}));
            break;
        }
        case MissilePattern::ParallelPair:
        {
            m_newEnemies.push_back(createMissile({ 0.f,  ceilingY }, scrollOffset, { 0.f, 0.f })); // topMissile
            m_newEnemies.push_back(createMissile({ 0.f,  floorY }, scrollOffset, { 0.f, 0.f }));   // bottomMissile

            break;
        }
        case MissilePattern::FollowingPair:
        {
            m_newEnemies.push_back(createMissile(playerPos, scrollOffset, { 0.f, 0.f }));       // leadingMissile
            m_newEnemies.push_back(createMissile(playerPos, scrollOffset, { 0.08f, -0.03f }));  // followingMissile

            break;
        }
        case MissilePattern::ParallelQuad:
        {
            m_newEnemies.push_back(createMissile({ 0.f,  ceilingY }, scrollOffset, { 0.f, 0.f }));   // topMissile1
            m_newEnemies.push_back(createMissile({ 0.f,  ceilingY }, scrollOffset, { 0.f, 0.07f })); // topMissile2
            m_newEnemies.push_back(createMissile({ 0.f,  floorY }, scrollOffset, { 0.f, -0.07f }));  // bottomMissile1
            m_newEnemies.push_back(createMissile({ 0.f,  floorY }, scrollOffset, { 0.f, 0.f }));     // bottomMissile2

            break;
        }
        case MissilePattern::FollowingQuad:
        {
            m_newEnemies.push_back(createMissile(playerPos, scrollOffset, { 0.f, 0.f }));       // leadingMissile
            m_newEnemies.push_back(createMissile(playerPos, scrollOffset, { 0.08f, -0.03f }));  // followingMissile1
            m_newEnemies.push_back(createMissile(playerPos, scrollOffset, { 0.16f, 0.03f }));   // followingMissile2
            m_newEnemies.push_back(createMissile(playerPos, scrollOffset, { 0.22f, -0.03f }));  // followingMissile3

            break;
        }
    }

    return m_newEnemies;
}

// Creates a single missile enemy at a calculated position.
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::createSingleMissile(const sf::Vector2f& playerPos,
                                                                           const sf::Vector2f& scrollOffset)
{
    MissilePattern pattern = MissilePattern::Single;
    return createMissilePattern(playerPos, scrollOffset,pattern);
}

// Creates a pair of parallel missiles (top and bottom).
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::CreateParallelMissilePair(const sf::Vector2f& playerPos,
                                                                                 const sf::Vector2f& scrollOffset)
{
    MissilePattern pattern = MissilePattern::ParallelPair;
    return createMissilePattern(playerPos, scrollOffset, pattern);
}

// Creates a pair of following missiles (one follows the other).
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::CreateFollowingMissilePair(const sf::Vector2f& playerPos,
                                                                                  const sf::Vector2f& scrollOffset)
{
    MissilePattern pattern = MissilePattern::FollowingPair;
    return createMissilePattern(playerPos, scrollOffset, pattern);
}

// Creates four parallel missiles (two top, two bottom).
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::CreateParallelMissileQuad(const sf::Vector2f& playerPos,
                                                                                 const sf::Vector2f& scrollOffset)
{
    MissilePattern pattern = MissilePattern::ParallelQuad;
    return createMissilePattern(playerPos, scrollOffset, pattern);
}

// Creates four following missiles in a quad pattern.
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::CreateFollowingMissileQuad(const sf::Vector2f& playerPos,
                                                                                  const sf::Vector2f& scrollOffset)
{
    (void)playerPos;
    MissilePattern pattern = MissilePattern::FollowingQuad;
    return createMissilePattern(playerPos, scrollOffset, pattern);
}

// Creates a chicken enemy at the right edge of the screen, at ceiling height.
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::createChicken(const sf::Vector2f& playerPos, const sf::Vector2f& scrollOffset)
{
    (void)playerPos;
    float posX = scrollOffset.x +GraphicUtilities::getWindowSize().x;
    float posY = GraphicUtilities::getCeilingY();

    return createEnemy(Chicken::getDefaultParams({ posX, posY }));
}

// Creates a missile enemy at a position relative to the player and scroll offset.
std::unique_ptr<Enemy> GameObjectFactory::createMissile(const sf::Vector2f& playerPos,
                                                       const sf::Vector2f& scrollOffset, 
                                                       const sf::Vector2f& addition)
{
    float posX = scrollOffset.x + (1 + addition.x) * GraphicUtilities::getWindowSize().x;
    float posY = playerPos.y + addition.y * GraphicUtilities::getWindowSize().y;
    GameObjectParams missileParams = Missile::getDefaultParams({ posX, posY });

    std::unique_ptr<GameObject> missile = GameObjectFactory::create("Missile", missileParams);
    std::unique_ptr<Enemy> newMissile(static_cast<Enemy*>(missile.release()));

    return newMissile;
}

// Creates a new enemy from the given parameters and returns it in a vector.
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::createEnemy(const GameObjectParams& params)
{
    std::vector<std::unique_ptr<Enemy>> newEnemies;

    std::unique_ptr<GameObject> enemy = GameObjectFactory::create(params._textureName, params);
    std::unique_ptr<Enemy> newEnemy(static_cast<Enemy*>(enemy.release()));
    newEnemies.push_back(std::move(newEnemy));

    return newEnemies;
}

// Creates a crab enemy at the right edge of the screen, at floor height.
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::createCrab(const sf::Vector2f& playerPos, 
                                                                        const sf::Vector2f& scrollOffset)
{
    (void)playerPos;
    float posX = scrollOffset.x +  GraphicUtilities::getWindowSize().x;
    float posY = GraphicUtilities::getFloorY();

    return createEnemy(Crab::getDefaultParams({ posX, posY }));
}


// Creates a shark enemy at the right edge of the screen, at floor height.
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::createShark(const sf::Vector2f& playerPos, const sf::Vector2f& scrollOffset)
{
    (void)playerPos;
    float posX = scrollOffset.x + GraphicUtilities::getWindowSize().x;
    float posY = GraphicUtilities::getFloorY();

    return createEnemy(Shark::getDefaultParams({ posX, posY }));
}

// Creates a set of pearls in a heart pattern around a shell position.
std::vector<std::unique_ptr<Pickables>> GameObjectFactory::createPearls(const sf::Vector2f& shellPos,
																	   const sf::Vector2f& scrollOffset)
{
    (void)scrollOffset;
	std::vector<std::unique_ptr<Pickables>> pearls;

	static std::vector<sf::Vector2f> pearlHeartTemplateRelativePositions;

	if (pearlHeartTemplateRelativePositions.empty())
	{
		initializePearlHeartTemplate(pearlHeartTemplateRelativePositions, shellPos);
	}

	for (const auto& relativePos : pearlHeartTemplateRelativePositions)
	{
		sf::Vector2f absolutePearlPos = shellPos + relativePos;

		GameObjectParams pearlParams = Pearl::getDefaultParams(absolutePearlPos);
		auto pearl = GameObjectFactory::create(pearlParams._textureName, pearlParams);

		if (pearl)
			pearls.push_back(std::unique_ptr<Pickables>(static_cast<Pickables*>(pearl.release())));
	}

	return pearls;
}

// Creates a set of decorative moving objects using a position function and range.
std::vector<std::unique_ptr<DecorativeMovingObject>> GameObjectFactory::createDecoratives(
	const sf::Vector2f& scrollOffset,
	GameObjectParams& params,
	std::function<sf::Vector2f(const sf::Vector2f&)> getPosFunc,
    int range)
{
	std::vector<std::unique_ptr<DecorativeMovingObject>> newDecor;

	if (1 <= range) createDecorative(newDecor, scrollOffset, 0.f, params, getPosFunc);
    if (2 <= range) createDecorative(newDecor, scrollOffset, 0.1f, params, getPosFunc);
    if (3 <= range) createDecorative(newDecor, scrollOffset, -0.3f, params, getPosFunc);
    if (4 <= range) createDecorative(newDecor, scrollOffset, 0.5f, params, getPosFunc);
    if (5 <= range) createDecorative(newDecor, scrollOffset, -0.6f, params, getPosFunc);

	return newDecor;
}

// Helper to create a single decorative object and add it to the vector.
void GameObjectFactory::createDecorative(std::vector<std::unique_ptr<DecorativeMovingObject>>& newDecor,
	const sf::Vector2f& scrollOffset, const float xOffSet, GameObjectParams& params,
	std::function<sf::Vector2f(const sf::Vector2f&)> getPosFunc)
{
	float windowWidth = GraphicUtilities::getWindowSize().x;

	float randPosX = (std::rand() / (float)RAND_MAX) * (windowWidth * 0.17f);

	float posX = scrollOffset.x + (1 + xOffSet) * windowWidth + randPosX;

	sf::Vector2f pos = getPosFunc(scrollOffset);
	pos.x = posX;

	params._position = pos;

    auto decor = GameObjectFactory::create("DecorativeMovingObject", params);

	if (decor)
		newDecor.push_back(std::unique_ptr<DecorativeMovingObject>(static_cast<DecorativeMovingObject*>(decor.release())));
}

// Returns a random underwater position for spawning sea creatures.
sf::Vector2f GameObjectFactory::getUnderWaterPos(const sf::Vector2f& scrollOffset)
{
	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

    const float minY = 0.7f * (GraphicUtilities::getFloorY() - windowSize.x * 0.02f) + windowSize.x * 0.1f;
	const float maxY = GraphicUtilities::getFloorY();

	float posX = scrollOffset.x + 0.05f * windowSize.x;
	float posY = minY + static_cast<float>(std::rand()) / RAND_MAX * (maxY - minY);

	return sf::Vector2f(posX, posY);
}

sf::Vector2f GameObjectFactory::floorPos(const sf::Vector2f& scrollOffset)
{
	(void)scrollOffset;
	float y = GraphicUtilities::getFloorY();
	return {y, y};
}

sf::Vector2f GameObjectFactory::wavesPos(const sf::Vector2f& scrollOffset)
{
    (void)scrollOffset;
    float y = GraphicUtilities::getWavesY();
    return { y, y };
}

// Initializes the template for placing pearls in a heart pattern around a shell.
void GameObjectFactory::initializePearlHeartTemplate(std::vector<sf::Vector2f>& outTemplateVector,
													const sf::Vector2f& shellPosForTemplate)
{
	sf::Vector2f windowScale = Pearl::getDefaultParams({0.f, 0.f})._windowScale;
	sf::Vector2f pearlItemSize = Pearl::getSize(windowScale);

	float templateReferenceX = 0.0f;
	float templateReferenceY = shellPosForTemplate.y;

	sf::Vector2f unitHeartBounds = GeometryPhysicsUtilities::getHeartBoundingBox(1.0f);

	if (unitHeartBounds.x == 0.0f) unitHeartBounds.x = 1.0f;
	if (unitHeartBounds.y == 0.0f) unitHeartBounds.y = 1.0f;

	float desiredStandardHeartPixelWidth = pearlItemSize.x * 5.0f;
	float desiredLargeHeartPixelWidth = pearlItemSize.x * 8.0f;

	float standardHeartShapeSize = desiredStandardHeartPixelWidth / unitHeartBounds.x;
	float largeHeartShapeSize = desiredLargeHeartPixelWidth / unitHeartBounds.x;

	standardHeartShapeSize = std::max(0.1f, standardHeartShapeSize);
	largeHeartShapeSize = std::max(0.1f, largeHeartShapeSize);

	float horizontalSpacing = pearlItemSize.x * 3.0f;

	std::vector<sf::Vector2f> heartCenters = GeometryPhysicsUtilities::generateParallelHeartPositions(
		templateReferenceY,
		standardHeartShapeSize,
		largeHeartShapeSize,
		horizontalSpacing,
		templateReferenceX
	);

	sf::Vector2f overallPatternCenter = { templateReferenceX, templateReferenceY };

	outTemplateVector.clear();

	for (const auto& heartCenter : heartCenters)
	{
		float currentHeartSize;
		if (heartCenters.size() >= 2 && heartCenter == heartCenters[1]) {
			currentHeartSize = largeHeartShapeSize;
		}
		else {
			currentHeartSize = standardHeartShapeSize;
		}

		float perimeter = GeometryPhysicsUtilities::heartPerimeter(currentHeartSize);

		int numPearlsPerHeart = static_cast<int>(perimeter / (pearlItemSize.x + 0.0001f));
		if (numPearlsPerHeart < 3) numPearlsPerHeart = 3;

		std::vector<sf::Vector2f> pearlPositionsOnCurrentHeartAbsolute = GeometryPhysicsUtilities::pointsOnHeart(
			heartCenter,
			currentHeartSize,
			numPearlsPerHeart
		);

		outTemplateVector.insert(outTemplateVector.end(),
			std::make_move_iterator(pearlPositionsOnCurrentHeartAbsolute.begin()),
			std::make_move_iterator(pearlPositionsOnCurrentHeartAbsolute.end()));
	}

	for (auto& pos : outTemplateVector)
		pos -= overallPatternCenter;
}

// Creates a bat enemy and its associated wave effect at a calculated position.
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::createBat(const sf::Vector2f& playerPos,
    const sf::Vector2f& scrollOffset)
{
    float posX = (float)(scrollOffset.x + 0.05 * GraphicUtilities::getWindowSize().x);
    float posY = playerPos.y + scrollOffset.y * GraphicUtilities::getWindowSize().y;

    GameObjectParams batParams = ProjectileEnemy::getBatDefaultParams({ posX, posY });
    GameObjectParams wavesParams = Projectile::getWavesDefaultParams({ posX, posY });

    return createProjectileEnemy(batParams, wavesParams,
        "BatSound", "DinoWingsSound", 100, 55);
}

// Creates a piranha enemy and its associated light effect at a random underwater position.
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::createPiranha(const sf::Vector2f& playerPos,
    const sf::Vector2f& scrollOffset)
{
    (void)playerPos;
    GameObjectParams piranhaParams = ProjectileEnemy::getPiranhaDefaultParams(getUnderWaterPos(scrollOffset));
    GameObjectParams lightBallParams = Projectile::getLightBallDefaultParams(piranhaParams._position);

    return createProjectileEnemy(piranhaParams, lightBallParams,
        "PiranhaSound", "SwimSound", 100, 80, 4, 6);
}

// Creates a projectile enemy (bat, piranha, etc.) with associated projectile and sound parameters.
std::vector<std::unique_ptr<Enemy>> GameObjectFactory::createProjectileEnemy(const GameObjectParams& enemyParams, 
    const GameObjectParams& projectileParams, const std::string& projectileSoundName, const std::string& enemySoundName,
    const float projectileVol, const float enemyVol, const int startFrame, const int renderFrame)
{
    std::vector<std::unique_ptr<Enemy>> newEnemies;

    auto enemy = std::make_unique<ProjectileEnemy>(enemyParams, projectileParams,
        projectileSoundName, enemySoundName, projectileVol, enemyVol, startFrame, renderFrame);
    newEnemies.push_back(std::move(enemy));

    return newEnemies;
}

// Returns a random position within the playable area, avoiding screen edges.
sf::Vector2f GameObjectFactory::getRandomPos(const sf::Vector2f& scrollOffset)
{
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
    float ceilingY = GraphicUtilities::getCeilingY();
    float floorY = GraphicUtilities::getFloorY();

    float bufferX = windowSize.x * 0.05f;
    float bufferY = windowSize.y * 0.2f;

    float playableHeight = floorY - ceilingY;
    float spawnableXRange = windowSize.x - (2 * bufferX);

    float x = bufferX + static_cast<float>(std::rand()) / RAND_MAX * spawnableXRange + scrollOffset.x;
    float y = ceilingY + bufferY + static_cast<float>(std::rand()) / RAND_MAX * (playableHeight - 2 * bufferY) + scrollOffset.y;

    return sf::Vector2f(x, y);
}

// Creates a special gift pickable (according to the state of the player) at a random position.
std::unique_ptr<Pickables> GameObjectFactory::createSpecialGift(const sf::Vector2f& scrollOffset,
                                                                const GameObjectParams& params)
{
    sf::Vector2f pos = getRandomPos(scrollOffset);
    auto giftParams = params;
    giftParams._position = pos;
    auto specialGift = GameObjectFactory::create(giftParams._textureName, giftParams);

    return std::unique_ptr<Pickables>(static_cast<Pickables*>(specialGift.release()));
}

// Creates a wall lamp static object at a fixed position.
std::unique_ptr<StaticObject> GameObjectFactory::createWallLamp(const sf::Vector2f& scrollOffset)
{
    std::unique_ptr<WallLamp> wallLamp;
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

    float posX = windowSize.x * 0.378f + scrollOffset.x;
    float posY = windowSize.y * 0.125f + scrollOffset.y;
    
    GameObjectParams params = WallLamp::getDefaultParams({ posX, posY });

    std::unique_ptr<GameObject> lamp = GameObjectFactory::create("WallLamp", params);

    std::unique_ptr<StaticObject> newLamp(static_cast<StaticObject*>(lamp.release()));

    return newLamp;
}

// Creates a power-up box pickable at a random position.
std::vector<std::unique_ptr<Pickables>> GameObjectFactory::createPowerUpBox(const sf::Vector2f& scrollOffset)
{
    std::vector<std::unique_ptr<Pickables>> pickables;

    sf::Vector2f pos = getRandomPos(scrollOffset);

    GameObjectParams params = PowerUpBox::getDefaultParams(pos);

    auto powerUpBox = GameObjectFactory::create("PowerUpBox", params);

    if (powerUpBox)
        pickables.push_back(std::unique_ptr<Pickables>(static_cast<Pickables*>(powerUpBox.release())));

    return pickables;
}

// Creates a circle of coins at calculated positions.
std::vector<std::unique_ptr<Pickables>> GameObjectFactory::createCoinCircle(const sf::Vector2f& scrollOffset)
{
    sf::Vector2f windowScale = { 0.02f, 0.04f };
	sf::Vector2f coinSize = Coin::getSize(windowScale);

	std::vector<sf::Vector2f> positions = GeometryPhysicsUtilities::createCircleShapePositions(
		scrollOffset,coinSize);

	std::vector<std::unique_ptr<Pickables>> pickables;
    for (const auto& pos : positions)
    {
		GameObjectParams params = Coin::getDefaultParams(pos);
		auto coin = GameObjectFactory::create(params._textureName, params);
        if (coin) pickables.push_back(std::unique_ptr<Pickables>(static_cast<Pickables*>(coin.release())));
    }
	return pickables;
}

// Creates a heart-shaped pattern of coins at calculated positions.
std::vector<std::unique_ptr<Pickables>> GameObjectFactory::createCoinHeart(const sf::Vector2f& scrollOffset)
{
    sf::Vector2f windowScale = { 0.02f, 0.04f };
	sf::Vector2f coinSize = Coin::getSize(windowScale);

	std::vector<sf::Vector2f> positions = GeometryPhysicsUtilities::createHeartShapePositions(
		scrollOffset,coinSize);

	std::vector<std::unique_ptr<Pickables>> pickables;
    for (const auto& pos : positions)
    {
		GameObjectParams params = Coin::getDefaultParams(pos);
		auto coin = GameObjectFactory::create(params._textureName, params);
        if (coin)
			pickables.push_back(std::unique_ptr<Pickables>(static_cast<Pickables*>(coin.release())));
        }
	return pickables;
}

// Creates a line of coins at calculated positions.
std::vector<std::unique_ptr<Pickables>> GameObjectFactory::createCoinLine(const sf::Vector2f& scrollOffset)
{
    sf::Vector2f windowScale = { 0.02f, 0.04f };
	sf::Vector2f coinSize = Coin::getSize(windowScale);

	std::vector<sf::Vector2f> positions = GeometryPhysicsUtilities::createLineShapePositions(
		scrollOffset, coinSize);

	std::vector<std::unique_ptr<Pickables>> pickables;
    for (const auto& pos : positions)
    {
		GameObjectParams params = Coin::getDefaultParams(pos);
		auto coin = GameObjectFactory::create(params._textureName, params);
        if (coin) pickables.push_back(std::unique_ptr<Pickables>(static_cast<Pickables*>(coin.release())));
	}
	return pickables;
}

// Creates a laser head component at a given position and angle, with optional rotation.
std::unique_ptr<LaserComponent> GameObjectFactory::createLaserHead(const sf::Vector2f& headPos, const float angle, const float additionToAngle, const bool needToRotate)
{
    GameObjectParams headParams = LaserComponent::getLaserHeadDefaultParams(headPos);

    std::unique_ptr<GameObject> laserHead = GameObjectFactory::create("LaserComponent", headParams);

    if (laserHead && needToRotate) laserHead->rotateSprite((float)angle + additionToAngle);

    std::unique_ptr<LaserComponent> newHead(static_cast<LaserComponent*>(laserHead.release()));

    return newHead;
}

// Creates a laser beam component between two head positions, with optional rotation and scaling.
std::unique_ptr<LaserComponent> GameObjectFactory::createLaserBeam(const sf::Vector2f& topHeadPos, const sf::Vector2f& bottomHeadPos,
                                                                   const bool needToRotate, const float angle)
{
    sf::Vector2f beamPos = (topHeadPos + bottomHeadPos) / 2.f;
    float distance = GeometryPhysicsUtilities::getDistance(topHeadPos, bottomHeadPos);

    GameObjectParams beamParams = LaserComponent::getLaserBeamDefaultParams(beamPos);

    std::unique_ptr<GameObject> beam = GameObjectFactory::create("LaserComponent", beamParams);

    float originalHeight = beam->getLocalBounds().height;
    float scaleY = (originalHeight > 0) ? distance / originalHeight : 0;
    beam->setScale(sf::Vector2f(1, scaleY));

    if (needToRotate) beam->rotateSprite((float)angle);

    std::unique_ptr<LaserComponent> newBeam(static_cast<LaserComponent*>(beam.release()));

    return newBeam;
}

// Returns a random fish name for decorative sea objects.
std::string GameObjectFactory::getFishName()
{
    static const std::vector<std::string> fishNames = {
        "Fish1", "Fish2", "JellyFish1", "JellyFish2", "Squid1", "Squid2",
        "ScientistSwim", "ScientistSwim"};
    int idx = std::rand() % fishNames.size();
    return fishNames[idx];
}
