/**
 * SoundState.h
 * Utility class for managing sound playback and state.
 *
 * The SoundState class wraps an sf::Sound object, providing methods to set, play, pause, stop,
 * and manage the state of sound effects. Supports saving and restoring sound state, looping, and pitch.
 * Used for flexible sound control in game objects and player states.
 */
#pragma once
#include "ResourcesManager.h"

class SoundState
{
public:
    // Default constructor
    SoundState();

    // Constructor that takes sound name and automatically sets it up
    SoundState(const std::string& soundName, bool shouldLoop = false, float pitch = 1.0f);

    // Main method to set and play sound
    void setSound(const std::string& soundName, bool shouldLoop = false, float pitch = 1.0f);

    // Control methods
    void play();
    void stop();
    void pause();

    // State management
    void saveState();
    void restoreState();
    void reset();

    // Getters
    bool wasPlaying() const;
    void setVolume(const float amount = 50);

    
private:
    sf::Sound m_sound;

    // Saved state
    bool m_wasPlaying = false;
    std::string m_savedSoundName = "";
    bool m_savedShouldLoop = false;
    float m_savedPitch = 1.0f;
};
