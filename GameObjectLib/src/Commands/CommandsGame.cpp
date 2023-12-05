#include "Commands/CommandsGame.h"
#include "Managers/SceneManager.h"
#include "Managers/CameraManager.h"

PauseCommand::PauseCommand() {}

void PauseCommand::Execute(const float& _delta)
{
	SceneManager::GetActiveGameScene()->SetIsActive(!SceneManager::GetActiveGameScene()->GetIsActive());
}

ZoomCommand::ZoomCommand() {}

void ZoomCommand::Execute(const float& _delta)
{
	CameraManager::Zoom(0.95f);
}

DezoomCommand::DezoomCommand() {}

void DezoomCommand::Execute(const float& _delta)
{
	CameraManager::Zoom(1.05f);
}


LeftCommand::LeftCommand() {}

void LeftCommand::Execute(const float& _delta)
{
	CameraManager::Move(-500.f * _delta, 0);
}

RightCommand::RightCommand() {}

void RightCommand::Execute(const float& _delta)
{
	CameraManager::Move(500.f * _delta, 0);
}


UpCommand::UpCommand() {}

void UpCommand::Execute(const float& _delta)
{
	CameraManager::Move(0.f,-500.f * _delta);
}

DownCommand::DownCommand() {}

void DownCommand::Execute(const float& _delta)
{
	CameraManager::Move(0.f, +500.f * _delta);
}
