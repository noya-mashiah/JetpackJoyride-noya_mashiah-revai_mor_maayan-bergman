#include "HallAnimation.h"

HallAnimation::HallAnimation(const GameObjectParams& params)
    : StaticObject(params), m_animation(m_sprite, params) 
{
    setScale(GraphicUtilities::getGameObjectScale(params._windowScale, 
                                                  m_sprite.getTextureRect()));

    soundInit();
}

void HallAnimation::update(const sf::View& view, const float deltaTime)
{
    (void)view;
    m_animation.update(deltaTime);

    checkNeedToPlaySound();
}


GameObjectParams HallAnimation::getDefaultParams(const sf::Vector2f& pos)
{
	return GameObjectParams("StartOfHallExplosion", { 1.f, 1.f }, pos,
                            10, 0, 9, 0.1f, false);
}

void HallAnimation::reset()
{
    m_animation.setAnimation(HallAnimation::getDefaultParams({ 0.f, 0.f }));
    m_playedSound = false;
}

void HallAnimation::soundInit()
{
    m_sound.setBuffer(ResourcesManager::getInstance().getSound("StartingExplosion"));
    m_sound.setVolume(50);
}

void HallAnimation::checkNeedToPlaySound()
{
    if (m_playedSound) return;

    m_sound.play();
    m_playedSound = true;
}
