#include "MissileAlarm.h"

// Static member initialization
bool MissileAlarm::m_registerit = GameObjectFactory::registerIt("FirstAlarmWarning",
							[](const GameObjectParams& params) -> std::unique_ptr<GameObject>
	{
		return std::make_unique<MissileAlarm>(params);
	});

MissileAlarm::MissileAlarm(const GameObjectParams& params)
	: StaticObject(params), m_animation(m_sprite, params), m_windowScale(params._windowScale)
{
	scaleInit();
}

void MissileAlarm::update(const sf::View& view, const float deltaTime)
{
	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
	 
	float rightViewEdge = view.getCenter().x + view.getSize().x / 2.f;

	float xPos = rightViewEdge - windowSize.x * 0.02f;
	float yPos = m_sprite.getPosition().y;

	m_sprite.setPosition(xPos, yPos);

	m_animation.update(deltaTime);
}

void MissileAlarm::render(sf::RenderWindow& window) const
{
    if (m_visible) m_animation.render(window);
}

GameObjectParams MissileAlarm::getDefaultParams(const sf::Vector2f& pos)
{
	return GameObjectParams("FirstAlarmWarning", { 0.05f, 0.1f }, pos,
							2, 0, 1, 0.3f, true);
}

void MissileAlarm::setIsVisible(const bool visible)
{
	m_visible = visible;
}

// change to second alarm, means missile is closer
void MissileAlarm::changeAlarmState()
{
	m_animation.setAnimation(GameObjectParams("SecondAlarmWarning", { 0.05f, 0.1f },
		m_sprite.getPosition(),2, 0, 1, 0.3f, true));
	
	scaleInit();
	checkNeedToPlaySound();
}

void MissileAlarm::scaleInit()
{
	sf::Vector2f origin((float)m_sprite.getTexture()->getSize().x / 2,
		(float)m_sprite.getTexture()->getSize().y / 2);
	
	m_sprite.setOrigin(origin);

	setScale(GraphicUtilities::getGameObjectScale(m_windowScale,
		m_sprite.getTextureRect()));
}

void MissileAlarm::playAlarmSound()
{
	static sf::Sound sound;

	sound.setBuffer(ResourcesManager::getInstance().getSound("MissileAlarm"));
	sound.setVolume(70);

	sound.play();
}

// so the sound will be played only once 
void MissileAlarm::checkNeedToPlaySound()
{
	if (m_visible && !m_playedAlready)
	{
		m_playedAlready = true;
		playAlarmSound();
	}
}
