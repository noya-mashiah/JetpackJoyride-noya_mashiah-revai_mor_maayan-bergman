#include "RegularPlayerState.h"
#include "Player.h"

RegularPlayerState::RegularPlayerState(sf::Sprite& sprite, Animation& animation)
	: PlayerState(sprite, animation),
	m_flame(PlayerEffect::getFlameDefaultParams(m_sprite.getPosition()),
		[&sprite]() { return sprite.getPosition(); },
		GraphicUtilities::getWindowSize().x * flameRelativeX,  // xOffset
		GraphicUtilities::getWindowSize().y* flameRelativeY,     // yOffset
		true)

{
	spriteAnimationInit(RegularPlayerState::getDefaultValues());
	init();
}

void RegularPlayerState::handleInput(const sf::Event& event)
{
	if (m_isLanding) return;

	// case flying 
	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		&& m_sprite.getPosition().y >= m_floorY)
		fly();
}

void RegularPlayerState::update(const sf::View& view, const float deltaTime)
{
	if (m_isLanding) updateSmoothLanding(view, deltaTime);

	m_flame.update(view, deltaTime);
}

void RegularPlayerState::render(sf::RenderWindow& window) const
{
	m_flame.render(window);
}

void RegularPlayerState::move(const sf::View& view, const float deltaTime)
{
	if (m_isLanding || !m_command) return;

	m_command->execute(view, deltaTime);

	if (m_command->shouldSwitchToWalk()) walk();
}

GameObjectParams RegularPlayerState::getDefaultValues()
{
	return GameObjectParams("BerryWalking", { 0.07f ,0.17f },
			sf::Vector2f(GraphicUtilities::getWindowSize().x * playerRelativeX,
		    GraphicUtilities::getFloorY()),
			4, 0, 2, 0.2f, true);
}

// for collision
void RegularPlayerState::processHit(Player& player)
{
	if (m_isLanding) return;

	player.setState(std::make_unique<DiePlayerState>(m_sprite, m_animation));
}

void RegularPlayerState::init()
{
	m_floorY = GraphicUtilities::getFloorY();
	m_ceilingY = GraphicUtilities::getCeilingY();

	// in sea state the player is with transparency - this changes it to opaque mode
	sf::Color solid(255, 255, 255, 255);

	m_sprite.setColor(solid);

	m_command = std::make_unique<WalkCommand>(m_sprite);
	m_floorSoundName = "RegularStateRunSound";
	m_airSoundName = "EngineSound";
	m_soundState.setSound(m_floorSoundName, true, 0.8f);
}

void RegularPlayerState::fly()
{
	m_command = std::make_unique<FlyCommand>(m_sprite, 1200.f, -400.f,
		m_floorY, m_ceilingY);

	m_animation.setAnimation(GameObjectParams("BerryWalking", { 0.07f ,0.17f },
		m_sprite.getPosition(), 4, 3, 3, 0.f, false));
	m_soundState.setSound(m_airSoundName, true);
	m_soundState.setVolume(50);
	m_soundState.play();
}

void RegularPlayerState::walk()
{
	m_command = std::make_unique<WalkCommand>(m_sprite);

	m_animation.setAnimation(GameObjectParams("BerryWalking", { 0.07f ,0.17f },
		m_sprite.getPosition(), 4, 0, 2, 0.2f, true));
	playWalk();
}

void RegularPlayerState::playWalk()
{
	m_soundState.setSound(m_floorSoundName, true, 0.8f);
	m_soundState.setVolume(60);
	m_soundState.play();
}

// player reached the floor 
void RegularPlayerState::onLandingComplete()
{
	playWalk();
}
