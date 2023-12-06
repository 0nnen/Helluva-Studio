#include "Commands/CommandCharacter.h"
#include "BuilderGameObject.h"
#include "Components/Entity/Character.h"
#include "Managers/SceneManager.h"


void MouveCharacterRight::Execute(const float& _delta) 
{
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	Character* character = player->GetComponent<Character>();
	player->SetPosition(player->GetPosition() + Maths::Vector2f::Right + Maths::Vector2f(25, 0) * _delta * character->GetSpeed());
	character->setDirection(Character::Direction::Right);
}
MouveCharacterRight::MouveCharacterRight(){}

void MouveCharacterLeft::Execute(const float& _delta)
{

	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	Character* character = player->GetComponent<Character>();
	player->SetPosition(player->GetPosition() + Maths::Vector2f::Left + Maths::Vector2f(25, 0) * _delta * character->GetSpeed());
	character->setDirection(Character::Direction::Left);
}
MouveCharacterLeft::MouveCharacterLeft() {}

