#include "MainMenuState.h"
#include "GameManager.h"
#include "SimpleButton.h"
#include "HoverButton.h"
#include "TuggleButton.h"
#include <vector>
#include <memory>

MainMenuState::MainMenuState(GameManager* gameManager) : 
    GameState(gameManager, "MenuMusic")
{
    backgroundInit(m_background, "OpenningBackground");
    buttonsInit();
}

void MainMenuState::update(float deltaTime)
{
    (void)deltaTime;
    GameState::updateButtons();
}

void MainMenuState::render() const
{
    if (m_gameManager)
    {
        auto& window = m_gameManager->getWindow();

        window.setView(window.getDefaultView());

        window.draw(m_background);

        GameState::renderButtons();
    }
}

void MainMenuState::handleInput(const sf::Event& event)
{
    GameState::handleButtonsInput(event);
}

void MainMenuState::quit()
{
    if (m_gameManager) m_gameManager->getWindow().close();
}

void MainMenuState::buttonsInit()
// Initializes the buttons for the main menu.
{
    m_buttons.clear();
    static std::vector<sf::Vector2f> scales = { {0.3f, 0.3f} , {0.3f, 0.3f} , {0.3f, 0.28f}, { 0.08f, 0.13f } };
    static std::vector<sf::Vector2f> positions = { { 0.05f, 0.65f } , { 0.35f, 0.65f } , { 0.65f, 0.66f }, { 0.025f, 0.03f } };
    static std::vector<std::pair<std::string, std::string>> names =
    {
        {"HelpOff", "HelpOn"},
        {"PlayGameOff", "PlayGameOn"},
        {"QuitOff", "QuitOn"},
        {"TrophyButton", " "}
    };

    std::vector<std::unique_ptr<CommandButton>> commands;
    commands.push_back(std::make_unique<HelpCommand>(m_gameManager));
    commands.push_back(std::make_unique<PlayCommandButton>(m_gameManager));
    commands.push_back(std::make_unique<QuitButtonCommand>(m_gameManager));
    commands.push_back(std::make_unique<ShowHighScoresCommand>(m_gameManager));
    
    for (int i = 0; i < 4; ++i) {
        ButtonData data(scales[i], positions[i], names[i].first, names[i].second);
        if (i < 3)
             m_buttons.push_back(std::make_unique<HoverButton>(data, std::move(commands[i])));
       else if (i == 3)
            m_buttons.push_back(std::make_unique<SimpleButton>(data, std::move(commands[i])));
    }

    createMuteButton({ 0.07f, 0.12f }, { 0.92f, 0.02f });
}
