#include "Commands/CommandsGame.h"
#include "Managers/SceneManager.h"
#include "Managers/CameraManager.h"

PauseCommand::PauseCommand() {}

void PauseCommand::Execute(const float& _delta)
{
	SceneManager::GetActiveGameScene()->SetIsActive(!SceneManager::GetActiveGameScene()->GetIsActive());
}