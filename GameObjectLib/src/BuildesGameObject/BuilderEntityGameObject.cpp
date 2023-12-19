#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/SceneManager.h"
#include "Managers/AssetManager.h"
#include "Components/SpriteRenderer.h"
#include "Components/Animation.h"
#include "Components/RigidBody2D.h"
#include "Components/HealthPointBar.h"
#include "Components/ComponentsGame/WeaponsContainer.h"
#include "Components/ComponentsGame/Bullet.h"
#include "Components/ComponentsGame/Sword.h"
#include "Components/ComponentsGame/FireBullet.h"
#include "Components/ComponentsGame/Gun.h"
#include "Components/Entity/Character.h"
#include "Components/Inputs/InputCharacter.h"
#include "Components/Entity/Enemy/EnemyA.h"
#include "Components/Entity/Enemy/Hades.h"
#include "Components/Entity/Enemy/ProtectionBall.h"

#include <Components/Shapes/Rectangle.h>
#include <Components/Shapes/Triangle.h>
#include "Components/Transform.h"
#include "Components/SquareCollider.h"
#include "TileMap/TileMap.h"

GameObject* BuilderEntityGameObject::CreateMapGameObject(const std::string& _name, const std::string& _jsonFile, const std::string& _tilesetName, const int& _idEmptyCollision)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(0, 0));
	gameObject->SetDepth(0.1f);

	TileMap* tileMap = gameObject->CreateComponent<TileMap>();
	tileMap->LoadIdCollision(_idEmptyCollision);
	tileMap->LoadTile(_jsonFile, _tilesetName);

	return gameObject;
}

GameObject* BuilderEntityGameObject::CreateBulletGameObject(const std::string& _name, sf::Texture* _textureBullet, GameObject* _player, const float& _scalex, const float& _scaley, const float& _damage, const float& _speed, const Maths::Vector2f& _direction, const float& _rotate, const Maths::Vector2f& _position)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(_position);
	gameObject->SetRotation(_rotate);
	gameObject->SetScale(Maths::Vector2f(_scalex, _scaley));
	gameObject->SetDepth(0.5f);

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetTexture(_textureBullet);

	Bullet* bullet = gameObject->CreateComponent<Bullet>();
	bullet->SetSpeed(_speed);

	rigidBody2D->AddForces(_direction * bullet->GetSpeed());

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidthCollider(sprite->GetBounds().x);
	squareCollider->SetHeightCollider(sprite->GetBounds().y);

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


	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(true);
	rigidBody2D->SetMass(0.5);
	rigidBody2D->SetMaxVelocity(Maths::Vector2f(300, 5000));


	Character* character = gameObject->CreateComponent<Character>();


	Sprite* spriteBody = gameObject->CreateComponent<Sprite>();
	spriteBody->SetName("body");
	spriteBody->SetTexture(texture);
	spriteBody->SetRecTextureWithFrame(0, 0, 10, 1);

	Sprite* spriteArm = gameObject->CreateComponent<Sprite>();
	spriteArm->SetName("arm");
	spriteArm->SetTexture(texture);
	spriteArm->SetActiveAndVisible(false);


	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetName("shape");
	squareCollider->SetWidthCollider((spriteBody->GetBounds().x - 30.f) * scalex);
	squareCollider->SetHeightCollider((spriteBody->GetBounds().y) * scaley);

	SquareCollider* squareColliderGround = gameObject->CreateComponent<SquareCollider>();
	squareColliderGround->SetName("ground");
	squareColliderGround->SetWidthCollider((spriteBody->GetBounds().x - 30.f) * scalex);
	squareColliderGround->SetHeightCollider(2);
	squareColliderGround->SetPerfectPosition(Maths::Vector2f(0, squareCollider->GetBottomCollider() + 1.f));
	squareColliderGround->SetActiveCollider(false);


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
	rigidBody2D->SetSize(200.f, 50.f);

	Rectangle* rectangle = gameObject->CreateComponent<Rectangle>();

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
	gameObject->SetPosition(Maths::Vector2f(_widthPos, _heightPos));
	gameObject->SetRotation(_rotation);

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

	Rectangle* rectangle = gameObject->CreateComponent<Rectangle>();

	return gameObject;
}

