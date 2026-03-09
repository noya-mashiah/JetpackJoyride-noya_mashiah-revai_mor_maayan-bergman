#include "BirdPlayerState.h"
#include "Player.h"

BirdPlayerState::BirdPlayerState(sf::Sprite& sprite, Animation& animation)
	: PlayerState(sprite, animation)
{
	spriteAnimationInit(BirdPlayerState::getDefaultValues());
	init();
	initializeGroundSparkles();
	initializeEatingSparkles();
	initializeDollarBills();
}

void BirdPlayerState::handleInput(const sf::Event& event)
// Handles input for flying  and triggers flying animation and sound.
{
	if (m_isLanding) return;

	if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		&& m_sprite.getPosition().y >= m_floorY)
	{
		m_command = std::make_unique<FlyCommand>(m_sprite, FlyCommandGravity, FlyCommandjumpForce,
			m_floorY, m_ceilingY);


		m_animation.setAnimation(GameObjectParams(TextureName, WindowScaleFly,m_sprite.getPosition(),
			FrameCount, StartFrameFly, EndFrame, FrameTimeFly, Loop));

		playFly();
	}
}

void BirdPlayerState::update(const sf::View& view, const float deltaTime)
{
	if (m_isLanding) updateSmoothLanding(view, deltaTime);

	if (m_isEatingCoin && !m_animation.isPlaying())
	{
		m_isEatingCoin = false;

		// Return to appropriate animation based on current command
		if (m_sprite.getPosition().y >= m_floorY)
		{
			m_animation.setAnimation(GameObjectParams(TextureName, WindowScaleGround,m_sprite.getPosition(),
				FrameCount, StartAndEndFrameGround, StartAndEndFrameGround, FrameTimeGround, NoLoop));
		}
		else
		{
			m_animation.setAnimation(GameObjectParams(TextureName, WindowScaleFly,m_sprite.getPosition(),
				FrameCount, StartFrameFly, EndFrame, FrameTimeFly, Loop));
		}
	}

	updateIf(m_eatingSparkles, m_isEatingCoin, view, deltaTime);
	updateIf(m_dollarBills, !isOnGround(), view, deltaTime);
	updateIf(m_groundSparkles, isOnGround(), view, deltaTime);
}

void BirdPlayerState::render(sf::RenderWindow& window) const
{
	renderIf(m_eatingSparkles, m_isEatingCoin, window);
	renderIf(m_dollarBills, !isOnGround(), window);
	renderIf(m_groundSparkles, isOnGround(), window);
}

void BirdPlayerState::move(const sf::View& view, const float deltaTime)
{
	if (m_isLanding || !m_command) return;

	m_command->execute(view, deltaTime);

	if (m_command->shouldSwitchToWalk())
	{
		m_command = std::make_unique<WalkCommand>(m_sprite);
		m_animation.setAnimation(GameObjectParams(TextureName, WindowScaleGround, m_sprite.getPosition(),
			FrameCount, StartAndEndFrameGround, StartAndEndFrameGround, FrameTimeGround, NoLoop));

		m_landingSound.play();
		playSlide();
	}
}

void BirdPlayerState::onCoinCollected(int& coinCounter)
{
	if (!m_isEatingCoin) m_yippySound.play();
	m_animation.setAnimation(GameObjectParams(TextureName, WindowScaleGround, m_sprite.getPosition(),
		FrameCount, StartFrameEatCoin, EndFrameEatCoin, FrameTimeEatCoin, NoLoop));

	coinCounter += CoinValue;

	m_isEatingCoin = true;
}

GameObjectParams BirdPlayerState::getDefaultValues()
{
	return GameObjectParams(TextureName, WindowScaleGround,
		sf::Vector2f(GraphicUtilities::getWindowSize().x * playerRelativeX,
			GraphicUtilities::getFloorY()),
		FrameCount, StartAndEndFrameGround, StartAndEndFrameGround, FrameTimeGround, NoLoop);
}

