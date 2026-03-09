/**
 *  GameManager.h
 *  Central class for managing the main game loop, states, and core systems.
 *
 * The GameManager class coordinates the overall flow of the game, including the main loop,
 * state transitions (menu, gameplay, pause, help, etc.), window management, and integration
 * of core components such as the Controller, BackgroundManager, and InfoBar.
 *
 * Implements the State design pattern for flexible game state management.
 * Handles input, rendering, sound, and game reset logic
 */
#pragma once
#include <cstdlib>
#include <ctime>
#include <memory>
#include "WindowUtilities.h"
#include "LandGameState.h"
#include "SeaGameState.h"
#include "MainMenuState.h"
#include "HelpState.h"
#include "HighScoresState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "Controller.h"
#include "BackgroundManager.h"
#include "InfoBar.h"
#include "ReturnToMenuCommand.h"

class GameManager
{
public:
	GameManager();
    
    void run();

    sf::RenderWindow& getWindow();

	void update(const float deltaTime);

	void updateWaves();

	void render();

	void renderWaves();

	void renderWalls();

	void handleInput(const sf::Event& event);

	// state requests in order to switch states vua requests in the command to prevent memory leakage
	enum class StateRequest { None, Land, Sea, Menu, Help, scoreBorad, Pause, Resume, GameOver };

	static void requestState(const StateRequest req);

	void moveHelpLeft();

	void moveHelpRight();

	void mute();

	void unmute();
	
	bool isPaused() const;

	void renderPausedState();

	void resetGame();

	void onEnter();

	void onExit(); 

	void stopPausedStateSounds();

	void mutePausedState();

	void unmutePausedState();

	bool isMuted() const;

	void quit();

private:

	void saveSoundState();

	void restoreSoundState();

    void setState(std::unique_ptr<GameState> state);
	
	void clearAllButLamps();

	void revertPlayerToRegularState();

	void pauseGame();

	void resumeGame();

	void gameOver();

    void windowInit();

	void setIcon();

	void handleStateRequest();

	std::unique_ptr<Controller> m_controller;

	std::unique_ptr<BackgroundManager> m_backgroundManager;

	std::unique_ptr<InfoBar> m_infoBar;

	bool m_scoreSaved = false;

	sf::RenderWindow m_window;

	std::unique_ptr<GameState> m_state;

	static StateRequest m_nextStateRequest;

	std::unique_ptr<GameState> m_pausedState;
	
	bool m_isPaused = false;

	bool m_isMuted = false;
};
