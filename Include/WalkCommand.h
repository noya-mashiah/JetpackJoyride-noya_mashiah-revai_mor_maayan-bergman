#pragma once
#include "PlayerCommand.h"

/*
* represent the walking command of the player
*/

class WalkCommand : public PlayerCommand
{
public:
	using PlayerCommand::PlayerCommand;
	
	virtual ~WalkCommand() = default;

	virtual void execute(const sf::View& view, const float deltaTime) override;

	virtual bool shouldSwitchToWalk() const override;
};
