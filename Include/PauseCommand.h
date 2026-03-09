#pragma once
#include "CommandButton.h"

/*
* represent the command of pausing
*/

class PauseCommand : public CommandButton
{
public:
    using CommandButton::CommandButton;
    void execute() override;
};
