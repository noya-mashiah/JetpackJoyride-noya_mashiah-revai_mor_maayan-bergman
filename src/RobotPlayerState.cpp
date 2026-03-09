#include "RobotPlayerState.h"
#include "Player.h"

RobotPlayerState::RobotPlayerState(sf::Sprite& sprite, Animation& animation)
	: PlayerState(sprite, animation), m_hourglass(Hourglass::getDefaultParams())
{
	spriteAnimationInit(RobotPlayerState::getDefaultValues());
	init();
	initializeSparkles();
}

void RobotPlayerState::handleInput(const sf::Event&  event)
{
	if (m_isLanding) return;

	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		&& m_sprite.getPosition().y >= m_floorY)
		fly();
}

void RobotPlayerState::update(const sf::View& view, const float deltaTime) 
{
	if (m_isLanding) updateSmoothLanding(view, deltaTime);

	updateTimer(deltaTime);

	if (m_invincible)
	{
		for (auto& s : m_sparkles)
			s->update(view, deltaTime);

		m_hourglass.update(view, deltaTime);
	}

	if (m_curGiftCount < m_maxGiftCount) m_specialGiftTimer += deltaTime;
}

void RobotPlayerState::render(sf::RenderWindow& window) const 
{
	if (m_invincible)
	{
		for (const auto& s : m_sparkles)
			s->render(window);

		m_hourglass.render(window);
	}
}

void RobotPlayerState::move(const sf::View& view, const float deltaTime)
{
	if (m_isLanding || !m_command) return;

	m_command->execute(view, deltaTime);

	if (m_command->shouldSwitchToWalk()) walk();
}

GameObjectParams RobotPlayerState::getDefaultValues()
{
	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

	return GameObjectParams("RobotState", { 0.17f ,0.3f },
		sf::Vector2f(windowSize.x * playerRelativeX,
	    GraphicUtilities::getFloorY() - windowSize.y * 0.08f),
		3, 0, 1, 0.3f, true);
}

void RobotPlayerState::onGasTankCollected()
{
	Pickables::playPickupSoundSpecialGift();

	m_invincible = true;

	m_invincibleTimer = maxDuration;

	m_hourglass.reset();
}

void RobotPlayerState::processHit(Player& player)
{
	if (m_invincible || m_isLanding) return;

	player.setState(std::make_unique<RegularPlayerState>(m_sprite, m_animation));
}

std::unique_ptr<Pickables> RobotPlayerState::addGift(const sf::Vector2f& scrollOffset)
{
	if (m_curGiftCount < m_maxGiftCount && m_specialGiftTimer > maxDurationGift)
	{
		m_curGiftCount++;
		m_specialGiftTimer = 0.f;

		std::unique_ptr<Pickables> newGasTank = GameObjectFactory::createSpecialGift(scrollOffset,
								GasTank::getDefaultParams({0.f, 0.f}));
		return newGasTank;
	}
	else return nullptr;
}

void RobotPlayerState::init()
{
	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

	m_floorY = GraphicUtilities::getFloorY() - windowSize.y * 0.08f;
	m_ceilingY = GraphicUtilities::getCeilingY() + windowSize.y * 0.02f;

	m_command = std::make_unique<WalkCommand>(m_sprite);
	m_floorSoundName = "RobotRunSound";
	m_airSoundName = "RobotEngineSound";
	m_soundState = SoundState(m_floorSoundName, true);
}

void RobotPlayerState::fly()
{
	m_command = std::make_unique<FlyCommand>(m_sprite, 1200.f, -400.f,
		m_floorY, m_ceilingY);

	m_animation.setAnimation(GameObjectParams("RobotState", { 0.17f ,0.3f },
		m_sprite.getPosition(), 3, 2, 2, 0.3f, false));
	m_soundState.setSound(m_airSoundName, true);
	m_soundState.setVolume(50);
	m_soundState.play();
}

void RobotPlayerState::walk()
{
	m_command = std::make_unique<WalkCommand>(m_sprite);

	m_animation.setAnimation(GameObjectParams("RobotState", { 0.17f ,0.3f },
		m_sprite.getPosition(), 3, 0, 1, 0.3f, true));

	playWalk();
}

void RobotPlayerState::playWalk()
{
	m_soundState.setSound(m_floorSoundName, true);
	m_soundState.setVolume(80);
	m_soundState.play();
}

void RobotPlayerState::onLandingComplete()
{
	playWalk();
}

void RobotPlayerState::initializeSparkles()
// Initializes the sparkles effect cluster around the robot.
{
	m_sparkles.clear();

	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();
	float radius = windowSize.x * 0.09f;
	int numSparkles = 15;

	std::vector<sf::Vector2f> circlePoints =
		GeometryPhysicsUtilities::pointsOnCircle({ 0, 0 }, radius, numSparkles);

	float visualOffsetX = -0.035f * windowSize.x;
	float visualOffsetY = 0.017f * windowSize.y;

	for (const auto& offset : circlePoints)
	{
		m_sparkles.push_back(std::make_unique<PlayerEffect>(
			PlayerEffect::getSparkleDefaultParams(m_sprite.getPosition()),
			[this]() { return m_sprite.getPosition(); },
			-(offset.x + visualOffsetX),  // xOffset
			offset.y + visualOffsetY   // yOffset
		));
	}
}
