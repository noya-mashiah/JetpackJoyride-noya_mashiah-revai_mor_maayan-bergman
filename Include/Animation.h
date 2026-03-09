/**
 *  Animation.h
 *  Handles sprite sheet animation for game objects.
 *
 * The Animation class manages frame-based animation for sprites, including updating frames,
 * controlling playback (play, stop, reset), and rendering the current frame.
 *
 * Uses parameters from GameObjectParams to configure animation properties,
 * and provides utility functions for frame/time control and querying animation state.
 */
#pragma once
#include "ResourcesManager.h"
#include "GraphicUtilities.h"
#include "GameObjectParams.h"

class Animation
{
public:

	Animation() = default; 

    Animation(sf::Sprite& sprite, const GameObjectParams& params);

    void update(const float deltaTime);

    void setAnimation(const GameObjectParams& params);

    void render(sf::RenderWindow& window) const;

    bool isPlaying() const;

	void play();
	void stop();
	void reset();

    void setFrameTime(const float frameTime);

    int getCurFrameNum() const;

    bool isAtLastFrame() const;

private:
    void updateFrame();

    sf::Sprite& m_sprite;

    int m_totalFrameCount = 0;

    int m_curFrameNum = 0;

    int m_startFrame = 0;

    int m_endFrame = 0;;

    int m_actualFrameCount = 0;

    float m_givenFrameTime = 0.f;

    float m_elapsedTime = 0.f;

    int m_frameWidth = 0; // interval of a discrete frame

    int m_frameHeight = 0;

    bool m_loop;

    bool m_playing = true; // for knowing if it has been played once for logical reasons
};