GameObject* BuilderEntityGameObject::CreateEnemyAGameObject(const std::string& _name, float _x, float _y, float scalex, float scaley, sf::Texture* _texture)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetScale(Maths::Vector2f(scalex, scaley));
	gameObject->SetDepth(0.9f);


	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(true);


	EnemyA* enemy = gameObject->CreateComponent<EnemyA>();


	Sprite* spriteBody = gameObject->CreateComponent<Sprite>();
	spriteBody->SetName("bodyEnemyA");
	spriteBody->SetTexture(_texture);


	Animation* idle = gameObject->CreateComponent<Animation>();
	idle->SetLoop(-1);
	idle->SetName("idle");
	idle->SetFrame(6);
	idle->SetAnimationTime(1);
	idle->SetSpriteSheet(AssetManager::GetAsset("idleEnemyA"));

	Animation* shoot = gameObject->CreateComponent<Animation>();
	shoot->SetLoop(1);
	shoot->SetName("idle");
	shoot->SetFrame(4);
	shoot->SetAnimationTime(1);
	shoot->SetSpriteSheet(AssetManager::GetAsset("shootEnemyA"));

	idle->Play();

	enemy->AddAnimation("idle", idle);
	enemy->AddAnimation("shoot", shoot);


	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidthCollider(spriteBody->GetBounds().x);
	squareCollider->SetHeightCollider(spriteBody->GetBounds().y);



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
	gameObject->SetScale(Maths::Vector2f(scalex, scaley));
	gameObject->SetDepth(0.9f);

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);

	Hades* enemy = gameObject->CreateComponent<Hades>();
	enemy->SetInvicible(false);

	Sprite* spriteBody = gameObject->CreateComponent<Sprite>();
	spriteBody->SetName("bodyEnemyA");
	spriteBody->SetTexture(_texture);

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

	idle->Play();

	enemy->AddAnimation("idle", idle);
	enemy->AddAnimation("roar", roar);
	enemy->AddAnimation("attack", attack);

	spriteBody->SetRecTextureWithFrame(0, 0, 6, 1);

	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidthCollider(spriteBody->GetBounds().x);
	squareCollider->SetHeightCollider(spriteBody->GetBounds().y);


	HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetScale(scalex, scaley);
	healthPointBar->SetSize(spriteBody->GetSizeV2f().GetX() + 25, 5);
	healthPointBar->SetHealthPoint(enemy->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(enemy->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(75);
	healthPointBar->SetHealthPointBar();

	return gameObject;
}
GameObject* BuilderEntityGameObject::CreateProtectionBallGameObject(const std::string& _name, float _x, float _y, float scalex, float scaley, sf::Texture* _texture, const int& _number, GameObject* _hades)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetScale(Maths::Vector2f(scalex, scaley));
	gameObject->SetDepth(0.7f);

	ProtectionBall* protectionBall = gameObject->CreateComponent<ProtectionBall>();
	protectionBall->SetHades(_hades);

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->SetKillImperfection(Maths::Vector2f(22., 22.f));

	Sprite* spriteBody = gameObject->CreateComponent<Sprite>();
	spriteBody->SetName("spriteProtectionBall");
	spriteBody->SetTexture(_texture);
	spriteBody->SetRecTextureWithFrame(_number % 4, _number % 2, 4, 2);


	SquareCollider* squareCollider = gameObject->CreateComponent<SquareCollider>();
	squareCollider->SetWidthCollider(spriteBody->GetBounds().x);
	squareCollider->SetHeightCollider(spriteBody->GetBounds().y);

	HealthPointBar* healthPointBar = gameObject->CreateComponent<HealthPointBar>();
	healthPointBar->SetScale(scalex, scaley);
	healthPointBar->SetSize(spriteBody->GetSizeV2f().GetX() + 25, 15);
	healthPointBar->SetHealthPoint(protectionBall->GetHealthPoint());
	healthPointBar->SetMaxHealthPoint(protectionBall->GetMaxHealthPoint());
	healthPointBar->SetAboveSprite(100);
	healthPointBar->SetHealthPointBar();

	return gameObject;
}
GameObject* BuilderEntityGameObject::CreateProtectionGameObject(const std::string& _name, float _x, float _y, float scalex, float scaley, sf::Texture* _texture)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_x, _y));
	gameObject->SetScale(Maths::Vector2f(scalex, scaley));
	gameObject->SetDepth(0.8999999f);

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->SetKillImperfection(Maths::Vector2f(22., 22.f));

	Sprite* spriteBody = gameObject->CreateComponent<Sprite>();
	spriteBody->SetName("spriteProtection");
	spriteBody->SetTexture(_texture);
	spriteBody->SetRecTextureWithFrame(0, 0, 6, 1);

	Animation* animation = gameObject->CreateComponent<Animation>();
	animation->SetLoop(1);
	animation->SetName("protection");
	animation->SetFrame(6);
	animation->SetAnimationTime(2);
	animation->SetSpriteSheet(AssetManager::GetAsset("protectionHades"));
	animation->Play();

	return gameObject;
}

GameObject* BuilderEntityGameObject::CreateFireBallEnemy(const std::string& _name, sf::Texture* _textureBullet, GameObject* _enemy, const float& _scalex, const float& _scaley, const float& _damage, const float& _speed, const Maths::Vector2f& _position)
{
	GameObject* gameObject = SceneManager::GetActiveGameScene()->CreateGameObject(_name);
	gameObject->SetPosition(Maths::Vector2f(_enemy->GetPosition().GetX(), _enemy->GetPosition().GetY()) + gameObject->GetTransform()->TransformPoint());
	gameObject->SetDepth(0.9f);

	FireBullet* bullet = gameObject->CreateComponent<FireBullet>();

	Sprite* sprite = gameObject->CreateComponent<Sprite>();
	sprite->SetName("FireBall");
	sprite->SetTexture(_textureBullet);

	Animation* idle = gameObject->CreateComponent<Animation>();
	idle->SetLoop(-1);
	idle->SetName("idle");
	idle->SetFrame(3);
	idle->SetAnimationTime(1);
	idle->SetSpriteSheet(AssetManager::GetAsset("FireBallEnemy"));

	RigidBody2D* rigidBody2D = gameObject->CreateComponent<RigidBody2D>();
	rigidBody2D->SetSize(sprite->GetBounds().x, sprite->GetBounds().y);
	rigidBody2D->SetIsGravity(false);
	rigidBody2D->AddForces(_position * bullet->GetSpeed());

	idle->Play();

	bullet->AddAnimation("idle", idle);

	return gameObject;
};