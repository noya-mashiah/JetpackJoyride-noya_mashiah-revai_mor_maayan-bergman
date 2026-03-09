#include "Missile.h"

bool Missile::m_registerit = GameObjectFactory::registerIt("Missile", [](const GameObjectParams& params) -> std::unique_ptr<GameObject>
	{
		return std::make_unique<Missile>(params);
	});

namespace { // helper function to initialize the m_alarm properly
	std::unique_ptr<MissileAlarm> createMissileAlarm(const GameObjectParams& params) {
		auto basePtr = GameObjectFactory::create("FirstAlarmWarning", params);
		return std::unique_ptr<MissileAlarm>(static_cast<MissileAlarm*>(basePtr.release()));
	}
}

Missile::Missile(const GameObjectParams& params)
	: Enemy(params)
	, m_alarm(createMissileAlarm(MissileAlarm::getDefaultParams({ 0.f, m_sprite.getPosition().y})))
{
	soundInit("MissileLaunch", false, 45);
}

void Missile::update(const sf::View& view, const float deltaTime)
// Updates missile movement, animation, and alarm visibility/state based on its position relative to the view.
{
	move(view, deltaTime);
	m_animation.update(deltaTime);

	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

	float viewRightEdge = view.getCenter().x + view.getSize().x / 2.f;

	if (m_sprite.getPosition().x >= viewRightEdge)
	{
		if (m_alarm) m_alarm->update(view, deltaTime);

		if (m_sprite.getPosition().x <= viewRightEdge + windowSize.x * playerRelativeX * 5)
			if (m_alarm) m_alarm->changeAlarmState();
	}
	else
	{
		if (m_alarm) m_alarm->setIsVisible(false);

		checkNeedToPlaySound(viewRightEdge);
	}
}

void Missile::render(sf::RenderWindow& window) const
{
	m_animation.render(window);

	if (m_alarm) m_alarm->render(window);
}

GameObjectParams Missile::getDefaultParams(const sf::Vector2f& pos)
{
	return GameObjectParams("Missile", { 0.07f, 0.08f }, pos,
							7, 0, 6, 0.1f, true);
}

void Missile::playExplodeSound()
{
	static sf::Sound sound;
	sound.setBuffer(ResourcesManager::getInstance().getSound("MissileExplode"));
	sound.setVolume(70);
	sound.play();
}

void Missile::move(const sf::View& view, const float deltaTime)
{
	(void)view;
	sf::Vector2f curPos = m_sprite.getPosition();
	m_sprite.setPosition(curPos.x - 700.f * deltaTime, curPos.y);
}

void Missile::checkNeedToPlaySound(const float viewRightEdge)
{
	float objPos = m_sprite.getPosition().x + m_sprite.getGlobalBounds().width;

	Enemy::checkNeedToPlaySound(objPos, viewRightEdge);
}
