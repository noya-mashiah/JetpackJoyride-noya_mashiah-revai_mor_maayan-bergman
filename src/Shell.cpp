#include "Shell.h"
#include "Player.h"
#include "GameObjectFactory.h"

// Static member initialization
bool Shell::m_registerit = GameObjectFactory::registerIt("Shell",
	[](const GameObjectParams& params) -> std::unique_ptr<GameObject>
	{
		return std::make_unique<Shell>(params);
	});

Shell::Shell(const GameObjectParams& params)
	: Pickables(params), m_animation(m_sprite, params)
{
	scaleSetUp(params._windowScale);

	sf::FloatRect bounds = m_sprite.getLocalBounds();

	m_sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Shell::update(const sf::View& view, const float deltaTime) 
{
	(void)deltaTime; (void)view;
	m_animation.update(deltaTime);
}

void Shell::render(sf::RenderWindow& window) const
{
	m_animation.render(window);
}

GameObjectParams Shell::getDefaultParams(const sf::Vector2f& pos)
{
	return GameObjectParams("Shell", { 0.3f, 0.4f }, pos, 2, 0, 0, 0.f,
		false);
}

// for collision
void Shell::applyToPlayer(Player& player)
{
	m_animation.setAnimation(GameObjectParams("Shell", { 0.2f, 0.3f }, m_sprite.getPosition(),
		2, 1, 1, 0.f, false));
	player.onShellCollected();
}

// for collision
std::vector<std::unique_ptr<Pickables>> Shell::addBonusGift(const sf::Vector2f& scrollOffset) const
{
	return GameObjectFactory::createPearls(m_sprite.getPosition(), scrollOffset);
}

// Has a unique pickup sound 
void Shell::playPickedSound()
{
	static sf::Sound sound;
	static bool initialized = false;

	if (!initialized)
	{
		sound.setBuffer(ResourcesManager::getInstance().getSound("ShellSound"));
		sound.setVolume(70);
		initialized = true;
	}
	sound.play();
}
