#pragma once
#include "PlayerState.h"
#include "Shell.h"

/*
* represent a special given state - surfer
*/

class SurferPlayerState : public PlayerState
{
public:
    SurferPlayerState() = default;

    SurferPlayerState(sf::Sprite& sprite, Animation& animation);

    virtual void handleInput(const sf::Event& event) override;

    virtual void update(const sf::View& view, const float deltaTime) override;

    virtual void render(sf::RenderWindow& window) const override;

    virtual void move(const sf::View& view, const float deltaTime) override;

    static GameObjectParams getDefaultValues();

     std::unique_ptr<Pickables> addGift(const sf::Vector2f& scrollOffset) override;

     void processHit(Player& player) override;

     virtual void onShellCollected() override;

     virtual void saveSoundState() override;

     virtual void restoreSoundState() override;

private:

    void init();

    void updateAnimationParams(int& firstFrame, int& lastFrame, bool& shouldLoop) const;

    void checkIfAnimationUpdateRequired();

    void initializeBubbles();

    bool isUnderWater() const;

    // members to track current animation parameters to avoid redundant setAnimation calls
    int m_currentFirstFrame = -1;
    int m_currentLastFrame = -1;
    bool m_currentShouldLoop = false;

    std::vector<std::unique_ptr<SwirlItem>> m_bubbles;
};
