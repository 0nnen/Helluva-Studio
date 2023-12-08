#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/SceneManager.h"
#include "Managers/AssetManager.h"
#include "Components/SpriteRenderer.h"
#include "Components/Animation.h"
#include "Components/RigidBody2D.h"
#include "Components/Entity/Character.h"
#include "Components/Inputs/InputCharacter.h"
#include "Components/Shapes/Rectangle.h"

GameObject* BuilderEntityGameObject::CreateBulletGameObject(const std::string& _name, sf::Texture* _textureBullet, const float& _scalex, const float& _scaley, GameObject* _player)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_player->GetPosition().GetX(), _player->GetPosition().GetY()));

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_textureBullet);
	sprite->SetSprite();

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	rigidBody2D->SetScale(0.5, 0.5);

	return gameObject;

}

GameObject* BuilderEntityGameObject::CreateCharacterGameObject(const std::string& _name, const float& _x, const float& _y, sf::Texture* texture, const float& scalex, const float& scaley)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetDepth(1.f);
	gameObject->SetScale(Maths::Vector2f(scalex, scaley));

	Character* character = gameObject->CreateComponent<Character>();

	//Armes* arme = gameObject->CreateComponent<Armes>();
	//arme->SetDamage(player->GetDamage());

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale(scalex, scaley);
	sprite->SetSprite();

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(true);
	rigidBody2D->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	rigidBody2D->SetScale(scalex, scaley);
	
	Animation* idle = gameObject->CreateComponent<Animation>();
	Animation* jump = gameObject->CreateComponent<Animation>();
	Animation* run = gameObject->CreateComponent<Animation>();
	idle->SetLoop(-1);
	jump->SetLoop(-1);
	run->SetLoop(-1);
	idle->SetName("idle");
	jump->SetName("jump");
	run->SetName("run");
	idle->SetFrame(10);
	jump->SetFrame(3);
	run->SetFrame(8);
	idle->SetAnimationTime(1);
	jump->SetAnimationTime(1);
	run->SetAnimationTime(1);
	idle->SetSpriteSheet(AssetManager::GetAsset("idleCharacter"));
	jump->SetSpriteSheet(AssetManager::GetAsset("jumpCharacter"));
	run->SetSpriteSheet(AssetManager::GetAsset("runCharacter"));
	idle->Play();

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

GameObject* BuilderEntityGameObject::CreatePlateformGameObject(const std::string& _name, const float& _positionX, const float& _positionY, const float& _scalex, const float& _scaley)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_positionX, _positionY));
	gameObject->SetScale(Maths::Vector2f(_scalex, _scaley));


	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->SetSize(200.f, 50.f);
	rigidBody2D->SetScale(_scalex, _scaley);

	Rectangle* rectangle = gameObject->CreateComponent<Rectangle>();
	rectangle->SetSize(200.f, 50.f);
	rectangle->SetScale(_scalex, _scaley);

	return gameObject;

}