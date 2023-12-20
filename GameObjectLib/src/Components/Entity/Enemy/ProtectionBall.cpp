#include "Components/Entity/Enemy/ProtectionBall.h"
#include "Components/Entity/Character.h"
#include "Components/Entity/Enemy/Hades.h"
#include "Managers/SceneManager.h"
#include <Components/RigidBody2D.h>

ProtectionBall::ProtectionBall() : Entity() 
{
	player = SceneManager::GetActiveGameScene()->GetPlayer();
	hades = SceneManager::GetActiveGameScene()->GetHades();
}
  
ProtectionBall::ProtectionBall(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range) : Entity(_hp, _damage, _speed, _attackSpeed, _range) {}

void ProtectionBall::Update(const float& _delta)
{
	Entity::Update(_delta);
	SetPower(_delta);
}


void ProtectionBall::CreateLava()
{
	area = BuilderEntityGameObject::CreateRectangleSpriteGameObject("Lava",position.x, 1100.f, 1.f, 0.5f, AssetManager::GetAsset("lavaArea"));
}


void ProtectionBall::CreateBouleFeu()
{
	circle = BuilderEntityGameObject::CreateSphereFeuGameObject("FireCircle", 500, 1000, 100);
}

void ProtectionBall::CollisionFireBall()
{
	if (player, circle) {
		std::cout << "debug\n";
		if (RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(circle->GetComponent<RigidBody2D>())))
		{
			// enelver des PV au joueur;
			std::cout << "Cirlce en collision\n";
		}
	}
}



void ProtectionBall::SetHealth()
{
	if (spawn <= 5)
	{
		// astral
		SetHealthPoint(175.f);
		SetMaxHealthPoint(175.f);

	}
	else if (spawn >= 6 && spawn <= 30)
	{
		//feu
	}
	else if (spawn >= 31 && spawn <= 40)
	{
		//spirituel
		SetHealthPoint(50.f);
		SetMaxHealthPoint(50.f);
	}
	else if (spawn >= 41 && spawn <= 55)
	{
		//eau t�n�breuse
		SetHealthPoint(250.f);
		SetMaxHealthPoint(250.f);
	}
	else if (spawn >= 56 && spawn <= 70)
	{
		//lave
		SetHealthPoint(100.f);
		SetMaxHealthPoint(100.f);
	}
	else if (spawn >= 71 && spawn <= 75)
	{
		//verte
		SetHealthPoint(100.f);
		SetMaxHealthPoint(100.f);
	}
	else if (spawn >= 86 && spawn <= 90)
	{
		//abysse
	}
	else  if (spawn >= 91 && spawn <= 100)
	{
		//eau
	}
}

void ProtectionBall::SetPower(const float& _delta)
{
	if (spawn <= 5)
	{

	}
	else if (spawn >= 6 && spawn <= 30)
	{

	}
	else if (spawn >= 31 && spawn <= 40)
	{
		if (tp >= 5)
		{
			randX = rand() % 1300 + 500;
			randY = rand() % 400 + 200;
			GetOwner()->SetPosition(Maths::Vector2f(randX, randY));
			tp = 0;
		}
		tp += _delta;
	}
	else if (spawn >= 41 && spawn <= 55)
	{
		
	}
	else if (spawn >= 56 && spawn <= 70)
	{
		position.x = GetOwner()->GetPosition().x;
		position.y = 100.f;
	}
	else if (spawn >= 71 && spawn <= 75)
	{

	}
	else if (spawn >= 86 && spawn <= 90)
	{

	}
	else if (spawn >= 91 && spawn <= 100)
	{

	}
}

void ProtectionBall::Die()
{
	Entity::Die();

	if (spawn <= 5)
	{
		hades->GetComponent<Hades>()->SetInvicible(false);
		hades->GetComponent<Hades>()->TakeDamage(50);
		hades->GetComponent<Hades>()->SetInvicible(true);
	}
	if (spawn >= 6 || spawn <= 30)
	{

	}
	if (spawn >= 31 || spawn <= 40)
	{
		
	}
	if (spawn >= 41 || spawn <= 55)
	{

	}
	if (spawn >= 56 || spawn <= 70)
	{
		CreateLava();
	}
	if (spawn >= 71 || spawn <= 75)
	{
		player->GetComponent<Character>()->TakeHealt(10);
	}
	if (spawn >= 86 || spawn <= 90)
	{

	}
	if (spawn >= 91 || spawn <= 100)
	{

	}


	hades->GetComponent<Hades>()->RemoveBall(GetOwner());
}