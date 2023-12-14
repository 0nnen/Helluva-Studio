#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/SceneManager.h"
#include "Managers/AssetManager.h"
#include "Components/SpriteRenderer.h"
#include "Components/Animation.h"
#include "Components/RigidBody2D.h"
#include "Components/ComponentsGame/WeaponsContainer.h"
#include "Components/ComponentsGame/Bullet.h"
#include "Components/ComponentsGame/Sword.h"
#include "Components/ComponentsGame/Gun.h"
#include "Components/Entity/Character.h"
#include "Components/Inputs/InputCharacter.h"
#include "Components/Entity/Enemy/EnemyA.h"
#include "Components/Entity/Enemy/Hades.h"

#include <Components/Shapes/Rectangle.h>
#include <Components/Shapes/Triangle.h>
#include "Components/Transform.h"



GameObject* BuilderEntityGameObject::CreateBulletGameObject(const std::string& _name, sf::Texture* _textureBullet, GameObject* _player, const float& _scalex, const float& _scaley, const float& _damage, const float& _speed, const Maths::Vector2f& _direction, const float& _rotate, const Maths::Vector2f& _position)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(_position);
	gameObject->SetRotation(_rotate);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_textureBullet);
	sprite->SetSprite();

	Bullet* bullet = gameObject->CreateComponent<Bullet>();
	bullet->SetSpeed(_speed);

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->AddForces(_direction * bullet->GetSpeed());

	gameObject->SetPosition(Maths::Vector2f(_player->GetPosition().GetX(), _player->GetPosition().GetY()) + gameObject->GetTransform()->TransformPoint());

	bullet->SetDamage(_damage);
	bullet->SetInitialPosition(gameObject->GetPosition());

	return gameObject;
}

GameObject* BuilderEntityGameObject::CreateCharacterGameObject(const std::string& _name, const float& _x, const float& _y, sf::Texture* texture, const float& scalex, const float& scaley)
{
	GameObject* gameObject = SceneManager::GetActiveScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetDepth(0.9f);
	gameObject->SetScale(Maths::Vector2f(scalex, scaley));

	Character* character = gameObject->CreateComponent<Character>();

	Sprite* spriteBody = gameObject->CreateComponent<Sprite>();
	spriteBody->SetName("body");
	spriteBody->SetTexture(texture);
	spriteBody->SetScale(scalex, scaley);
	spriteBody->SetSprite();

	Sprite* spriteArm = gameObject->CreateComponent<Sprite>();
	spriteArm->SetName("arm");
	spriteArm->SetTexture(texture);
	spriteArm->SetScale(scalex, scaley);
	spriteArm->SetSprite();
	spriteArm->SetActiveAndVisible(false);

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(true);
	rigidBody2D->SetSize(spriteBody->GetBounds().x, spriteBody->GetBounds().y);
	rigidBody2D->SetKillImperfection(Maths::Vector2f(8.f, 8.f));
	rigidBody2D->SetScale(scalex, scaley);

	Animation* idle = gameObject->CreateComponent<Animation>();
	idle->SetLoop(-1);
	idle->SetName("idle");
	idle->SetFrame(10);
	idle->SetAnimationTime(1);
	idle->SetSpriteSheet(AssetManager::GetAsset("idleCharacter"));

	Animation* jump = gameObject->CreateComponent<Animation>();
	jump->SetLoop(-1);
	jump->SetName("jump");
	jump->SetFrame(3);
	jump->SetAnimationTime(1);
	jump->SetSpriteSheet(AssetManager::GetAsset("jumpCharacter"));

	Animation* run = gameObject->CreateComponent<Animation>();
	run->SetLoop(-1);
	run->SetName("run");
	run->SetFrame(8);
	run->SetAnimationTime(1);
	run->SetSpriteSheet(AssetManager::GetAsset("runCharacter"));

	Animation* shootBody = gameObject->CreateComponent<Animation>();
	shootBody->SetLoop(1);
	shootBody->SetName("shootBody");
	shootBody->SetFrame(10);
	shootBody->SetAnimationTime(0.2f);
	shootBody->SetSpriteSheet(AssetManager::GetAsset("shootBody"));

	Animation* shootArm = gameObject->CreateComponent<Animation>();
	shootArm->SetLoop(1);
	shootArm->SetName("shootArm");
	shootArm->SetFrame(10);
	shootArm->SetAnimationTime(0.2f);
	shootArm->SetSpriteSheet(AssetManager::GetAsset("shootArm"));

	idle->Play();

	character->AddAnimation("idle", idle);
	character->AddAnimation("jump", jump);
	character->AddAnimation("run", run);
	character->AddAnimation("shootBody", shootBody);
	character->AddAnimation("shootArm", shootArm);

	InputCharacter* inputCharacter = gameObject->CreateComponent<InputCharacter>();

	WeaponsContainer* weaponsContainer = gameObject->CreateComponent<WeaponsContainer>();
	weaponsContainer->AddNewWeapon(BuilderEntityGameObject::CreateWeaponGameObject(std::string("Gun"), gameObject, Weapon::TypeWeapon::Gun, _x, _y, 25.f, 100.f, 0.02f));
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
GameObject* BuilderEntityGameObject::CreateWeaponGameObject(const std::string& _name, GameObject* _player, const Weapon::TypeWeapon& _typeWeapon, const float& _positionX, const float& _positionY, const float& _damage, const float& _range, const float& _attackSpeed)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_positionX, _positionY));

	//RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	//rigidBody2D->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	//rigidBody2D->SetScale(0.5, 0.5);

	WeaponsContainer* weaponsContainer = _player->GetComponent<WeaponsContainer>();
	weaponsContainer->AddNewWeapon(gameObject);

	Weapon* weapon;
	if (_typeWeapon == Weapon::TypeWeapon::Gun) weapon = gameObject->CreateComponent<Gun>();
	else if (_typeWeapon == Weapon::TypeWeapon::Sword) weapon = gameObject->CreateComponent<Sword>();
	else weapon = gameObject->CreateComponent<Weapon>();
	weapon->SetName(_name);
	weapon->SetAttackSpeed(_attackSpeed);
	weapon->SetDamage(_damage);
	weapon->SetRange(_range);
	weapon->SetIndexWeapon(weaponsContainer->GetIndexActualWeapon());

	return gameObject;
}


