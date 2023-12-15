#include "Components/Entity/Enemy/EnemyA.h"
#include "Managers/SceneManager.h"
#include "Scenes/ScenesGame/SceneGameWorld.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Components/RigidBody2D.h"

float EnemyA::cooldown;
float EnemyA::fireRate;
float EnemyA::speed;
bool EnemyA::bulletShoot;
GameObject* EnemyA::bulletEnemy;

EnemyA::EnemyA() : Entity()
{
	bulletShoot = true;
	directionEnemy = false;
	direction = Direction::Right;
	cooldown = 0.f;
	fireRate = 150.f;
	SetSpeed(10.f);
}

void EnemyA::Update(const float& _delta)
{
	Entity::Update(_delta);

	if (SceneGameWorld::GetFlip())
	{

		SetDirection(Left);
		directionEnemy = true;
	}
	if (!SceneGameWorld::GetFlip())
	{

		SetDirection(Right);
		directionEnemy = false;
	}


}


void EnemyA::Attack(float _x, float _y)
{
	GameObject* enemy = SceneManager::GetActiveGameScene()->GetEnemy();
	if (cooldown <= 0)
	{
		bulletShoot = true;
		cooldown = fireRate;
		bulletEnemy = BuilderEntityGameObject::CreateFireBallEnemy("fireBallEnemy", AssetManager::GetAsset("FireBallEnemy"), enemy, 2.f, 1.f, 15.f, 15.f, Maths::Vector2f(_x, _y));
	}
	bulletShoot = false;
	cooldown--;
}

void EnemyA::Mouve(const float& _delta, float _speed)
{
	GameObject* enemy = SceneManager::GetActiveGameScene()->GetEnemy();
	enemy->GetComponent<RigidBody2D>()->AddForces(Maths::Vector2f::Left * _delta * _speed);
}