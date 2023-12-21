#include "Components/Entity/Enemy/EnemyA.h"
#include "Managers/SceneManager.h"
#include "Scenes/ScenesGame/ScenesTest.h"
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

	if (!ScenesTest::GetFlip())
	{

		SetDirection(Left);
		directionEnemy = true;
	}
	if (ScenesTest::GetFlip())
	{

		SetDirection(Right);
		directionEnemy = false;
	}

	if (!this->GetAnimation("shoot")->GetIsPlaying() && !this->GetAnimation("idle")->GetIsPlaying()) this->GetAnimation("idle")->Play();

}

void EnemyA::CreateBullet(float _x, float _y)
{
	bulletEnemy = BuilderEntityGameObject::CreateFireBallEnemy("fireBallEnemy", AssetManager::GetAsset("FireBallEnemy"), GetOwner(), 2.f, 1.f, 15.f, 15.f, Maths::Vector2f(_x, _y));
};


void EnemyA::Attack()
{
	Entity::Attack();
	GameObject* enemy = GetOwner();
	if (cooldown <= 0)
	{
		if (this->GetAnimation("idle")->GetIsPlaying()) this->GetAnimation("idle")->Stop();
		cooldown = fireRate;
		if (!this->GetAnimation("shoot")->GetIsPlaying()) 
		{
			this->GetAndSetAnimation("shoot")->Play();
		}
		if (!ScenesTest::GetFlip())
		{
			CreateBullet(-1.f, 0.f);
		}
		if (ScenesTest::GetFlip())
		{
			CreateBullet(1.f, 0.f);
		}
		
	}
	cooldown++;
	bulletShoot = false;
}

void EnemyA::Mouve(const float& _delta, float _speed)
{
	GameObject* enemy = SceneManager::GetActiveGameScene()->GetEnemy();
	enemy->GetComponent<RigidBody2D>()->AddForces(Maths::Vector2f::Left * _delta * _speed);
}