#pragma once
#include "CommandButton.h"

/*
* represent the command of moving right on the Help screen
*/

class HelpRightCommand : public CommandButton
{
public:
    using CommandButton::CommandButton;

    void execute() override;
};
