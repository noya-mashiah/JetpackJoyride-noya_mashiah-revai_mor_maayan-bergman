#include "Enemy.h"

void Enemy::soundInit(const std::string& soundName, const bool shouldLoop, const float volume)
{
	m_sound.setBuffer(ResourcesManager::getInstance().getSound(soundName));
	m_sound.setLoop(shouldLoop);
	m_sound.setVolume(volume);
}

void Enemy::checkNeedToPlaySound(const float objPos, const float limitPos)
{
	if (!m_playedSound && (objPos <= limitPos))
	{
		m_sound.play();
		m_playedSound = true;
	}
}
