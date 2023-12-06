#pragma once

#include "Command.h"

class PauseCommand final : public Command
{
public:
	PauseCommand();
	void Execute(const float& _delta) override;
};


class ZoomCommand final : public Command
{
public:
	ZoomCommand();
	void Execute(const float& _delta) override;
};


class DezoomCommand final : public Command
{
public:
	DezoomCommand();
	void Execute(const float& _delta) override;
};

class LeftCommand final : public Command
{
public:
	LeftCommand();
	void Execute(const float& _delta) override;
};


class RightCommand final : public Command
{
public:
	RightCommand();
	void Execute(const float& _delta) override;
};


class UpCommand final : public Command
{
public:
	UpCommand();
	void Execute(const float& _delta) override;
};

class DownCommand final : public Command
{
public:
	DownCommand();
	void Execute(const float& _delta) override;
};