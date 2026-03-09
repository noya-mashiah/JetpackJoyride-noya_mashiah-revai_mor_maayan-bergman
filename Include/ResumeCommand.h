#pragma once
#include "CommandButton.h"

/*
* represent the command of the "resume" button
*/

class ResumeCommand : public CommandButton
{
public:
    using CommandButton::CommandButton;

    void execute() override;
};
