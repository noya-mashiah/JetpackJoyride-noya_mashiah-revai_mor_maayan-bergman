#pragma once
#include "RunGameState.h"

/*
* represent the under water state of the game
*/

class SeaGameState : public RunGameState
{
public:

	SeaGameState(GameManager* gameManager,
		const std::string& musicName = "SeaStateSound");

	virtual void update(const float deltaTime) override;

	virtual void render() const override;

	virtual void onEnter() override;
	virtual void onExit() override;

private:
	void playMusic();

	void updateTimerText();

	void renderTextTimer() const;

	float m_waterTimer = 0.f;
	
	static constexpr float WaterDuration = 61.f; // 60 seconds

	sf::Text m_timerText;
};
