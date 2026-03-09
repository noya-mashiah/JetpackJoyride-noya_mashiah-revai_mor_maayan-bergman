#pragma once
#include "CommandButton.h"

/*
* represent the command of the unmute button
*/

class UnmuteCommand : public CommandButton
{
public:

    using CommandButton::CommandButton;

    void execute() override;
};
