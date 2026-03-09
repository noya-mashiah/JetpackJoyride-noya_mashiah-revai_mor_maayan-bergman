#include "Pickables.h"

sf::Sound Pickables::m_specialGiftSound;

std::vector<std::unique_ptr<Pickables>> Pickables::addBonusGift(const sf::Vector2f& scrollOffset) const
{ (void)scrollOffset; return {}; }

void Pickables::playPickupSound()
{
	static sf::Sound sound;
	static bool initialized = false;

	if (!initialized)
	{
		sound.setBuffer(ResourcesManager::getInstance().getSound("Coin"));
		sound.setVolume(200);
		initialized = true;
	}

	sound.play();
}

void Pickables::playPickupSoundSpecialGift()
{
	static bool initialized = false;
	if (!initialized)
	{
		m_specialGiftSound.setBuffer(ResourcesManager::getInstance().getSound("SpecialGiftSound"));
		m_specialGiftSound.setVolume(70);
		initialized = true;
	}
	m_specialGiftSound.play();
}

void Pickables::stopSpecialGiftSound()
{
	if (m_specialGiftSound.getStatus() == sf::Sound::Playing)
		m_specialGiftSound.stop();
}
