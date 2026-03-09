#include "Pearl.h"
#include "Player.h"

// Static member initialization
bool Pearl::m_registerit = GameObjectFactory::registerIt("Pearl", [](const GameObjectParams& params)
	-> std::unique_ptr<GameObject>
	{
		return std::make_unique<Pearl>(params);
	});

Pearl::Pearl(const GameObjectParams& params)
	: Pickables(params)
{
	scaleSetUp(params._windowScale);
}
void Pearl::update(const sf::View& view, const float deltaTime) { (void)view; (void)deltaTime;}

GameObjectParams Pearl::getDefaultParams(const sf::Vector2f& pos)
{
	return GameObjectParams("Pearl", { 0.02f, 0.04f }, pos);
}

// for collision
void Pearl::applyToPlayer(Player& player)
{
	player.onPearlCollected();
}

// Calculates and returns the scaled size of the peral based on window scale
sf::Vector2f Pearl::getSize(const sf::Vector2f& windowScale)
{
	const sf::Texture& pearlTexture = ResourcesManager::getInstance().getTexture("Pearl");
	sf::IntRect textureRect(0, 0, pearlTexture.getSize().x, pearlTexture.getSize().y);
	sf::Vector2f scale = GraphicUtilities::getGameObjectScale(windowScale, textureRect);
	float pearlWidth = pearlTexture.getSize().x * scale.x;
	float pearlHeight = pearlTexture.getSize().y * scale.y;
	return { pearlWidth, pearlHeight };
}
