#include "GeometryPhysicsUtilities.h"
#include "Pearl.h"

// Calculates the Euclidean distance between two SFML vectors.
float GeometryPhysicsUtilities::getDistance(const sf::Vector2f& pointA, const sf::Vector2f& pointB)
{
    sf::Vector2f delta = getDelta(pointA, pointB);

    return std::sqrt(delta.x * delta.x + delta.y * delta.y);
}

// Calculates the angle (in degrees) between two SFML vectors.
float GeometryPhysicsUtilities::getAngle(const sf::Vector2f& pointA, const sf::Vector2f& pointB)
{
    sf::Vector2f delta = getDelta(pointA, pointB);

    float angle = std::atan2(delta.y, delta.x) * 180.f / 3.14159265f;

    return angle;
}

// Calculates the number of objects that can fit on a circle's circumference.
int GeometryPhysicsUtilities::calcNumObjectsOnCircle(const float radius, const float objectWidth, const float gap)
{
    float circumference = 2 * 3.14159265f * radius;
    int num = static_cast<int>(circumference / (objectWidth + gap));
    return std::max(num, 3);
}

// Generates a vector of points arranged on a circle.
std::vector<sf::Vector2f> GeometryPhysicsUtilities::pointsOnCircle(const sf::Vector2f& center, 
    const float radius, const int numPoints)
{
    std::vector<sf::Vector2f> points;
    for (int i = 0; i < numPoints; ++i)
    {
        float angle = 2 * 3.14159265f * i / numPoints;
        points.emplace_back(center.x + radius * std::cos(angle), center.y + radius * std::sin(angle));
    }
    return points;
}

// Calculates the approximate perimeter of a heart shape.
float GeometryPhysicsUtilities::heartPerimeter(const float size, const int samples)
{
    float perimeter = 0.f;
    sf::Vector2f prev;
    for (int i = 0; i <= samples; ++i)
    {
        float t = 2 * 3.14159265f * i / samples;
        float x = (float)(size * 16 * std::pow(std::sin(t), 3));
        float y = -size * (13 * std::cos(t) - 5 * std::cos(2 * t) - 2 * std::cos(3 * t) - std::cos(4 * t));
        sf::Vector2f curr(x, y);
        if (i > 0)
            perimeter += std::sqrt((curr.x - prev.x) * (curr.x - prev.x) + (curr.y - prev.y) * (curr.y - prev.y));
        prev = curr;
    }
    return perimeter;
}

// Generates a vector of points arranged on a heart shape.
std::vector<sf::Vector2f> GeometryPhysicsUtilities::pointsOnHeart(const sf::Vector2f& center, 
    const float size, const int numPoints)
{
    std::vector<sf::Vector2f> points;
    for (int i = 0; i < numPoints; ++i)
    {
        float t = 2 * 3.14159265f * i / numPoints;
        float x = (float)(size * 16 * std::pow(std::sin(t), 3));
        float y = -size * (13 * std::cos(t) - 5 * std::cos(2 * t) - 2 * std::cos(3 * t) - std::cos(4 * t));
        points.emplace_back(center.x + x, center.y + y);
    }
    return points;
}

// GeometryPhysicsUtilities.cpp
sf::Vector2f GeometryPhysicsUtilities::getHeartBoundingBox(const float size, const int samples)
{
    float minX = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float minY = std::numeric_limits<float>::max();
    float maxY = std::numeric_limits<float>::lowest();

    for (int i = 0; i <= samples; ++i)
    {
        float t = 2 * 3.14159265f * i / samples;
    
        float x_raw = (float)(16 * std::pow(std::sin(t), 3));
        float y_raw = -(13 * std::cos(t) - 5 * std::cos(2 * t) - 2 * std::cos(3 * t) - std::cos(4 * t));

        float x = size * x_raw;
        float y = size * y_raw;

        minX = std::min(minX, x);
        maxX = std::max(maxX, x);
        minY = std::min(minY, y);
        maxY = std::max(maxY, y);
    }

    return { maxX - minX, maxY - minY }; // width, height
}

// Generates a vector of points arranged along a line segment.
std::vector<sf::Vector2f> GeometryPhysicsUtilities::pointsOnLine(const sf::Vector2f& start, 
    const sf::Vector2f& end, const int numPoints)
{
    std::vector<sf::Vector2f> points;
    for (int i = 0; i < numPoints; ++i)
    {
        float t = static_cast<float>(i) / (numPoints - 1);
        points.emplace_back(start.x + t * (end.x - start.x), start.y + t * (end.y - start.y));
    }
    return points;
}

