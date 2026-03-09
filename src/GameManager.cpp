#include "GameManager.h"
#include "GameState.h"
#include "Exceptions.h"

GameManager::StateRequest GameManager::m_nextStateRequest = StateRequest::None;

GameManager::GameManager()
{
    std::srand((unsigned int)std::time(NULL));

	windowInit();
    
    m_controller = std::make_unique<Controller>();
    m_backgroundManager = std::make_unique<BackgroundManager>();
    m_infoBar = std::make_unique<InfoBar>();

    setState(std::make_unique<MainMenuState>(this));
}

void GameManager::run()
{
    sf::Clock clock;
    // Main game loop: runs while the window is open
	while (m_window.isOpen())
	{
        // Handles any pending state change requests
        handleStateRequest();

        sf::Event event;
        // Polls and processes all window events ( input, close)
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) m_window.close();
           
            if (m_state) m_state->handleInput(event);
        }

        float deltaTime = clock.restart().asSeconds();

        m_window.clear();

        // Updates and render the current game state
        if (m_state)
        {
            m_state->update(deltaTime);
            m_state->render();
        }
        
        m_window.display();
    }
}

void GameManager::setState(std::unique_ptr<GameState> state)
{
    if (m_state) m_state->onExit();
	m_state = std::move(state);
    if (m_state) m_state->onEnter();
}

sf::RenderWindow& GameManager::getWindow()
{
	return m_window;
}

void GameManager::update(const float deltaTime)
{
    if (!m_backgroundManager || !m_controller || !m_infoBar) return;

    m_backgroundManager->setScrollSpeedAddition(m_controller->getViewSpeedMultiplier());

    m_backgroundManager->update(deltaTime);

    // creates new object each time (and only this time) one of the walls moves out of view,
    // in order to create objects for  the next frame 
    if (m_backgroundManager->doesNeedToCreateObjects())
    {
        m_controller->createObjects(m_backgroundManager->getScrollOffSet(), deltaTime);
    }

    m_controller->update(m_backgroundManager->getView(), deltaTime);

    m_infoBar->update(m_controller->getDistancePassed(), m_controller->getCoinsAmount());
}

void GameManager::updateWaves()
{
    if (m_backgroundManager) m_backgroundManager->updateWaves();
}

void GameManager::render()
{
    if (!m_backgroundManager || !m_controller || !m_infoBar) return;

    m_window.setView(m_backgroundManager->getView());

    m_backgroundManager->render(m_window);

    m_controller->render(m_window);

    m_window.setView(m_window.getDefaultView());

    m_infoBar->render(m_window);
}

void GameManager::renderWaves()
{
    m_window.setView(m_backgroundManager->getView());
    if (m_backgroundManager) m_backgroundManager->renderWaves(m_window);
}

void GameManager::renderWalls()
{
    m_window.setView(m_backgroundManager->getView());
    if (m_backgroundManager) m_backgroundManager->renderWalls(m_window);
}

void GameManager::handleInput(const sf::Event& event)
{
    if (m_controller) m_controller->handleInput(event);
}

void GameManager::requestState(const StateRequest req)
{
    m_nextStateRequest = req;
}

void GameManager::clearAllButLamps()
{
    if (m_controller) m_controller->clearAllButLamps();
}

void GameManager::revertPlayerToRegularState()
{
    if (m_controller) m_controller->revertPlayerToRegularState();
}

void GameManager::moveHelpLeft()
{
    if (m_state) m_state->moveHelpLeft();
}

void GameManager::moveHelpRight()
{
    if (m_state) m_state->moveHelpRight();
}

void GameManager::mute()
{
    m_isMuted = true;
    if (m_state) m_state->mute();
}

void GameManager::unmute()
{
    m_isMuted = false;
    if (m_state) m_state->unmute();
}

void GameManager::pauseGame()
{
    if (!m_isPaused && m_state)
    {
        saveSoundState();
        m_state->pause();
        m_pausedState = std::move(m_state);
        m_isPaused = true;

        setState(std::make_unique<PauseState>(this));
        m_state->onEnter();
    }
}

