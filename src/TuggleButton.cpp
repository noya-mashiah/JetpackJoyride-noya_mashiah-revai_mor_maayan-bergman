#include "TuggleButton.h"

ToggleButton::ToggleButton(const ButtonData& data,
    std::unique_ptr<CommandButton> commandOff, 
    std::unique_ptr<CommandButton> commandOn, bool startOn)
    : BaseButton(data,std::move(commandOn)),
    m_commandOff(std::move(commandOff)),
    m_isOn(startOn),
    m_offTextureName(data._offTextureName),
    m_onTextureName(data._onTextureName)
{
    updateTexture();
}

void ToggleButton::executeClick()
{
    if (m_click)
    {
        m_sound.play();
        m_click = false;

        m_isOn = !m_isOn;
        if (m_isOn)
            m_command->execute();
        else
            m_commandOff->execute();
        updateTexture();
    }
}

void ToggleButton::updateTexture()
{
    m_sprite.setTexture(ResourcesManager::getInstance().getTexture(
        m_isOn ? m_onTextureName : m_offTextureName));
}
