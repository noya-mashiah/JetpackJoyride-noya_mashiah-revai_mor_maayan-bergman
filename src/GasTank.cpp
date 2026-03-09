#include "GasTank.h"
#include "Player.h"

// Static member initialization
bool GasTank::m_registerit = GameObjectFactory::registerIt("GasTank", [](const GameObjectParams& params)
	-> std::unique_ptr<GameObject>
	{
		return std::make_unique<GasTank>(params);
	});

GasTank::GasTank(const GameObjectParams& params)
	: Pickables(params)
{
	scaleSetUp(params._windowScale);
}

void GasTank::update(const sf::View& view, const float deltaTime) { (void)view; (void)deltaTime;}

GameObjectParams GasTank::getDefaultParams(const sf::Vector2f& pos)
{
	return GameObjectParams("GasTank", { 0.07f, 0.11f }, pos, 0, 0, 0, 0.f, false);
}

// for collision
void GasTank::applyToPlayer(Player& player)
{
	player.onGasTankCollected();
}
