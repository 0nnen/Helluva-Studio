#pragma once

#include "Command.h"
#include "Components/Inputs/InputCharacter.h"

class MoveCharacterRight final: public Command
{
public:
	MoveCharacterRight();
	void Execute(const float& _delta) override;
};

class MoveCharacterLeft final : public Command
{
public:
	MoveCharacterLeft();
	void Execute(const float& _delta) override;
};

class JumpCharacter final : public Command
{
public:
	JumpCharacter();
	void Execute(const float& _delta) override;
};

class ShootCharacter final : public Command
{
public:
	ShootCharacter();
	void Execute(const float& _delta) override;
};

class ChangeWeaponCharacter final : public Command
{
public:
	ChangeWeaponCharacter(const int& _numberWeapon);
	void Execute(const float& _delta) override;
private:
	int numberWeapon = 0;
};

