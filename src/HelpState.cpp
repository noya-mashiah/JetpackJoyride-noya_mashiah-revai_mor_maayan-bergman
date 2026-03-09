#include "HelpState.h"
#include "GameManager.h"

HelpState::HelpState(GameManager* gameManager) : GameState(gameManager, "HelpMusic")
{
    backgroundInit(m_background, "HelpPage1");

    buttonsInit();
}

void HelpState::update(float deltaTime)
{
    (void)deltaTime;
    updateBackground();
}

void HelpState::render() const
{
    if (m_gameManager)
    {
        auto& window = m_gameManager->getWindow();

        window.setView(window.getDefaultView());

        window.draw(m_background);

        for (int i = 0; i < m_buttons.size(); i++)
        {
            if ((m_curPage == 0 && i == left_t) ||
                (m_curPage == m_maxNumPages - 1 && i == right_t))
                continue;

            m_buttons[i]->render(window);
        }
    }
}

void HelpState::handleInput(const sf::Event& event)
{
    GameState::handleButtonsInput(event);
}

void HelpState::moveHelpLeft()
{
    if (m_curPage > 0) m_curPage--;
}

void HelpState::moveHelpRight()
{
    if (m_curPage < m_maxNumPages - 1) m_curPage++;
}

void HelpState::updateBackground()
{
    static int mostRecentPage = 0;

    static std::vector<std::string> pages = { "HelpPage1", "HelpPage2", "HelpPage3",
                                               "HelpPage4", "HelpPage5" };

    if (m_curPage != mostRecentPage)
    {
        mostRecentPage = m_curPage;

        m_background.setTexture(ResourcesManager::getInstance().getTexture(pages[m_curPage]));
    }
}

void HelpState::buttonsInit()
{
    m_buttons.clear();
    static std::vector<sf::Vector2f> scales = { {0.05f, 0.1f}, {0.08f, 0.12f}, {0.08f, 0.12f}, };
    static std::vector<sf::Vector2f> positions = { { 0.01f, 0.02f }, { 0.05f, 0.85f }, { 0.95f, 0.85f } };
    static std::vector<std::string> names =
    {
        {"ReturnToMenuButton"},
        {"ArrowButton"},
        {"ArrowButton"}
    };

    std::vector<std::unique_ptr<CommandButton>> commands;
    commands.push_back(std::make_unique<ReturnToMenuCommand>(m_gameManager));
    commands.push_back(std::make_unique<HelpLeftCommand>(m_gameManager));
    commands.push_back(std::make_unique<HelpRightCommand>(m_gameManager));

    for (int i = 0; i < m_numButtons - 1; ++i) {
        ButtonData data(scales[i], positions[i], names[i]);
        m_buttons.push_back(std::make_unique<SimpleButton>(data, std::move(commands[i])));
    }

    m_buttons[right_t]->flipScale();

    createMuteButton();
}
