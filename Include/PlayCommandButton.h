#pragma once
#include "CommandButton.h"
#include "LandGameState.h"

/*
* represent the command of the "play" button
*/

class PlayCommandButton : public CommandButton {
public:
    using CommandButton::CommandButton;

    void execute() override;
};
