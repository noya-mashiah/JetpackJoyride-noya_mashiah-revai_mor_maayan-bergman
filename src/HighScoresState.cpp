#include "HighScoresState.h"
#include "GameManager.h"
#include "SimpleButton.h"
#include "HoverButton.h"
#include "TuggleButton.h"
#include "ResourcesManager.h"
#include <vector>
#include <memory>

HighScoresState::HighScoresState(GameManager* gameManager)
    : GameState(gameManager, "ScoreBoardMusic")
{
    backgroundInit(m_background, "GameMenu");
    buttonsInit();
    m_topScores = HighScoresManager::getInstance().getTopScores(m_numHighestScores);
    initScoreTexts();
    berryInit();
}

void HighScoresState::update(float) 
{
    sf::Vector2f pos = (HighScoresManager::getInstance().hasScores()) ? m_berryScoresPos : m_berryNoScoresPos;

    m_berry.setPosition(pos);
}

void HighScoresState::render() const
// Renders the high scores background, texts, berry, and buttons.
{
    if (m_gameManager)
    {
        auto& window = m_gameManager->getWindow();
        window.setView(window.getDefaultView());
        window.draw(m_background);
        GameState::renderButtons();

        if (HighScoresManager::getInstance().hasScores())
        {
            for (const auto& text : m_scoreTexts)
                window.draw(text);

            window.draw(m_yourScoreText);
        }
        else
            window.draw(m_noScoresText);

        window.draw(m_berry);
    }
}

void HighScoresState::handleInput(const sf::Event& event)
{
    GameState::handleButtonsInput(event);
}

void HighScoresState::buttonsInit()
{
    m_buttons.clear();

    m_buttons.push_back(std::make_unique<SimpleButton>(
        ButtonData({ 0.07f, 0.13f }, { 0.02f, 0.04f }, "ReturnToMenuButton"),
        std::make_unique<ReturnToMenuCommand>(m_gameManager)
    ));

    createMuteButton();
}

void HighScoresState::initScoreTexts()
// Initializes the score texts for the high scores screen.
{
    m_scoreTexts.clear();

    static std::vector<std::string> scoreTitles = {
        "Champion of the Skies : ",
        "Almost a Legend       : ",
        "Brave Runner          : ",
        "Made the List         : ",
        "One to Watch          : "
    };

    static std::vector<float> yOffSets = { 0.2f, 0.28f, 0.36f, 0.44f, 0.52f };

    // High scores
    for (size_t i = 0; i < m_topScores.size(); ++i) {
        int displayScore = m_topScores[i] / 100;
        std::string str = std::to_string(i + 1) + ". " + scoreTitles[i] + std::to_string(displayScore) + "M";
        m_scoreTexts.push_back(
            GraphicUtilities::createNormalizedText(str, yOffSets[i], 0.25f)
        );
    }

    // "No scores yet" message
    m_noScoresText = GraphicUtilities::createNormalizedText(
        "No brave soul has conquered this game... yet!\n      The hall of fame awaits its first hero!",
        0.2f, 0.16f, 0.035f, sf::Color::White
    );

    // "Your Score" message
    int currentScore = HighScoresManager::getInstance().getCurrentScore();
    m_yourScoreText = GraphicUtilities::createNormalizedText(
        "Your Score: " + std::to_string(currentScore / 100) + "M",
        0.72f, 0.34f, 0.035f, sf::Color::Yellow
    );
}

void HighScoresState::berryInit()
// Initializes the berry sprite and its positions.
{
    m_berry.setTexture(ResourcesManager::getInstance().getTexture("KingBarry"));
    sf::Vector2f windowSize = GraphicUtilities::getWindowSize();

    m_berryNoScoresPos = { 0.4f * windowSize.x, 0.45f * windowSize.y };
    m_berryScoresPos = { 0.76f * windowSize.x, 0.45f * windowSize.y };
    m_berry.setPosition(m_berryNoScoresPos);
    sf::Vector2f scale = GraphicUtilities::getGameObjectScale({ 0.2f, 0.5 }, m_berry.getTextureRect());
    m_berry.setScale(scale);
}