// Applies a vertical transition effect to a position based on physics parameters.
sf::Vector2f GeometryPhysicsUtilities::applyVerticalTransition(const sf::View& view,
    const sf::Vector2f currentPos, float& velocityY, const float acceleration,
    const float deltaTime, const float targetY, bool& stillTransitioning)
{
    velocityY += acceleration * deltaTime;

    float newY = currentPos.y + velocityY * deltaTime;

    bool reached = (acceleration > 0 && newY >= targetY) ||
        (acceleration < 0 && newY <= targetY);

    if (reached)
    {
        newY = targetY;
        stillTransitioning = false;
    }

    float fixedX = view.getCenter().x - view.getSize().x / 2 +
        (GraphicUtilities::getWindowSize().x * playerRelativeX);

    return { fixedX, newY };
}

// Calculates the delta vector between two SFML vectors.
sf::Vector2f GeometryPhysicsUtilities::getDelta(const sf::Vector2f& pointA, const sf::Vector2f& pointB)
{
    float deltaX = pointB.x - pointA.x;
    float deltaY = pointB.y - pointA.y;

    return sf::Vector2f(deltaX, deltaY);
}


// Generic Shape Position Generators (implementations)

// Generates positions for items arranged in a circle.
std::vector<sf::Vector2f> GeometryPhysicsUtilities::createCircleShapePositions(
    const sf::Vector2f& scrollOffset,
    const sf::Vector2f& itemSize)
{
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
    float ceilingY = GraphicUtilities::getCeilingY();
    float floorY = GraphicUtilities::getFloorY();
    float playableHeight = floorY - ceilingY;

    float itemWidth = itemSize.x;
    float gap = itemWidth * 0.5f;

    float radius = calculateRandomCircleRadius(playableHeight);

    int numItems = GeometryPhysicsUtilities::calcNumObjectsOnCircle(radius, itemWidth, gap);

    sf::Vector2f center = calculateCircleCenter(scrollOffset, playableHeight, radius, itemWidth);

    return GeometryPhysicsUtilities::pointsOnCircle(center, radius, numItems);
}

// Generates positions for items arranged in a heart shape.
std::vector<sf::Vector2f> GeometryPhysicsUtilities::createHeartShapePositions(
    const sf::Vector2f& scrollOffset,
    const sf::Vector2f& itemSize)
{
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
    float ceilingY = GraphicUtilities::getCeilingY();
    float floorY = GraphicUtilities::getFloorY();
    float playableHeight = floorY - ceilingY;

    float itemWidth = itemSize.x;
    float gap = 0; // Fixed gap for heart shape

    float size = calculateHeartShapeOptimalSize(itemSize, playableHeight);

    sf::Vector2f center = calculateHeartCenter(scrollOffset, itemSize, size);

    float perimeter = GeometryPhysicsUtilities::heartPerimeter(size);
    int numItems = static_cast<int>(perimeter / (itemWidth + gap));
    if (numItems < 3) numItems = 3;

    return GeometryPhysicsUtilities::pointsOnHeart(center, size, numItems);
}

// Generates positions for items arranged in a line.
std::vector<sf::Vector2f> GeometryPhysicsUtilities::createLineShapePositions(
    const sf::Vector2f& scrollOffset,
    const sf::Vector2f& itemSize)
{
    float itemWidth = itemSize.x;
    float gap = itemWidth * 0.5f;

    int numItems = calculateLineNumItems(); // Number of items for the line is determined here

    std::pair<sf::Vector2f, sf::Vector2f> linePoints = calculateLineStartEndPoints(scrollOffset, numItems, itemWidth, gap);
    sf::Vector2f start = linePoints.first;
    sf::Vector2f end = linePoints.second;

    if (numItems < 3) return {}; // Return empty if insufficient items after adjustment

    return GeometryPhysicsUtilities::pointsOnLine(start, end, numItems);
}

