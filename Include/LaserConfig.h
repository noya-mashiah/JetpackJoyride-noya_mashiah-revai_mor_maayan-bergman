/**
 * LaserConfig.h
 *  Defines the LazerConfig struct for laser obstacle configuration.
 *
 * LazerConfig calculates and stores the position and length of a laser obstacle,
 * using randomization within playable area constraints.
 *
* The struct is constructed with a scroll offset and uses utility functions
 * to determine window and playable area dimensions.
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "GraphicUtilities.h"



struct LazerConfig 
{
    float _laserLength;                         // Length of the laser obstacle
    float _xStartPos;                           // X starting position of the laser
    float _yStartPos;                           // Y starting position of the laser
    float _boxTopLeftX;                         // Top-left X coordinate of the laser box
    float _boxTopLeftY;                         // Top-left Y coordinate of the laser box

    LazerConfig(const sf::Vector2f& scrollOffset)
    {
        sf::Vector2f scrollOffSet = scrollOffset;
        sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
        float ceilingY = GraphicUtilities::getCeilingY();
        float floorY = GraphicUtilities::getFloorY();
       
        // Calculate buffer zones to keep lasers away from screen edges
        float bufferX = windowSize.x * 0.05f;
        float bufferY = windowSize.y * 0.2f;
        
        // Calculate playable area dimensions
        float playableHeight = floorY - ceilingY;
        
        // Calculate spawnable ranges for laser positioning
        float spawnableXRange = windowSize.x - (2 * bufferX);
        float spawnableYRange = playableHeight - bufferY;
        
        // Generate random laser length within reasonable bounds
        float minLength = playableHeight * 0.17f;
        float maxLength = playableHeight * 0.35f;
        
        _laserLength = minLength + (static_cast<float>(std::rand()) / RAND_MAX) * (maxLength - minLength);
        
        // Calculate spawnable areas accounting for laser length
        float spawnableWidth = windowSize.x - (2 * bufferX) - _laserLength;
        float spawnableHeight = playableHeight - _laserLength;
        float spawnableXRangeForLaser = spawnableXRange - _laserLength;
        
        // Generate random starting positions for the laser
        _xStartPos = bufferX + scrollOffSet.x + (std::rand() % static_cast<int>(spawnableXRangeForLaser));
        _yStartPos = ceilingY + scrollOffSet.y + (std::rand() % static_cast<int>(spawnableYRange));
        
        // Generate random top-left positions for the laser box
        _boxTopLeftX = bufferX + scrollOffSet.x + (static_cast<float>(std::rand()) / RAND_MAX) * spawnableWidth;
        _boxTopLeftY = ceilingY + scrollOffSet.y + (static_cast<float>(std::rand()) / RAND_MAX) * spawnableHeight;
    }
};