void BirdPlayerState::initializeGroundSparkles()
// Initializes the ground sparkles effect cluster.
{
	m_groundSparkles.clear();

	int numSparkles = NumGroundSparkels;
	float spacing = m_sprite.getGlobalBounds().width / (numSparkles + 1);

	float yOffset = m_sprite.getGlobalBounds().height * GroundSparkleYOffsetRatio;

	for (int i = 1; i <= numSparkles; ++i)
	{
		m_groundSparkles.push_back(std::make_unique<PlayerEffect>(
			PlayerEffect::getSparkleDefaultParams(m_sprite.getPosition()),
			[this]() { return m_sprite.getPosition(); },
			-(-m_sprite.getGlobalBounds().width / 2.f + i * spacing),  // xOffset
			yOffset  // yOffset
		));
	}
}

void BirdPlayerState::initializeEatingSparkles()
// Initializes the eating sparkles effect cluster.
{
	m_eatingSparkles.clear();

	int numSparkles = NumEatingSparkels;
	sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

	// Base position (mouth area) - normalized
	float baseXOffset = -windowSize.x * 0.06f;
	float baseYOffset = -windowSize.y * 0.01f;

	for (int i = 0; i < numSparkles; ++i)
	{
		// Create a more natural cluster effect
		float clusterRadius = windowSize.x * 0.015f; // Cluster radius
		float angle = (std::rand() % 360) * 3.14159f / 180.0f; // Random angle
		float distance = (std::rand() % 100) * 0.01f * clusterRadius; // Random distance within cluster

		float clusterX = baseXOffset + distance * std::cos(angle);
		float clusterY = baseYOffset + distance * std::sin(angle);

		m_eatingSparkles.push_back(std::make_unique<PlayerEffect>(
			PlayerEffect::getSparkleDefaultParams(m_sprite.getPosition()),
			[this]() { return m_sprite.getPosition(); },
			-clusterX,  // xOffset
			clusterY   // yOffset
		));
	}
}

void BirdPlayerState::initializeDollarBills()
// Initializes the dollar bills swirl effect cluster.
{
	initializeSwirlItems(m_dollarBills, GameObjectParams("Dollar", { 0.05f ,0.07f }, m_sprite.getPosition(),
		8, 0, 7, 0.7f, true));
}

bool BirdPlayerState::isOnGround() const
{
	return (std::abs(m_sprite.getPosition().y - m_floorY) < 1.0f);
}

void BirdPlayerState::init()
{
	m_floorY = static_cast<float>((float)GraphicUtilities::getFloorY() + GraphicUtilities::getWindowSize().x * 0.012);
	m_ceilingY = static_cast<float>((float)GraphicUtilities::getCeilingY());

	m_command = std::make_unique<WalkCommand>(m_sprite);
	soundInit();
}

void BirdPlayerState::soundInit()
{
	m_command = std::make_unique<WalkCommand>(m_sprite);
	m_floorSoundName = "BirdSlide";
	m_airSoundName = "BirdFlap";
	m_soundState.setSound(m_floorSoundName, true);
	m_soundState.setVolume(60);

	auto& inst = ResourcesManager::getInstance();
	m_landingSound.setBuffer(inst.getSound("BirdLanding"));
	m_landingSound.setVolume(70);

	m_yippySound.setBuffer(inst.getSound("BirdYippie"));
	m_yippySound.setVolume(80);
}

void BirdPlayerState::onLandingComplete()
{
	m_landingSound.play();
	playSlide();
}

void BirdPlayerState::playFly()
{
	m_soundState.setSound(m_airSoundName, true);
	m_soundState.setVolume(60);
	m_soundState.play();
}

void BirdPlayerState::playSlide()
{
	m_soundState.setSound(m_floorSoundName, true);
	m_soundState.setVolume(65);
	m_soundState.play();
}
