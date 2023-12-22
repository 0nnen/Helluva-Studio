#pragma once

#include "Command.h"

class PauseCommand final : public Command
{
public:
	PauseCommand();
	void Execute(const float& _delta) override;
};