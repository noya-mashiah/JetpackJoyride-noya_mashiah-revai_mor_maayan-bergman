#pragma once
#include "QuitButtonCommand.h"
#include "PlayCommandButton.h"
#include "HelpCommand.h"
#include "ReturnToMenuCommand.h"
#include "HelpLeftCommand.h"
#include "HelpRightCommand.h"
#include "UnmuteCommand.h"
#include "MuteCommand.h"
#include "ShowHighScoresCommand.h"
#include "ResumeCommand.h"
#include "PauseCommand.h"
#include "GraphicUtilities.h"
#include "Collision.h"
#include <thread>        // For std::this_thread
#include <chrono>        // For std::chrono::millisec

// Holds configuration data for initializing a button's appearance and layout
struct ButtonData
{
    sf::Vector2f _windowScale = { 0.f, 0.f };
    sf::Vector2f _pos = { 0.f, 0.f };
    std::string _offTextureName = " ";
    std::string _onTextureName = " ";

    ButtonData() = default;

    ButtonData(const sf::Vector2f& windowScale, const sf::Vector2f& pos,
        const std::string& offTextureName, const std::string& onTextureName = " ")
        : _windowScale(windowScale), _pos(pos), _offTextureName(offTextureName),
        _onTextureName(onTextureName) {
    }
};

/*
* an abstract class represent a button
*/

class BaseButton
{
public:
    BaseButton(const ButtonData& data, std::unique_ptr<CommandButton> command);

    virtual ~BaseButton() = default;

    virtual void render(sf::RenderWindow& window) const;

    virtual void update(const sf::RenderWindow& window) = 0;

    virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    virtual void flipScale();

    void setCommand(std::unique_ptr<CommandButton> newCommand);

protected:

    void soundInit();

    void playSound();

    virtual void executeClick();

    bool isClickedOn();

    void setPosition(const sf::Vector2f& pos);

    void spriteInit(const ButtonData& data);

    bool m_click = false;

    sf::Sprite m_sprite;

    std::unique_ptr<CommandButton> m_command;

    sf::Sound m_sound;

    int m_soundDuration = 200;
};
