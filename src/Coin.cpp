#include "Coin.h"
#include "Player.h"

// Static member initialization
bool Coin::m_registerit = GameObjectFactory::registerIt("Coin",
	[](const GameObjectParams& params) -> std::unique_ptr<GameObject> 
	{
	return std::make_unique<Coin>(params);
	});


Coin::Coin(const GameObjectParams& params)
	: Pickables(params), m_animation(m_sprite, params)
{
	scaleSetUp(params._windowScale);
}

void Coin::update(const sf::View& view, const float deltaTime)
{
	(void)view;
	m_animation.update(deltaTime);
}

void Coin::render(sf::RenderWindow& window) const
{
	m_animation.render(window);
}

GameObjectParams Coin::getDefaultParams(const sf::Vector2f& pos)
{
	return GameObjectParams("Coin", { 0.02f, 0.04f }, pos,
							8, 0, 7, 0.1f, true);
}

// for collision
void Coin::applyToPlayer(Player& player)
{
	player.onCoinCollected();
}

// Calculates and returns the scaled size of the coin based on window scale
sf::Vector2f Coin::getSize(const sf::Vector2f& windowScale)
{
	const sf::Texture& coinTexture = ResourcesManager::getInstance().getTexture("Coin");
	sf::IntRect textureRect(0, 0, coinTexture.getSize().x, coinTexture.getSize().y);
	sf::Vector2f scale = GraphicUtilities::getGameObjectScale(windowScale, textureRect);
	float coinWidth = coinTexture.getSize().x * scale.x;
	float coinHeight = coinTexture.getSize().y * scale.y;
	return { coinWidth, coinHeight };
}
