#include "DecorativeMovingObject.h"

bool DecorativeMovingObject::m_registerIt = GameObjectFactory::registerIt("DecorativeMovingObject",
    [](const GameObjectParams& params) -> std::unique_ptr<GameObject>
    {
        return std::make_unique<DecorativeMovingObject>(params);
    });

DecorativeMovingObject::DecorativeMovingObject(const GameObjectParams& params)
    : MovingObject(params)
{
    updatePictureDirection();
    applyTransparency(params._textureName);
}

GameObjectParams DecorativeMovingObject::getScientistDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("Scientist", { 0.04f, 0.21f }, pos, 3, 0, 2, 0.2f, true);
}

GameObjectParams DecorativeMovingObject::getScientistSeaDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("ScientistSwim", { 0.18f, 0.3f }, pos, 2, 0, 1, 0.4f, true);
}

GameObjectParams DecorativeMovingObject::getFishDefaultParams(const sf::Vector2f& pos)
{
    return GameObjectParams("Fish1", { 0.1f, 0.12f }, pos, 3, 0, 2, 0.2f, true);
}


 // Applies transparency effect to certain decorative objects
 // textureName The name of the texture to check for transparency
void DecorativeMovingObject::applyTransparency(const std::string& textureName)
{
    if (textureName == "Scientist" || textureName == "ScientistSwim") return;

    sf::Color semiTransparent(255, 255, 255, 160);
    m_sprite.setColor(semiTransparent);
}

void DecorativeMovingObject::updatePictureDirection()
{
    // Set random speed 
    m_speed = (float)(std::rand() % 250 + 100);

    // Determine direction based on X position (odd/even check)
    if ((int)m_sprite.getPosition().x % 2 != 0)
    {
        // Face right and flip sprite horizontally
        m_isFacingRight = true;
        sf::Vector2f scale = m_sprite.getScale();
        m_sprite.setScale(-scale.x, scale.y);
    }
    else m_speed = -m_speed; // Face left
}

void DecorativeMovingObject::move(const sf::View& view, const float deltaTime)
{
    (void)view;
    float posX = m_sprite.getPosition().x + m_speed * deltaTime;
    float posY = m_sprite.getPosition().y;
    m_sprite.setPosition(posX, posY);
}
