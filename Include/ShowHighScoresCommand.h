#pragma once
#include "CommandButton.h"

/*
* represent the command of the show high score button
*/

class ShowHighScoresCommand : public CommandButton
{
public:
    using CommandButton::CommandButton;

    void execute() override;
};
