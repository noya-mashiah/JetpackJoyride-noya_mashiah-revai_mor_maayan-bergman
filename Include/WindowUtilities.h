#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Consts.h"

///*
// * windowConfig Struct
// * -------------------
// * Holds the result of screen configuration:
// * - _tileSize: Calculated size of a single tile in pixels.
// * - _windowWidth: Final width of the game window.
// * - _windowHeight: Final height of the game window (includes InfoBar).
// */
struct windowConfig
{
	float _windowWidth;
	float _windowHeight;
};

///*
// * WindowUtilities Class
// * ---------------------
// * Utility class responsible for calculating a responsive window layout based on:
// * - The number of board rows and columns.
// * - The resolution of the user's desktop.
// * - A fixed ratio reserved for the InfoBar (e.g., score/time display).
// *
// * Goal:
// * -----
// * To ensure a unified and scalable interface across different screen resolutions,
// * so that the game appears correctly proportioned on any device.
// */
class WindowUtilities
{
public:

	static windowConfig calculateWindowConfig();
};
