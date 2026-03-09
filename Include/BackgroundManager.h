#pragma once
#include <vector>
#include "HallAnimation.h"

/*
* Manages the animated scrolling background, waves, and decorative elements
*/

class BackgroundManager
{
public:
    BackgroundManager();

    void update(const float deltaTime);

    void render(sf::RenderWindow& window) const;

    void renderWaves(sf::RenderWindow& window) const;

    void renderWalls(sf::RenderWindow& window) const;

    const sf::View& getView() const;

    bool doesNeedToCreateObjects() const;

    sf::Vector2f getScrollOffSet() const;

    void setScrollSpeedAddition(const float scrollSpeedAddition);

    void updateWaves();

    void reset();

    void stopViewMovement();

private:

    void moveBackground();

    void moveWaves();

    void backgroundInit();

    void setBackground(sf::Sprite& background, const float xOffSet);

    void WavesInit();

    void checkIfBackgroundMoved(sf::Sprite& backgroundA, sf::Sprite& backgroundB);

    bool m_needToCreateObjects = false; // to know when the backgrounds moved to 
                                        // create objects in next frame

    sf::Vector2f m_offSet = { 0.f, 0.f };

    HallAnimation m_hallAnimation;

    sf::Sprite m_background1;

    sf::Sprite m_background2;

    std::vector<sf::Sprite> m_waves;

    sf::View m_view;

    float m_scrollSpeed = 400.f;

    float m_scrollSpeedAddition = 1.f;

    bool m_viewMovementStopped = false;
};
