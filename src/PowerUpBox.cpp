#include "PowerUpBox.h"
#include "Player.h"
#include "GameManager.h"

// Static member initialization 
int PowerUpBox::m_curState = 0;

// Static member initialization
bool PowerUpBox::m_registerit = GameObjectFactory::registerIt("PowerUpBox", [](const GameObjectParams& params)
	-> std::unique_ptr<GameObject>
	{
		return std::make_unique<PowerUpBox>(params);
	});

PowerUpBox::PowerUpBox(const GameObjectParams& params)
	: Pickables(params)
{
	scaleSetUp(params._windowScale);
}

void PowerUpBox::update(const sf::View& view, const float deltaTime) { (void)view; (void)deltaTime;}

GameObjectParams PowerUpBox::getDefaultParams(const sf::Vector2f& pos)
{
	return GameObjectParams("PowerUpBox", {0.06f, 0.11f}, pos);
}

// for collision
// Applies a random power-up effect to the player
void PowerUpBox::applyToPlayer(Player& player)
{
    // if in invuncible mode or died
    if (player.isInvincible() || !player.canCollectPowerUpBox()) return;

    static std::unordered_map<int, std::function<void(Player&)>> playerStatesMap = {
        {0, [](Player& p) { p.changeToRobotState(); }},
        {1, [](Player& p) { p.changeToUpsideDownState(); }},
        {2, [](Player& p) { p.changeToBirdState(); }},
        {3, [](Player& p) { p.changeToDinosaurState(); }},
        {4, [](Player& p) { p.changeToSurferState(); }}
    };
    int choice = rand() % numSpecialStates;
    if (choice == m_curState) choice = (choice + 1) % numSpecialStates; // ensuring difference from 
                                                                        //the current state
    m_curState = choice;

    // Got special state sea
    if (m_curState == seaStateIndex) GameManager::requestState(GameManager::StateRequest::Sea);

    auto it = playerStatesMap.find(choice);

    if (it != playerStatesMap.end()) it->second(player);
}

// has a unique sound
void PowerUpBox::playPickedSound()
{
    static sf::Sound sound;
    static bool initialized = false;

    if (!initialized)   // make sure happens only once ( gets called in collision check)
    {
        sound.setBuffer(ResourcesManager::getInstance().getSound("PowerUpSound"));
        sound.setVolume(60);
        initialized = true;
    }
    sound.play();
}
