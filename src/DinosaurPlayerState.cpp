#include "DinosaurPlayerState.h"
#include "Player.h"

DinosaurPlayerState::DinosaurPlayerState(sf::Sprite& sprite, Animation& animation)
	: PlayerState(sprite, animation), 
	m_fire(PlayerEffect::getDinoFireDefaultParams(m_sprite.getPosition()),
		[&sprite]() { return sprite.getPosition(); },
		GraphicUtilities::getWindowSize().x * dinoFireRelativeX,    // xOffset (positive)
		GraphicUtilities::getWindowSize().y * dinoFireRelativeY, // yOffset (negative)
		false),

	m_wings(PlayerEffect::getDinoWingsDefaultParams(m_sprite.getPosition()),
		[&sprite]() { return sprite.getPosition(); },
		GraphicUtilities::getWindowSize().x * dinoWingsRelativeX,   // xOffset (positive)
		GraphicUtilities::getWindowSize().y * dinoWingsRelativeY,  // yOffset (positive)
		false),
	m_hourglass(Hourglass::getDefaultParams())
{
	spriteAnimationInit(DinosaurPlayerState::getDefaultValues());
	init();
}

void DinosaurPlayerState::handleInput(const sf::Event& event)
{
	if (m_isLanding || m_invincible) return;

	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		&& m_sprite.getPosition().y >= m_floorY)
		jump();

	if (m_command->shouldPlaySound()) playJump();
}

void DinosaurPlayerState::update(const sf::View& view, const float deltaTime)
// Updates landing, timers, invincibility effects, and gift timer.
{
	if (m_isLanding) updateSmoothLanding(view, deltaTime);

	updateTimer(deltaTime);

	if (!m_invincible && m_command && m_command->shouldSwitchToWalk()) walk();

	if (m_invincible)
	{
		m_fire.update(view, deltaTime);
		m_wings.update(view, deltaTime);
		m_hourglass.update(view, deltaTime);
	}

	if (m_curGiftCount < m_maxGiftCount) m_specialGiftTimer += deltaTime;
}

void DinosaurPlayerState::render(sf::RenderWindow& window) const
{
	if (m_invincible)
	{
		m_fire.render(window);
		m_wings.render(window);
		m_hourglass.render(window);
	}
}

void DinosaurPlayerState::move(const sf::View& view, const float deltaTime)
{
	if (m_isLanding || !m_command) return;

	m_command->execute(view, deltaTime);

	if (!m_invincible && m_command->shouldSwitchToWalk()) walk();
}

// Handles meat collection, triggers invincibility, animation, and sound.
void DinosaurPlayerState::onMeatCollected()
{
	Pickables::playPickupSoundSpecialGift();

	m_invincible = true;

	m_invincibleTimer = maxDuration;

	m_animation.setAnimation(GameObjectParams("DinoJumping", { 0.15f ,0.25f },
		m_sprite.getPosition(), 5, 4, 4, 0.f, false));

	m_soundState.setSound("DinoRoar");
	m_soundState.setVolume(80);
	m_soundState.play();

	m_command = std::make_unique<FlyCommand>(m_sprite, 1200.f, -400.f, m_floorY, m_ceilingY);

	m_viewSpeedMultiplier = 4.f;

	m_hourglass.reset();
}

GameObjectParams DinosaurPlayerState::getDefaultValues()
{
	return GameObjectParams("DinoWalking", { 0.15f ,0.25f },
		sf::Vector2f(GraphicUtilities::getWindowSize().x * playerRelativeX,
			GraphicUtilities::getFloorY()),
		4, 0, 3, 0.2f, true);
}

std::unique_ptr<Pickables> DinosaurPlayerState::addGift(const sf::Vector2f& scrollOffset)
{
	if (m_curGiftCount < m_maxGiftCount && m_specialGiftTimer > maxDurationGift)
	{
		m_curGiftCount++;
		m_specialGiftTimer = 0.f;

		std::unique_ptr<Pickables> newMeat = GameObjectFactory::createSpecialGift(scrollOffset,
																Meat::getDefaultParams({ 0.f, 0.f }));
		return newMeat;
	}
	else return nullptr;
}

void DinosaurPlayerState::processHit(Player& player)

{
	if (m_invincible || m_isLanding) return;

	player.setState(std::make_unique<RegularPlayerState>(m_sprite, m_animation));
}

void DinosaurPlayerState::onInvincibilityEnd()
// Ends invincibility, transitions to landing and walking.
{
	m_isLanding = true;

	m_command = std::make_unique<WalkCommand>(m_sprite);
	m_animation.setAnimation(GameObjectParams("DinoWalking", { 0.15f ,0.25f },
		m_sprite.getPosition(), 4, 0, 3, 0.2f, true));

	m_viewSpeedMultiplier = 1.f;
}

void DinosaurPlayerState::init()
{
	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

	m_floorY = GraphicUtilities::getFloorY() - windowSize.x * 0.02f;
	m_ceilingY = GraphicUtilities::getCeilingY();

	m_command = std::make_unique<WalkCommand>(m_sprite);

	soundInit();
}

void DinosaurPlayerState::soundInit()
{
	m_floorSoundName = "DinoWalkSound";
	m_airSoundName = "DinoJump";
	m_soundState.setSound(m_floorSoundName, true);
}

void DinosaurPlayerState::onLandingComplete()
{
	playWalk();
}

void DinosaurPlayerState::walk()
{
	m_command = std::make_unique<WalkCommand>(m_sprite);

	m_animation.setAnimation(GameObjectParams("DinoWalking", { 0.15f ,0.25f },
		m_sprite.getPosition(), 4, 0, 3, 0.2f, true));
	playWalk();
}

void DinosaurPlayerState::playWalk()
{
	m_soundState.setSound(m_floorSoundName, true);
	m_soundState.setVolume(47);
	m_soundState.play();
}

void DinosaurPlayerState::jump()
{
	static int lastJumpCount = 0;

	m_command = std::make_unique<JumpCommand>(m_sprite, 1200.f, -400.f,
		m_floorY, m_ceilingY);

	m_animation.setAnimation(GameObjectParams("DinoJumping", { 0.15f ,0.25f },
		m_sprite.getPosition(), 5, 0, 4, 0.2f, false));
}

void DinosaurPlayerState::playJump()
{
	m_soundState.setSound(m_airSoundName);
	m_soundState.setVolume(95);
	m_soundState.play();
}
