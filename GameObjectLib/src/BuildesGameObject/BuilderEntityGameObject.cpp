#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/SceneManager.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody2D.h"
#include "Components/Entity/Character.h"
#include "Components/Inputs/InputCharacter.h"
#include <Components/Shapes/Rectangle.h>
#include <Components/Shapes/Triangle.h>

GameObject* BuilderEntityGameObject::CreateBulletGameObject(const std::string& _name,sf::Texture* _textureBullet, const float& _scalex, const float& _scaley, GameObject* _player)
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


	Character* character = gameObject->CreateComponent<Character>();

	//Armes* arme = gameObject->CreateComponent<Armes>();
	//arme->SetDamage(player->GetDamage());

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(texture);
	sprite->SetScale();
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

GameObject* BuilderEntityGameObject::CreatePlatformCollisionGameObject(const std::string& _name, const float& _positionX, const float& _positionY, const float& _scalex, const float& _scaley)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_positionX, _positionY));
	gameObject->SetScale(Maths::Vector2f(_scalex, _scaley));


	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);

	Rectangle* rectangle = gameObject->CreateComponent<Rectangle>();
	rectangle->SetSize(200.f, 50.f);
	rectangle->SetScale(_scalex, _scaley);

	return gameObject;

}

GameObject* BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject(const std::string& _name, const float& _base, const float& _height, const float& _widthPos, const float& _heightPos, const float& _rotation)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);


	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);

	Triangle* triangle = gameObject->CreateComponent<Triangle>();
	triangle->SetBase(_base);
	triangle->SetHeight(_height);
	triangle->SetPositionTriangle(_widthPos, _heightPos, _rotation);

	return gameObject;

}