std::vector<sf::Vector2f> GeometryPhysicsUtilities::generateSwirlPositions(const int numItems, 
    const sf::Vector2f& windowSize, const float clusterWidth, const float clusterHeight, 
    const float baseXOffset, const float baseYOffset)
{
    (void)windowSize;
    std::vector<sf::Vector2f> positions;
    positions.reserve(numItems); // Pre-allocate memory for efficiency

    for (int i = 0; i < numItems; ++i)
    {
        float clusterX = baseXOffset + ((std::rand() % 1001) / 1000.f - 0.5f) * clusterWidth;
        float clusterY = baseYOffset + ((std::rand() % 1001) / 1000.f - 0.5f) * clusterHeight;

        positions.emplace_back(clusterX, clusterY);
    }
    return positions;
}

std::vector<sf::Vector2f> GeometryPhysicsUtilities::generateParallelHeartPositions(
    const float centerY,             // The desired Y-coordinate for the center of all three hearts (will be clamped)
    const float standardHeartSize,   // The 'size' parameter for the two outer hearts
    const float largeHeartSize,      // The 'size' parameter for the central, larger heart
    const float horizontalSpacing,   // The horizontal gap between heart bounding boxes
    const float objectSpawnX        // The X-coordinate (e.g., shell's center X) to position hearts relative to.
)
{
    std::vector<sf::Vector2f> positions;
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
    float ceilingY = GraphicUtilities::getCeilingY();
    float floorY = GraphicUtilities::getFloorY();

    // Calculate the maximum height of any heart to determine Y-clamping
    sf::Vector2f largeHeartBounds = GeometryPhysicsUtilities::getHeartBoundingBox(largeHeartSize);
    sf::Vector2f standardHeartBounds = GeometryPhysicsUtilities::getHeartBoundingBox(standardHeartSize);
    float maxHeartHeight = std::max(largeHeartBounds.y, standardHeartBounds.y);

    // Clamp the Y-coordinate of the heart centers to ensure they are within game boundaries
    float clampedCenterY = clampHeartCenterY(centerY, maxHeartHeight, ceilingY, floorY);

    // Define an initial offset from objectSpawnX to the first heart's center.
    float initialOffsetFromShell = standardHeartBounds.x / 2.0f + horizontalSpacing;

    // Calculate the X position of the first (left-most) heart in the group.
    // This will be the standard-sized heart on the far left.
    float currentX = objectSpawnX + initialOffsetFromShell;

    // Position for the first (left) standard heart
    positions.emplace_back(currentX, clampedCenterY);

    // Move X for the central large heart
    currentX += (standardHeartBounds.x / 2.0f) + horizontalSpacing + (largeHeartBounds.x / 2.0f);
    positions.emplace_back(currentX, clampedCenterY); // Middle large heart position

    // Move X for the third (right) standard heart
    currentX += (largeHeartBounds.x / 2.0f) + horizontalSpacing + (standardHeartBounds.x / 2.0f);
    positions.emplace_back(currentX, clampedCenterY); // Right standard heart position

    return positions;
}

// Calculates a random radius for a circle shape based on playable height.
float GeometryPhysicsUtilities::calculateRandomCircleRadius(const float playableHeight)
{
    float minRadius = playableHeight * 0.10f;
    float maxRadius = playableHeight * 0.30f;
    return minRadius + static_cast<float>(std::rand()) / RAND_MAX * (maxRadius - minRadius);
}

// Calculates the center position for a circle shape.
sf::Vector2f GeometryPhysicsUtilities::calculateCircleCenter(const sf::Vector2f& scrollOffset, const float playableHeight,
    const float radius, const float itemWidth)
{
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
    float ceilingY = GraphicUtilities::getCeilingY();

    float marginX = radius + itemWidth / 2.f + 10.f;
    float marginY = radius + itemWidth / 2.f + 10.f;

    float spawnableXRange = windowSize.x - 2 * marginX;
    float centerX = marginX + static_cast<float>(std::rand()) / RAND_MAX * spawnableXRange;

    float spawnableYRange = playableHeight - 2 * marginY;
    float centerY = ceilingY + marginY + static_cast<float>(std::rand()) / RAND_MAX * spawnableYRange;

    return scrollOffset + sf::Vector2f(centerX, centerY);
}

// Calculates the optimal scale size for a heart shape based on item size and playable height.
float GeometryPhysicsUtilities::calculateHeartShapeOptimalSize(const sf::Vector2f& itemSize, const float playableHeight)
{
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

    sf::Vector2f heartUnitSize = GeometryPhysicsUtilities::getHeartBoundingBox(1.0f);
    float maxSizeX = (windowSize.x - itemSize.x - 20.f) / heartUnitSize.x / 2.f;
    float maxSizeY = (playableHeight - itemSize.y - 20.f) / heartUnitSize.y / 2.f;
    float maxSize = std::min(maxSizeX, maxSizeY);
    float minSize = maxSize * 0.5f;
    float size = minSize + static_cast<float>(std::rand()) / RAND_MAX * (maxSize - minSize);
    return size; // Returns a single float size
}

