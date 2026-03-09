/**
 *  GameObjectParams.h
 *  Struct for holding parameters needed to initialize a game object.
 *
 * GameObjectParams encapsulates texture, scale, position, animation, and loop settings
 * for flexible and consistent object creation throughout the game.
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct GameObjectParams
{
	GameObjectParams() = default;

	GameObjectParams(const std::string& textureName, const sf::Vector2f& windowScale,
		const sf::Vector2f& position, const int countFrames = 1,
		const int startFrame = 0, const int endFrame = 0, const float frameTime = 0.f,
		const bool loop = false)
		: _textureName(textureName), _windowScale(windowScale), _position(position),
		_countFrames(countFrames), _startFrame(startFrame), _endFrame(endFrame),
		_frameTime(frameTime), _loop(loop) {}

	std::string _textureName = " "; // Name of the texture to be used
	sf::Vector2f _windowScale = { 0.f, 0.f }; // Percentage of the window the object will take
	sf::Vector2f _position = { 0.f, 0.f };   // Position of the object in the window
	int _countFrames = 0;        // Number of frames in the animation
	int _startFrame = 0;        // Starting frame of the animation
	int _endFrame = 0;          // Ending frame of the animation
	float _frameTime = 0.f;       // Time each frame is displayed
	bool _loop = false;            // Whether the animation should loop
};
