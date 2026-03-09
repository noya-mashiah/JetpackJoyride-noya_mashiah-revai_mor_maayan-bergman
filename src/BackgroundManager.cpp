#include "BackgroundManager.h"

BackgroundManager::BackgroundManager()
	: m_hallAnimation(HallAnimation::getDefaultParams({0.f, 0.f })),
	  m_view(sf::FloatRect(0, 0, GraphicUtilities::getWindowSize().x,
		     GraphicUtilities::getWindowSize().y))
{
	backgroundInit();

	WavesInit();
}

void BackgroundManager::update(const float deltaTime)
{
	if (m_viewMovementStopped) return;

	m_scrollSpeed += 5.0f * deltaTime;

	m_view.move(m_scrollSpeed * deltaTime * m_scrollSpeedAddition, 0.f);

	m_hallAnimation.update(m_view, deltaTime);

	moveBackground();
}

void BackgroundManager::render(sf::RenderWindow& window) const
{
	m_hallAnimation.render(window);
}

void BackgroundManager::renderWaves(sf::RenderWindow& window) const
{
	for (const auto& w : m_waves)
		window.draw(w);
}

void BackgroundManager::renderWalls(sf::RenderWindow& window) const
{
	window.draw(m_background1);

	window.draw(m_background2);
}

const sf::View& BackgroundManager::getView() const
{
	return m_view;
}

bool BackgroundManager::doesNeedToCreateObjects() const
{
	return m_needToCreateObjects;
}

sf::Vector2f BackgroundManager::getScrollOffSet() const
{
	return m_offSet;
}

void BackgroundManager::setScrollSpeedAddition(const float scrollSpeedAddition)
{
	m_scrollSpeedAddition = scrollSpeedAddition;
}

void BackgroundManager::updateWaves()
{
	moveWaves();
}

void BackgroundManager::reset()
{
	m_view = sf::View(sf::FloatRect(0, 0, GraphicUtilities::getWindowSize().x,
		GraphicUtilities::getWindowSize().y));

	m_scrollSpeed = ScrollSpeed;
	m_scrollSpeedAddition = 1.f;

	backgroundInit();

	m_hallAnimation.reset();

	m_viewMovementStopped = false;
	m_needToCreateObjects = true;
	m_offSet = { 0.f, 0.f };
}

void BackgroundManager::stopViewMovement()
{
	m_scrollSpeed = 0.f;
	m_scrollSpeedAddition = 0.f;
	m_viewMovementStopped = true;
}

void BackgroundManager::moveBackground()
{
	m_needToCreateObjects = false;

	m_offSet = { 0.f, 0.f };

	checkIfBackgroundMoved(m_background1, m_background2);
	checkIfBackgroundMoved(m_background2, m_background1);
}

void BackgroundManager::moveWaves()
{
	const float yPos = GraphicUtilities::getWindowSize().y * WaveBaseYRatio;

	for (int i = 0; i < m_waves.size(); ++i)
	{
		const sf::Sprite& bg = (i % 2 == 0) ? m_background1 : m_background2;

		const float yMultiplier = (i < 2) ? 1.f : FarWaveYMultiplier;

		m_waves[i].setPosition(bg.getPosition().x, yPos * yMultiplier);
	}
}

void BackgroundManager::backgroundInit()
{
	setBackground(m_background1, 0.f);
	setBackground(m_background2, 1.f);
}

void BackgroundManager::setBackground(sf::Sprite& background ,const float xOffSet)
{
	background.setTexture(ResourcesManager::getInstance().getTexture("Hall"));

	background.setScale(GraphicUtilities::getBackgroundScale("Hall"));

	float backgroundWidth = background.getTexture()->getSize().x * m_background1.getScale().x;
	
	background.setPosition(GraphicUtilities::getWindowSize().x + xOffSet * backgroundWidth, 0.f);
}

// Initializes the wave sprites used in the background
void BackgroundManager::WavesInit()
{
	auto& wavesTexture = ResourcesManager::getInstance().getTexture("Wave");
	const auto& textureSize = wavesTexture.getSize();

	sf::IntRect fullRect(0, 0, textureSize.x, textureSize.y);
	sf::Vector2f desiredWindowFraction = WavesWindowFraction;
	// Calculate the scale to fit the waves within the desired window fraction
	sf::Vector2f scale = GraphicUtilities::getGameObjectScale(desiredWindowFraction, fullRect);

	m_waves.clear();
	m_waves.resize(NumWaves);

	for (int i = 0; i < NumWaves; ++i)
	{
		m_waves[i].setTexture(wavesTexture);
		m_waves[i].setColor(WaveSemiTransparentColor);
		m_waves[i].setScale(scale);
	}
}

// Checks if backgroundA has moved out of the visible view on the left side
// if so - repositions backgroundA to the right side of backgroundB to create a continuous scrolling effect
void BackgroundManager::checkIfBackgroundMoved(sf::Sprite& backgroundA, sf::Sprite& backgroundB)
{
	float backgroundWidth = backgroundA.getTexture()->getSize().x * backgroundA.getScale().x;

	if (backgroundA.getPosition().x + backgroundWidth < m_view.getCenter().x - m_view.getSize().x / 2)
	{
		backgroundA.setPosition(backgroundB.getPosition().x + backgroundWidth, 0.f);

		m_needToCreateObjects = true;

		m_offSet = backgroundA.getPosition();
	}
}
