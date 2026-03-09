#pragma once
#include "CommandButton.h"

/*
* represent the command of muting
*/

class MuteCommand : public CommandButton
{
public:

    using CommandButton::CommandButton;

    void execute() override;
};