// Resumes the game from pause, restoring sound state.
void GameManager::resumeGame()
{
    if (m_isPaused && m_pausedState)
    {
        m_state = std::move(m_pausedState);
        m_isPaused = false;

        restoreSoundState();
    }
}

bool GameManager::isPaused() const
{
    return m_isPaused;
}

void GameManager::renderPausedState()
{
    if (m_isPaused && m_pausedState)
        m_pausedState->render();
}

void GameManager::resetGame()
{
    if (m_controller) m_controller->reset();
    if (m_backgroundManager) m_backgroundManager->reset();

    GameManager::requestState(GameManager::StateRequest::Land);
    
    m_isPaused = false;
    
    m_scoreSaved = false;
}

void GameManager::onEnter()
{
    if (m_controller) m_controller->onEnter();
}

void GameManager::onExit()
{
    if (m_controller) m_controller->onExit();
}

void GameManager::stopPausedStateSounds()
{
	if (m_pausedState) m_pausedState->onExit();
}

void GameManager::mutePausedState()
{
    if (m_pausedState) m_pausedState->mute();
}

void GameManager::unmutePausedState()
{
    if (m_pausedState) m_pausedState->unmute();
}

bool GameManager::isMuted() const
{
    return m_isMuted;
}

void GameManager::quit()
{
	if (m_state) m_state->quit();
}

void GameManager::saveSoundState()
{
    if (m_controller) m_controller->saveSoundState();
}

void GameManager::restoreSoundState()
{
    if (m_controller) m_controller->restoreSoundState();
}

void GameManager::gameOver()
{
    if (m_controller) m_controller->setObjectCreationEnabled(false);

    if (m_backgroundManager) m_backgroundManager->stopViewMovement();

    m_window.setView(m_window.getDefaultView());
}

void GameManager::windowInit()
{
	windowConfig config = WindowUtilities::calculateWindowConfig();

    m_window.create(sf::VideoMode((int)config._windowWidth, (int)config._windowHeight), "Jetpack Joyride by Noya, Revai & Maayan ");

    m_window.setFramerateLimit(25);

    setIcon();

	GraphicUtilities::setWindowSize({ config._windowWidth, config._windowHeight });
}

void GameManager::setIcon()
{
    const sf::Image& icon = ResourcesManager::getInstance().getIconImage();
    
    if (icon.getSize().x > 0 && icon.getSize().y > 0)
        m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    else
        throw ResourceLoadException("Icon image not loaded, window icon not set.");
}

void GameManager::handleStateRequest()
{
    static const std::unordered_map<StateRequest, std::function<void(GameManager*)>> stateHandlers = {
    { StateRequest::Land, [](GameManager* gm) {
        gm->clearAllButLamps();
        gm->setState(std::make_unique<LandGameState>(gm));
        gm->revertPlayerToRegularState();
        GameObjectFactory::setContext(GameObjectFactory::GameContext::Land);
    }},
    { StateRequest::Sea, [](GameManager* gm) {
        gm->clearAllButLamps();
        gm->setState(std::make_unique<SeaGameState>(gm));
        GameObjectFactory::setContext(GameObjectFactory::GameContext::Sea);
    }}, 
     { StateRequest::Help, [](GameManager* gm) {
        gm->setState(std::make_unique<HelpState>(gm));
    }},
    { StateRequest::Menu, [](GameManager* gm) {
        gm->setState(std::make_unique<MainMenuState>(gm));
    }}, 
       { StateRequest::scoreBorad, [](GameManager* gm) {
        gm->setState(std::make_unique<HighScoresState>(gm));
    }},
    { StateRequest::Pause, [](GameManager* gm) {
        gm->pauseGame();
    }},
    { StateRequest::Resume, [](GameManager* gm) {
        gm->resumeGame();
    }},
    { StateRequest::GameOver, [](GameManager* gm) {
       gm->gameOver();
        gm->setState(std::make_unique<GameOverState>(gm));
    }}
    };

    auto it = stateHandlers.find(m_nextStateRequest);
    if (it != stateHandlers.end()) {
        it->second(this);
        m_nextStateRequest = StateRequest::None;
    }
}
