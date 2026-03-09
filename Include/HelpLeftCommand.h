#pragma once
#include "CommandButton.h"

/*
* represent the command of moving left on the Help screen
*/

class HelpLeftCommand : public CommandButton
{
public:
    using CommandButton::CommandButton;

    void execute() override;
};
