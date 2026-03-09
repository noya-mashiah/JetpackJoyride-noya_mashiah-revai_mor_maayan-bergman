/**
 *  BirdPlayerState.h
 *  Defines the Bird player state (flying, coin eating, sparkles).
 *
 * The BirdPlayerState class implements the player's behavior when in bird mode,
 * including flying, special coin collection, and visual effects like sparkles and dollar bills.
 * Inherits from PlayerState and manages multiple effect clusters.
 */
#pragma once
#include "PlayerState.h"

class BirdPlayerState : public PlayerState
{
public:
    BirdPlayerState() = default;

	BirdPlayerState(sf::Sprite& sprite, Animation& animation);

    virtual void handleInput(const sf::Event& event) override;

    virtual void update(const sf::View& view, const float deltaTime) override;

    virtual void render(sf::RenderWindow& window) const  override;

    virtual void move(const sf::View& view, const float deltaTime) override;

    virtual void onCoinCollected(int& coinCounter) override;

    static GameObjectParams getDefaultValues();

private:

    void initializeGroundSparkles();

    void initializeEatingSparkles();

    void initializeDollarBills();

    bool isOnGround() const;

    void init();

    void soundInit();

    virtual void onLandingComplete() override;

    void playFly();

    void playSlide();

    // Template functions to eliminate code duplication
    template<typename TContainer>
    void updateIf(const TContainer& sparkles, bool condition,
                          const sf::View& view, const float deltaTime);

    template<typename TContainer>
    void renderIf(const TContainer& sparkles, bool condition,
                          sf::RenderWindow& window) const;

    std::vector<std::unique_ptr<PlayerEffect>> m_groundSparkles;

    std::vector<std::unique_ptr<PlayerEffect>> m_eatingSparkles;

    std::vector<std::unique_ptr<SwirlItem>> m_dollarBills;

    bool m_isEatingCoin = false;

    sf::Sound m_landingSound;

    sf::Sound m_yippySound;

    // --- class consts -----
    inline static constexpr float FlyCommandGravity = 1200.f;
    inline static constexpr float FlyCommandjumpForce = -400.f;
    inline static constexpr int CoinValue = 2;
    inline static const sf::Vector2f DefaultBirdVelocity = { 1.f, 0.f };
    inline static constexpr float GroundSparkleYOffsetRatio = 0.25f;
    inline static constexpr int NumGroundSparkels = 7;
    inline static constexpr int NumEatingSparkels = 10;

    // flying animation
    inline static const std::string TextureName = "BirdFlying";
    inline static const sf::Vector2f WindowScaleFly = { 0.07f ,0.17f };
    inline static constexpr int FrameCount = 6;
    inline static constexpr int StartFrameFly = 0;
    inline static constexpr int EndFrame = 3;
    inline static constexpr float FrameTimeFly= 0.1f;
    inline static constexpr bool Loop = true;
    inline static const sf::Vector2f DefaultVelocity = { 0.f, 0.f };

    // not flying animation
    inline static const sf::Vector2f WindowScaleGround = { 0.10f ,0.17f };
    inline static constexpr int StartAndEndFrameGround = 1;
    inline static constexpr float FrameTimeGround = 0.f;
    inline static constexpr bool NoLoop = false;

    // collect coin animation
    inline static constexpr int StartFrameEatCoin = 4;
    inline static constexpr int EndFrameEatCoin = 5;
    inline static constexpr float FrameTimeEatCoin = 0.3f;
};

// Template function implementations
template<typename TContainer>
void BirdPlayerState::updateIf(const TContainer& sparkles, bool condition,
                                       const sf::View& view, const float deltaTime)
{
    if (condition)
        for (auto& s : sparkles)
            s->update(view, deltaTime);
}

template<typename TContainer>
void BirdPlayerState::renderIf(const TContainer& sparkles, bool condition,
                                        sf::RenderWindow& window) const
{
    if (condition)
        for (const auto& s : sparkles)
            s->render(window);
}
