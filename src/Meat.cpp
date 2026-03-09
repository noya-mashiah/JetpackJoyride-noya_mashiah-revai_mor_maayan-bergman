#include "Meat.h"
#include "Player.h"

// Static member initialization
bool Meat::m_registerit = GameObjectFactory::registerIt("Meat",
	[](const GameObjectParams& params) -> std::unique_ptr<GameObject>
	{
		return std::make_unique<Meat>(params);
	});

Meat::Meat(const GameObjectParams& params)
	: Pickables(params)
{
	scaleSetUp(params._windowScale);
}

void Meat::update(const sf::View& view, const float deltaTime) { (void)view; (void)deltaTime; }

GameObjectParams Meat::getDefaultParams(const sf::Vector2f& pos)
{
	return GameObjectParams("Meat", { 0.07f, 0.14f }, pos);
}

// for collision
void Meat::applyToPlayer(Player& player)
{
	player.onMeatCollected();
}