// Calculates the center position for a heart shape.
sf::Vector2f GeometryPhysicsUtilities::calculateHeartCenter(const sf::Vector2f& scrollOffset, 
    const sf::Vector2f& itemSize, const float size)
{
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
    float ceilingY = GraphicUtilities::getCeilingY();
    float floorY = GraphicUtilities::getFloorY();

    sf::Vector2f heartSizeBounds = GeometryPhysicsUtilities::getHeartBoundingBox(size);
    float marginX = heartSizeBounds.x / 2.f + itemSize.x / 2.f + 10.f;
    float marginY = heartSizeBounds.y / 2.f + itemSize.y / 2.f + 10.f;

    float minCenterX = marginX;
    float maxCenterX = windowSize.x - marginX;
    float centerX = minCenterX + static_cast<float>(std::rand()) / RAND_MAX * (maxCenterX - minCenterX);

    float minCenterY = ceilingY + marginY;
    float maxCenterY = floorY - marginY;
    float centerY = minCenterY + static_cast<float>(std::rand()) / RAND_MAX * (maxCenterY - minCenterY);

    return scrollOffset + sf::Vector2f(centerX, centerY);
}

// Calculates the number of items for a line shape.
int GeometryPhysicsUtilities::calculateLineNumItems()
{
    int minItems = 3;
    int maxItems = 10;
    return minItems + (std::rand() % (maxItems - minItems + 1));
}

// Calculates the start and end points for a line shape, adjusting item count if necessary.
std::pair<sf::Vector2f, sf::Vector2f> GeometryPhysicsUtilities::calculateLineStartEndPoints(const sf::Vector2f& scrollOffset,
    int& numItems, const float itemWidth, const float gap)
{
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
    float margin = 50.f;
    int minItems = 3; // Minimum items in a line

    float angle = static_cast<float>(std::rand()) / RAND_MAX * 2 * 3.14159265f;
    float lineLength = (numItems - 1) * (itemWidth + gap);
    float dx = std::cos(angle) * lineLength;
    float dy = std::sin(angle) * lineLength;

    float minStartX = margin + std::max(0.f, -dx);
    float maxStartX = windowSize.x - margin - std::max(0.f, dx);
    float minStartY = margin + std::max(0.f, -dy);
    float maxStartY = windowSize.y - margin - std::max(0.f, dy);

    // Loop to adjust numItems if the line goes out of bounds
    while ((minStartX > maxStartX || minStartY > maxStartY) && numItems > minItems) {
        numItems--;
        lineLength = (numItems - 1) * (itemWidth + gap);
        dx = std::cos(angle) * lineLength;
        dy = std::sin(angle) * lineLength;
        minStartX = margin + std::max(0.f, -dx);
        maxStartX = windowSize.x - margin - std::max(0.f, dx);
        minStartY = margin + std::max(0.f, -dy);
        maxStartY = windowSize.y - margin - std::max(0.f, dy);
    }

    if (numItems < minItems) {
        return { {0.f, 0.f}, {0.f, 0.f} }; // Return invalid points if no valid range found
    }

    float startX = minStartX + static_cast<float>(std::rand()) / RAND_MAX * (maxStartX - minStartX);
    float startY = minStartY + static_cast<float>(std::rand()) / RAND_MAX * (maxStartY - minStartY);

    sf::Vector2f start = scrollOffset + sf::Vector2f(startX, startY);
    sf::Vector2f end = scrollOffset + sf::Vector2f(startX + dx, startY + dy);

    return { start, end };
}

float GeometryPhysicsUtilities::clampHeartCenterY(const float desiredCenterY, 
    const float heartHeight, const float ceilingY, const float floorY)
{
    float halfHeartHeight = heartHeight / 2.0f;

    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

    float normalizedBufferY = windowSize.y * 0.01f;

    float minAllowedY = ceilingY + halfHeartHeight + normalizedBufferY;
    float maxAllowedY = floorY - halfHeartHeight - normalizedBufferY;

    // Clamp the Y coordinate
    float clampedY = std::max(minAllowedY, std::min(desiredCenterY, maxAllowedY));

    return clampedY;
}
