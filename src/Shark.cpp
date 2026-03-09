#include "Shark.h"

bool Shark::m_registerit = GameObjectFactory::registerIt("Shark", [](const GameObjectParams& params) -> std::unique_ptr<GameObject>
	{
		return std::make_unique<Shark>(params);
	});

Shark::Shark(const GameObjectParams& params)
	: Enemy (params)
{
	sf::Vector2f scale = m_sprite.getScale();
	m_sprite.setScale(-scale.x, scale.y);
	soundInit("Jaws", true, 50);
	ResourcesManager::getInstance().getMusic("SeaStateSound").setVolume(10);
	m_sound.play();
}

void Shark::update(const sf::View& view, const float deltaTime)
{
	move(view, deltaTime);
	m_animation.update(deltaTime);
	checkNeedToPlaySound(view);
}


GameObjectParams Shark::getDefaultParams(const sf::Vector2f& pos)
{
	return GameObjectParams("Shark", { 0.15f, 0.15f }, pos,
		6, 0, 5, 0.1f, true);
}

void Shark::playBiteSound()
{
	static sf::Sound sound;
	static bool initialized = false;

	if (!initialized)
	{
		sound.setBuffer(ResourcesManager::getInstance().getSound("BiteSound"));
		sound.setVolume(80);
		initialized = true;
	}
	sound.play();
}

void Shark::move(const sf::View& view, const float deltaTime)
{
	(void)view;
	sf::Vector2f curPos = m_sprite.getPosition();
	m_sprite.setPosition(curPos.x - 200.f * deltaTime, curPos.y);
}

void Shark::checkNeedToPlaySound(const sf::View& view)
{
	float fixedPlayerX = view.getCenter().x - (view.getSize().x / 2) +
		(GraphicUtilities::getWindowSize().x * playerRelativeX);

	if (!m_playedSound && m_sprite.getPosition().x <= fixedPlayerX)
	{
		m_playedSound = true;
		ResourcesManager::getInstance().getMusic("SeaStateSound").setVolume(37);
	}
}
