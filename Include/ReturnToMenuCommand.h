#pragma once
#include "CommandButton.h"

/*
* represent the command of the return to menu button
*/

class ReturnToMenuCommand : public CommandButton
{
public:
    using CommandButton::CommandButton;

    void execute() override;
};
