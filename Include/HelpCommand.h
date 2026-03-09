#pragma once
#include "CommandButton.h"

/*
* represent the command of Help Button
*/

class HelpCommand : public CommandButton
{
public:
    using CommandButton::CommandButton;

    void execute() override;
};
