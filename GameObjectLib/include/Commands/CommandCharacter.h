#pragma once

#include "Command.h"
#include "Components/Inputs/InputCharacter.h"
#include "Component.h"

class InputPlayer;

class MouveCharacterRight : public Command
{
public:
	MouveCharacterRight();
	void Execute(const float& _delta);
};

class MouveCharacterLeft : public Command
{
public:
	MouveCharacterLeft();
	void Execute(const float& _delta);
};

class JumpCharacter : public Command
{
public:
	JumpCharacter();
	void Execute(const float& _delta);
};


