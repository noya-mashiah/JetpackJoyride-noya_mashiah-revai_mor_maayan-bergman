/**
 * LandGameState.h
 *  Defines the LandGameState, the main gameplay state for land environments.
 *
 * The LandGameState class manages the update and rendering logic for the land gameplay section,
 * inheriting from RunGameState and integrating with the GameManager.
 */
#pragma once
#include "RunGameState.h"

class LandGameState : public RunGameState
{
public:
	using RunGameState::RunGameState;

	LandGameState(GameManager* gameManager, 
			      const std::string& musicName = "JetpackJoyrideMusic");

	virtual void update(const float deltaTime) override;

	virtual void render() const override;
};
