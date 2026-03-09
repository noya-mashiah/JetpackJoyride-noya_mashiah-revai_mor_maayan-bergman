#pragma once
#include "GameState.h"

class GameManager;

/*
* an abstract class represents the command of buttons
*/

class CommandButton {
public:

    CommandButton(GameManager* gameManager) : m_gameManager(gameManager) {}

    virtual ~CommandButton() = default;
    
    virtual void execute() = 0;

protected:

    GameManager* m_gameManager;
};
