#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/SceneManager.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody2D.h"
#include "Components/Entity/Character.h"
#include "Components/Inputs/InputCharacter.h"

GameObject* BuilderEntityGameObject::CreateBulletGameObject(const std::string& _name, const sf::Texture& _textureBullet, const float& _scalex, const float& _scaley, GameObject* _player)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_player->GetPosition().GetX(), _player->GetPosition().GetY()));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_textureBullet);
	sprite->SetScale(_scalex, _scaley);
	sprite->SetSprite();

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	rigidBody2D->SetScale(0.5, 0.5);

	return gameObject;

}

GameObject* BuilderEntityGameObject::CreateCharacterGameObject(const std::string& _name, float _x, float _y, const sf::Texture texture, float scalex, float scaley)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));


	Character* character = gameObject->CreateComponent<Character>();

	//Armes* arme = gameObject->CreateComponent<Armes>();
	//arme->SetDamage(player->GetDamage());

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	rigidBody2D->SetScale(scalex, scaley);

	InputCharacter* inputCharacter = gameObject->CreateComponent<InputCharacter>();

	/*HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(player->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(player->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(sprite->GetBounds().y / 2 + 50.f);
	healthPointBar->SetSize(sprite->GetBounds().x, 5);
	healthPointBar->SetScale(scalex, scaley);
	healthPointBar->SetHealthPointBar();*/

	return gameObject;
}