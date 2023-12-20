#include "Components/ComponentsGame/Weapon.h"
#include "Managers/SceneManager.h"
#include "Components/Entity/Character.h"

void Weapon::Update(const float& _delta)
{
	Component::Update(_delta);
}

void Weapon::Attack() {
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	Character* character = player->GetComponent<Character>();
	if (!underCooldown)
	{
		if (!character->GetAnimation("shootArm")->GetIsPlaying() && !character->GetAnimation("shootBody")->GetIsPlaying()) {
			if (character->GetAnimation("idle")->GetIsPlaying()) character->GetAnimation("idle")->Stop();
			if (character->GetAnimation("run")->GetIsPlaying()) character->GetAnimation("run")->Stop();
			if (character->GetAnimation("jump")->GetIsPlaying()) character->GetAnimation("jump")->Stop();
			character->GetAnimation("shootBody")->Play();
			const std::string nameArm = "arm";
			character->GetAnimation("shootArm")->Play(nameArm);
		}
	}
	else
	{
		if (character->GetAnimation("shootBody")->GetIsPlaying()) character->GetAndSetAnimation("shootBody")->Stop();
		if (character->GetAnimation("shootArm")->GetIsPlaying()) character->GetAndSetAnimation("shootArm")->Stop();
		if (!character->GetAnimation("run")->GetIsPlaying())
		{
			if (!character->GetAnimation("idle")->GetIsPlaying()) {
				character->GetAndSetAnimation("idle")->Play();
			}
		}
	}
}