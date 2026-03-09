#include "WindowUtilities.h"

windowConfig WindowUtilities::calculateWindowConfig()
{
    // Get the user's desktop resolution
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    float tileW = (desktop.width / boardCols) * sizingWindowPercentage;
    float tileH = (desktop.height / boardRows) * sizingWindowPercentage ;
    float tileSize = std::min(tileW, tileH);

    // Calculate the actual window size based on tile size and board dimensions
    float finalWidth = tileSize * boardCols;
    float finalHeight = tileSize * boardRows;

    return { finalWidth, finalHeight };
}
