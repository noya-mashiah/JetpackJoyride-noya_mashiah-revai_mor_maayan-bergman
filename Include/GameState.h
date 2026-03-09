/**
* GameState.h
*  Abstract base class for all game states
*
* The GameState class defines the interface and shared logic for different game states,
* including update, render, input handling, and button management.
*
* Enables the State design pattern for flexible and extensible game flow.
* Provides utility functions for button and background management.
**/
#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class GameManager;
class BaseButton;
class CommandButton;

class GameState
{
public:
    GameState(GameManager* gameManager, const std::string& musicName = " ", const float soundVol = 50);
    virtual void update(const float deltaTime) = 0;
    virtual void render() const = 0;
    virtual void handleInput(const sf::Event& event) = 0;
	virtual ~GameState() = default;

    virtual void moveHelpLeft() {};
    
    virtual void moveHelpRight() {};

    virtual void mute();
    virtual void unmute();

    virtual void onEnter();
    virtual void onExit();

    virtual void pause(); 
    virtual void resume();
    virtual void quit(){} 

protected:

    virtual void buttonsInit() = 0;

    virtual void updateButtons();

    virtual void renderButtons() const;

    virtual void handleButtonsInput(const sf::Event& event);

    std::vector< std::unique_ptr<BaseButton>> m_buttons;

    void backgroundInit(sf::Sprite& background, const std::string& textureName);

    void createMuteButton(const sf::Vector2f& windowScale = { 0.07f, 0.12f }, 
                          const sf::Vector2f& pos = { 0.92f, 0.02f });

    void createTuggleButton(const sf::Vector2f& windowScale, const sf::Vector2f& pos,
        const std::string& offName, const std::string& onName,
        std::unique_ptr<CommandButton> commandOff, std::unique_ptr<CommandButton> commandOn);

	GameManager* m_gameManager; // not a unique ptr in order to not destroy the 
                                // game manager while switching states

    std::string m_musicName;
    float m_soundVolume;
};
