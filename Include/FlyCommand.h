#pragma once
#include "PlayerCommand.h"

/*
* represent the command of flying
*/

class FlyCommand : public PlayerCommand
{
public:

	using PlayerCommand::PlayerCommand;

	virtual void execute(const sf::View& view, const float deltaTime) override;

	virtual bool shouldSwitchToWalk() const override;

};
