#pragma once 
#include <SFML/Graphics.hpp>

// window utilities related
const int boardRows = 20;

const int boardCols = 40;

const float sizingWindowPercentage = 0.8f;

//const float playerRelativeX = 0.1f;
const float playerRelativeX = 0.15f;

const float playerRelativeYFloor = 0.85f;

const float playerRelativeYCeiling = 0.169f;

const float flameRelativeX = -0.012f; // relative X position of the flame to the player

const float flameRelativeY = 0.094f; // relative Y position of the flame to the player

const float dinoFireRelativeX = 0.16f; // relative X position of the flame to the player

const float dinoFireRelativeY = -0.015f; // relative Y position of the flame to the player

const float dinoWingsRelativeX = 0.03f; // relative X position of the wings to the player

const float dinoWingsRelativeY = 0.025f; // relative Y position of the wings to the player

const float WavesRelativeX = 0.1f; // relative X position of the waves to the bat

const float WavesRelativeY = -0.01f; // relative Y position of the waves to the bat

const float EggDropMinRelativeX = 0.12f; // relative X position of the egg to the chicken

const float EggDropMinRelativeY = 0.4f; // relative Y position of the egg to the chicken

//--- buttons related:

const sf::Vector2f playButtonOffset = { 0.05f, 0.65f };

constexpr int PixelAlphaLimit= 127;

inline constexpr float ButtonSoundVolume = 300.f;

// background related

constexpr float ScrollSpeed = 400.f;

inline constexpr float WaveBaseYRatio = 0.2f;

inline constexpr float FarWaveYMultiplier = 1.5f;

inline const sf::Vector2f WavesWindowFraction = { 1.f, 0.7f };

inline constexpr float WaveTopYRatio = 0.3f;

inline const sf::Color WaveSemiTransparentColor = sf::Color(255, 255, 255, 160);

inline constexpr int NumWaves = 4;

inline constexpr float WingsSoundVolume = 90.f;

const int SHARK_RANDOM_NUMBER = 3;

const int seaStateIndex = 4;

const int numSpecialStates = 5;