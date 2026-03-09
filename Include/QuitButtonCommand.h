#pragma once
#include "CommandButton.h"

/*
* represent the command of the "quit" button
*/

class QuitButtonCommand : public CommandButton
{
public:
    
    using CommandButton::CommandButton;

    void execute() override;
};
