#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <limits>
#include <utility>
#include <functional>
#include "GraphicUtilities.h"

///*
// * GeometryPhysicsUtilities Class
// * ------------------------------
// * A static utility class providing geometric and physics-based layout tools
// * for placing and animating items in the game world.
//
// * Functionality:
// * --------------
// * - Generate item positions arranged in various shapes:
// *     - Circle
// *     - Heart
// *     - Line
// *     - Swirl / Parallel hearts
// * - Perform physical calculations, such as:
// *     - Distance and angle between points
// *     - Movement using gravity and velocity (vertical transitions)
// * - Compute shape-specific properties:
// *     - Perimeter and bounding box for heart shapes
// *     - Optimal center positions based on screen and item sizes
//
// * Purpose:
// * --------
// * To provide reusable and scalable logic for object placement and
// * animation across different game states and screen sizes.

class GeometryPhysicsUtilities
{
public:

    // Calculates the Euclidean distance between two SFML vectors.
    static float getDistance(const sf::Vector2f& pointA, const sf::Vector2f& pointB);

    // Calculates the angle (in degrees) between two SFML vectors.
    static float getAngle(const sf::Vector2f& pointA, const sf::Vector2f& pointB);

    // Calculates the number of objects that can fit on a circle's circumference.
    static int calcNumObjectsOnCircle(const float radius, const float objectWidth, const float gap);

    // Generates a vector of points arranged on a circle.
    static std::vector<sf::Vector2f> pointsOnCircle(const sf::Vector2f& center, 
        const float radius, int const numPoints);

    // Calculates the approximate perimeter of a heart shape.
    static float heartPerimeter(const float size, const int samples = 200);

    // Generates a vector of points arranged on a heart shape.
    static std::vector<sf::Vector2f> pointsOnHeart(const sf::Vector2f& center, 
        const float size, const int numPoints);

    // Calculates the bounding box (width and height) of a heart shape.
    static sf::Vector2f getHeartBoundingBox(const float size, const int samples = 200);

    // Generates a vector of points arranged along a line segment.
    static std::vector<sf::Vector2f> pointsOnLine(const sf::Vector2f& start, 
        const sf::Vector2f& end, const int numPoints);

    // Applies a vertical transition effect to a position based on physics parameters.
    static sf::Vector2f applyVerticalTransition(const sf::View& view,
        const sf::Vector2f currentPos, float& velocityY, const float acceleration,
        const float deltaTime, const float targetY, bool& stillTransitioning);


    // Generates positions for items arranged in a circle.
    // Takes scrollOffset and itemSize for calculations.
    static std::vector<sf::Vector2f> createCircleShapePositions(
        const sf::Vector2f& scrollOffset,
        const sf::Vector2f& itemSize
    );

    // Generates positions for items arranged in a heart shape.
    // Takes scrollOffset and itemSize for calculations.
    static std::vector<sf::Vector2f> createHeartShapePositions(
        const sf::Vector2f& scrollOffset,
        const sf::Vector2f& itemSize
    );

    // Generates positions for items arranged in a line.
    // Takes scrollOffset and itemSize for calculations.
    static std::vector<sf::Vector2f> createLineShapePositions(
        const sf::Vector2f& scrollOffset,
        const sf::Vector2f& itemSize
    );

    static std::vector<sf::Vector2f> generateSwirlPositions(
        const int numItems,
        const sf::Vector2f& windowSize,
        const float clusterWidth,
        const float clusterHeight,
        const float baseXOffset,
        const float baseYOffset
    );

    static std::vector<sf::Vector2f> generateParallelHeartPositions(
        const float centerY,
        const float standardHeartSize,
        const float largeHeartSize,
        const float horizontalSpacing,
        const float objectSpawnX
    );

private:

    // Calculates the delta vector between two SFML vectors.
    static sf::Vector2f getDelta(const sf::Vector2f& pointA, const sf::Vector2f& pointB);

    // Calculates a random radius for a circle shape based on playable height.
    static float calculateRandomCircleRadius(const float playableHeight);

    // Calculates the center position for a circle shape.
    static sf::Vector2f calculateCircleCenter(const sf::Vector2f& scrollOffset, const float playableHeight,
        const float radius, const float itemWidth);

    // Calculates the optimal scale size for a heart shape based on item size and playable height.
    static float calculateHeartShapeOptimalSize(const sf::Vector2f& itemSize, const float playableHeight);

    // Calculates the center position for a heart shape.
    static sf::Vector2f calculateHeartCenter(const sf::Vector2f& scrollOffset, 
        const sf::Vector2f& itemSize, const float size);

    // Calculates the number of items for a line shape.
    static int calculateLineNumItems();

    // Calculates the start and end points for a line shape, adjusting item count if necessary.
    static std::pair<sf::Vector2f, sf::Vector2f> calculateLineStartEndPoints(const sf::Vector2f& scrollOffset,
        int& numItems, const float itemWidth, const float gap);

    static float clampHeartCenterY(const float desiredCenterY, 
        const float heartHeight, const float ceilingY, const float floorY);

};
