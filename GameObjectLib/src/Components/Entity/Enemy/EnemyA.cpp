#include "Components/Entity/Enemy/EnemyA.h"
#include "Managers/SceneManager.h"
#include "Managers/AssetManager.h"
#include "Scenes/ScenesGame/ScenesTest.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Components/RigidBody2D.h"

EnemyA::EnemyA() : Entity()
{
	bulletShoot = true;
	directionEnemy = false;
	direction = Direction::Right;
	cooldown = 0.f;
	fireRate = 5.f;
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


void EnemyA::Attack(const float& _delta)
{
	Entity::Attack(_delta);
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
			CreateBullet(0.25f, 0.f);
		}
		if (ScenesTest::GetFlip())
		{
			CreateBullet(-0.25f, 0.f);
		}
		
	}
	cooldown -= _delta;
	bulletShoot = false;
}