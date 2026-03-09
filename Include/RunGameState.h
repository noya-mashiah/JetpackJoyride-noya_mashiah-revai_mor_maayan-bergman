#pragma once 
#include "GameState.h"

class BaseButton;

/*
* Represent the screen of running the game
*/

class RunGameState : public GameState
{
public:
	RunGameState(GameManager* gameManager,
		const std::string& musicName = " ", const float soundVol = 50);

	virtual void handleInput(const sf::Event& event) override;

	virtual void onEnter() override;

	virtual void onExit() override;

	virtual void pause() override;

protected:

	virtual void buttonsInit() override;
};
