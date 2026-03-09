#pragma once
#include "StaticObject.h"
#include "Animation.h"

/**
 *  A projectile object that can be attached to parent objects and move independently
 *
 * The Projectile class represents visual effects like waves or light balls that follow
 * parent objects (like enemies) and can play sounds when they enter the view.
 * It inherits from StaticObject and includes animation capabilities.
 */

class Projectile : public StaticObject
{
public:
    Projectile() = default;
    Projectile(const GameObjectParams& params);

    virtual void update(const sf::View& view, const float deltaTime) override;
    virtual void render(sf::RenderWindow& window) const override;

    static GameObjectParams getWavesDefaultParams(const sf::Vector2f& pos);
    static GameObjectParams getLightBallDefaultParams(const sf::Vector2f& pos);

    void setGetParentPosFunc(std::function<sf::Vector2f()> func);
    void setSound(const std::string& soundName, const float vol);
    void playSound();

private:
    void setPosAndScale(const GameObjectParams& params);
    void offsetsInit();
    void soundInit(const std::string& soundName);
    void checkNeedToPlaySound(const sf::View& view);

    Animation m_animation;
    std::function<sf::Vector2f()> m_getParentPos;

    float m_xOffset = 0.f;
    float m_yOffset = 0.f;

    static bool m_registerit;

    sf::Sound m_sound;
    bool m_playedSound = false;  // flag to prevent sound from playing multiple times
    float m_volume = 60;
};
