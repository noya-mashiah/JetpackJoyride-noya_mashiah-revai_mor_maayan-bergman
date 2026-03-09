#pragma once
#include "BaseButton.h"
#include <memory>

/*
* represents a toggle button
*/

class ToggleButton : public BaseButton {
public:
    ToggleButton(const ButtonData& data,std::unique_ptr<CommandButton> commandOff,
        std::unique_ptr<CommandButton> commandOn, bool startOn = false);

    void executeClick() override;

    virtual void update(const sf::RenderWindow& window) override { (void)window; };
    
private:
    void updateTexture();
    
    std::unique_ptr<CommandButton> m_commandOff;
    bool m_isOn;
    std::string m_offTextureName, m_onTextureName;
};