GameObject* BuilderEntityGameObject::CreatePlatformTriangleCollisionGameObject(const std::string& _name, const float& _base, const float& _height, const float& _widthPos, const float& _heightPos, const float& _rotation)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);

	Triangle* triangle = gameObject->CreateComponent<Triangle>();
	triangle->SetBase(_base);
	triangle->SetHeight(_height);
	triangle->SetPositionTriangle(_widthPos, _heightPos, _rotation);

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

GameObject* BuilderEntityGameObject::CreateEnemyAGameObject(const std::string& _name, float _x, float _y, float scalex, float scaley, sf::Texture* _texture)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetDepth(0.9f);

	EnemyA* enemy = gameObject->CreateComponent<EnemyA>();

	Sprite* spriteBody = gameObject->CreateComponent<Sprite>();
	spriteBody->SetName("bodyEnemyA");
	spriteBody->SetTexture(_texture);
	spriteBody->SetScale(scalex, scaley);
	spriteBody->SetSprite();

	Animation* idle = gameObject->CreateComponent<Animation>();
	idle->SetLoop(-1);
	idle->SetName("idle");
	idle->SetFrame(6);
	idle->SetAnimationTime(1);
	idle->SetSpriteSheet(AssetManager::GetAsset("idleEnemyA"));

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(true);
	rigidBody2D->SetSize(spriteBody->GetBounds().x, spriteBody->GetBounds().y);
	rigidBody2D->SetScale(scalex, scaley);


	idle->Play();

	enemy->AddAnimation("idle", idle);



	/*HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(enemy->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(enemy->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(25);
	healthPointBar->SetSize(25, 2);
	healthPointBar->SetScale(2.f, 2.f);
	healthPointBar->SetHealthPointBar();*/
	//enemies.push_back(gameObject);

	return gameObject;
}


GameObject* BuilderEntityGameObject::CreateHadesGameObject(const std::string& _name, float _x, float _y, float scalex, float scaley, sf::Texture* _texture)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetDepth(0.9f);

	Hades* enemy = gameObject->CreateComponent<Hades>();
	enemy->SetInvicible(false);

	Sprite* spriteBody = gameObject->CreateComponent<Sprite>();
	spriteBody->SetName("bodyEnemyA");
	spriteBody->SetTexture(_texture);
	spriteBody->SetScale(scalex, scaley);
	spriteBody->SetSprite();

	Animation* idle = gameObject->CreateComponent<Animation>();
	idle->SetLoop(-1);
	idle->SetName("idle");
	idle->SetFrame(6);
	idle->SetAnimationTime(1);
	idle->SetSpriteSheet(AssetManager::GetAsset("idleHades"));

	Animation* attack = gameObject->CreateComponent<Animation>();
	attack->SetLoop(1);
	attack->SetName("attack");
	attack->SetFrame(6);
	attack->SetAnimationTime(2);
	attack->SetSpriteSheet(AssetManager::GetAsset("attackHades"));

	Animation* roar = gameObject->CreateComponent<Animation>();
	roar->SetLoop(1);
	roar->SetName("roar");
	roar->SetFrame(6);
	roar->SetAnimationTime(2);
	roar->SetSpriteSheet(AssetManager::GetAsset("roarHades"));

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->SetSize(spriteBody->GetBounds().x, spriteBody->GetBounds().y);
	rigidBody2D->SetScale(scalex, scaley);


	idle->Play();

	enemy->AddAnimation("idle", idle);
	enemy->AddAnimation("roar", roar);
	enemy->AddAnimation("attack", attack);

	/*HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(enemy->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(enemy->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(25);
	healthPointBar->SetSize(25, 2);
	healthPointBar->SetScale(2.f, 2.f);
	healthPointBar->SetHealthPointBar();*/
	//enemies.push_back(gameObject);

	return gameObject;
}
GameObject* BuilderEntityGameObject::CreateProtectionBallGameObject(const std::string& _name, float _x, float _y, float scalex, float scaley, sf::Texture* _texture, const int& _number)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetScale(Maths::Vector2f(scalex, scaley));
	gameObject->SetDepth(0.7f);

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->SetScale(scalex, scaley);

	Sprite* spriteBody = gameObject->CreateComponent<Sprite>();
	spriteBody->SetName("spriteProtection");
	spriteBody->SetTexture(_texture);
	spriteBody->SetRecTextureWithFrame(_number % 4, _number % 2, 4, 2);
	spriteBody->SetScale(scalex, scaley);
	spriteBody->SetSprite();
	rigidBody2D->SetSize(spriteBody->GetBounds().x, spriteBody->GetBounds().y);

	/*HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetHealthPoint(enemy->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(enemy->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(25);
	healthPointBar->SetSize(25, 2);
	healthPointBar->SetScale(2.f, 2.f);
	healthPointBar->SetHealthPointBar();*/
	//enemies.push_back(gameObject);

	return gameObject;
}
