#pragma once

#include "Command.h"
#include "Components/Inputs/InputCharacter.h"
#include "Component.h"

class InputPlayer;

class MoveCharacterRight : public Command
{
public:
	MoveCharacterRight();
	void Execute(const float& _delta);
};

class MoveCharacterLeft : public Command
{
public:
	MoveCharacterLeft();
	void Execute(const float& _delta);
};

class JumpCharacter : public Command
{
public:
	JumpCharacter();
	void Execute(const float& _delta);
};

class ShootCharacter : public Command
{
public:
	ShootCharacter();
	void Execute(const float& _delta);
};



