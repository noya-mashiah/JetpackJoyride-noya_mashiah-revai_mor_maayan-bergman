#include "CollisionManager.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "Exceptions.h"

#include "Collision.h"

#include "Player.h"
#include "Coin.h"
#include "LaserObstacle.h"
#include "PowerUpBox.h"
#include "Missile.h"
#include "Chicken.h"
#include "GasTank.h"
#include "ProjectileEnemy.h"

#include "Meat.h"
#include "Shell.h"
#include "Crab.h"
#include "Shark.h"

namespace
{
	void playerCoinCollide(GameObject& player, GameObject& coin)
	{
		static_cast<Coin&>(coin).applyToPlayer(static_cast<Player&>(player));

		Pickables::playPickupSound();
	}

	void playerGasTankCollide(GameObject& player, GameObject& gasTank)
	{
		static_cast<GasTank&>(gasTank).applyToPlayer(static_cast<Player&>(player));
	}

	void playerMeatCollide(GameObject& player, GameObject& meat)
	{
		static_cast<Meat&>(meat).applyToPlayer(static_cast<Player&>(player));
	}

	void playerPowerBoxCollide(GameObject& player, GameObject& powerUpBox)
	{
		static_cast<PowerUpBox&>(powerUpBox).applyToPlayer(static_cast<Player&>(player));

		PowerUpBox::playPickedSound();
	}

	void playerShellCollide(GameObject& player, GameObject& shell)
	{
		static_cast<Shell&>(shell).applyToPlayer(static_cast<Player&>(player));
	}

	void playerPearlCollide(GameObject& player, GameObject& pearl)
	{
		static_cast<Pearl&>(pearl).applyToPlayer(static_cast<Player&>(player));
		Pickables::playPickupSound();
	}

	void playerLaserCollide(GameObject& player, GameObject& laser)
	{
		static_cast<Player&>(player).processHit();
		static_cast<LaserObstacle&>(laser).playZappSound();
	}

	void playerMissileCollide(GameObject& player, GameObject& missile)
	{
		(void)missile;
		static_cast<Player&>(player).processHit();
		Missile::playExplodeSound();
	}

	void playerChickenCollide(GameObject& player, GameObject& chicken)
	{
		(void)chicken;
		static_cast<Player&>(player).processHit();
		Missile::playExplodeSound();
	}

	void playerProjectileEnemyCollide(GameObject& player, GameObject& projectile)
	{
		(void)projectile;
		static_cast<Player&>(player).processHit();
		Missile::playExplodeSound();
	}

	void playerCrabCollide(GameObject& player, GameObject& crab)
	{
		(void)crab;
		static_cast<Player&>(player).processHit();
		Crab::playPinchSound();
	}

	void playerSharkCollide(GameObject& player, GameObject& shark)
	{
		(void)shark;
		static_cast<Player&>(player).processHit();
		Shark::playBiteSound();
	}

	using Key = std::pair<std::type_index, std::type_index>;
	using CollisionFunc = void (*)(GameObject&, GameObject&);
	using HitMap = std::map<Key, CollisionFunc>;

	HitMap HitMapInit()
	{
		HitMap phm;
		phm[Key(typeid(Player), typeid(Coin))] = &playerCoinCollide;
		phm[Key(typeid(Player), typeid(PowerUpBox))] = &playerPowerBoxCollide;
		phm[Key(typeid(Player), typeid(GasTank))] = &playerGasTankCollide;
		phm[Key(typeid(Player), typeid(Meat))] = &playerMeatCollide;
		phm[Key(typeid(Player), typeid(Shell))] = &playerShellCollide;
		phm[Key(typeid(Player), typeid(Pearl))] = &playerPearlCollide;
		phm[Key(typeid(Player), typeid(LaserObstacle))] = &playerLaserCollide;
		phm[Key(typeid(Player), typeid(Missile))] = &playerMissileCollide;
		phm[Key(typeid(Player), typeid(Chicken))] = &playerChickenCollide;
		phm[Key(typeid(Player), typeid(ProjectileEnemy))] = &playerProjectileEnemyCollide;
		phm[Key(typeid(Player), typeid(Crab))] = &playerCrabCollide;
		phm[Key(typeid(Player), typeid(Shark))] = &playerSharkCollide;

		return phm;
	}

	CollisionFunc lookUp(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = HitMapInit();

		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));

		if (mapEntry == collisionMap.end())
			return nullptr;

		return mapEntry->second;
	}
}

void processCollision(GameObject& obj1, GameObject& obj2)
// Handles the collision between two game objects by dispatching to the correct handler based on their types.
{
	auto phf = lookUp(typeid(obj1), typeid(obj2));

	if (!phf) throw UnknownCollisionException(obj1, obj2);

	phf(obj1, obj2);
}
