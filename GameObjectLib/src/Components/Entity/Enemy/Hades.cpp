#include "Components/Entity/Enemy/Hades.h"
#include "Managers/SceneManager.h"
#include <Components/RigidBody2D.h>
#include <Components/Entity/Enemy/ProtectionBall.h>
#include <Components/Entity/Character.h>

Hades::Hades() : Entity(1000, 200, 500.f, 40.f, 10000.f)
{
	attackFire = BuilderEntityGameObject::CreateRangeHadesCollisionGameObject("CollisionRangeHades", -200, 1000, 1.5f, 2.5f);
	damageZone = BuilderEntityGameObject::CreateRangeHadesCollisionGameObject("DamageZone", -200, 1000, 2.0f, 7.5f);
	float nightmareX = (randomAttackCheval == 0) ? 2200 : 0;
	nightmare = BuilderEntityGameObject::CreateChevalGameObject("Nightmare", nightmareX, 1000, 2.5f, 2.5f, AssetManager::GetAsset("NightmareGalloping"));
	countAllerRetour = 1;
	countAllerRetour2 = 3;
	countAllerRetour3 = 3;
	hitHorse = true;

	player = SceneManager::GetActiveGameScene()->GetPlayer();
}
Hades::Hades(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range) : Entity(_hp, _damage, _speed, _attackSpeed, _range)
{

}

void Hades::SetProtection(const float& _delta)
{
	isInvicible = true;
	Maths::Vector2f positionHades = GetOwner()->GetPosition();
	protection = BuilderEntityGameObject::CreateProtectionGameObject("Protection", positionHades.GetX(), positionHades.GetY(), 2.5f, 2.5f, AssetManager::GetAsset("protectionHades"));

	switch (step)
	{
	case Hades::Step3:
		randomNumber = rand() % 8;
		randX = rand() % 1300 + 500;
		randY = rand() % 400 + 200;
		randomAttackCheval = rand() % 2;
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection4", randX, randY, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber, GetOwner(), randomNumber));
		AllerRetourHorse(true, _delta);
	case Hades::Step2:
		randomNumber = rand() % 8;
		randX = rand() % 1300 + 500;
		randY = rand() % 400 + 200;
		randomAttackCheval = rand() % 2;
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection3", randX, randY, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber, GetOwner(), randomNumber));
		AllerRetourHorse(true, _delta);
	case Hades::Step1:
		randomNumber = 0;
		randX = rand() % 1300 + 500;
		randY = rand() % 400 + 200;
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection2", randX, randY, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber, GetOwner(), 1));
		randomNumber = 0;
		randX = rand() % 1300 + 500;
		randY = rand() % 400 + 200;
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection1", randX, randY, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber, GetOwner(), 1));
		AllerRetourHorse(true, _delta);
		break;
	default:
		break;
	}
}

void Hades::SetDirection()
{
	Maths::Vector2f positionPlayer = player->GetPosition();
	Maths::Vector2f positioHades = GetOwner()->GetPosition();

	if (positioHades.GetX() <= positionPlayer.GetX())
	{
		for (Sprite* sprite : GetOwner()->GetComponentsByType<Sprite>()) {
			if (sprite) sprite->SetScale(-1 * GetOwner()->GetScale().GetX(), GetOwner()->GetScale().GetY());
		}
	}
	else
	{
		for (Sprite* sprite : GetOwner()->GetComponentsByType<Sprite>()) {
			if (sprite) sprite->SetScale(GetOwner()->GetScale().GetX(), GetOwner()->GetScale().GetY());
		}
	}
}

void Hades::AttackFire(const float& _delta)
{
	Maths::Vector2f positionPlayer = player->GetPosition();
	Maths::Vector2f positionHades = GetOwner()->GetPosition();

	attackFire->SetPosition(Maths::Vector2f(positionHades.x + 50.0f, 1000));
	attackFire->GetComponent<RigidBody2D>()->SetHeightCollider(positionHades.y);
	attackFire->GetComponent<RigidBody2D>()->SetWidthCollider(positionHades.x);

	// si y'a collision avec le boss et que le player est dans la range du boss alors il va attacker/toucher le player
	if (player, attackFire) {

		if (RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(attackFire->GetComponent<RigidBody2D>())))
		{
			if (positionPlayer.y > positionHades.y)
			{
				state = Hades::State::Attack;
				cooldownAttackFeu -= _delta;
				if (cooldownAttackFeu <= 0.0f)
				{
					player->GetComponent<Character>()->TakeDamage(1);
					cooldownAttackFeu = 1.0f;
				}
			}
		}
		else
		{
			state = Hades::State::Idle;
		}
	}

	// le boss track le player
	if (positionHades.GetX() <= positionPlayer.GetX() - 300)
	{
		Hades::GetOwner()->SetPosition(Maths::Vector2f(GetOwner()->GetPosition().x + 0.05f, GetOwner()->GetPosition().y));
	}
	else if (positionHades.GetX() >= positionPlayer.GetX() + 300)
	{
		Hades::GetOwner()->SetPosition(Maths::Vector2f(GetOwner()->GetPosition().x - 0.05f, GetOwner()->GetPosition().y));
	}
}

void Hades::DamageZoneHades(const float& _delta)
{
	Maths::Vector2f positionPlayer = player->GetPosition();
	Maths::Vector2f positionHades = GetOwner()->GetPosition();

	damageZone->SetPosition(Maths::Vector2f(positionHades.x + 50.0f, positionHades.y));
	damageZone->GetComponent<RigidBody2D>()->SetHeightCollider(positionHades.y);
	damageZone->GetComponent<RigidBody2D>()->SetWidthCollider(positionHades.x);

	// si y'a collision avec le boss et que le player est dans la range du boss alors il va attacker/toucher le player
	if (player, damageZone) {

		if (RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(damageZone->GetComponent<RigidBody2D>())))
		{
			cooldownDamageZone -= _delta;
			if (cooldownDamageZone <= 0.0f)
			{
				player->GetComponent<Character>()->TakeDamage(1);
				cooldownDamageZone = 2.0f;
			}
		}
	}
}

void Hades::AttackHorse(int _randomAttackCheval, const float& _delta)
{
	Maths::Vector2f positionPlayer = player->GetPosition();
	Maths::Vector2f positionHades = GetOwner()->GetPosition();

	if (countAllerRetour > 0 || countAllerRetour2 > 0 || countAllerRetour3 > 0)
	{
		if (_randomAttackCheval == 1)
		{
			if (nightmare->GetPosition().x <= 2200)
			{
				nightmare->SetPosition(Maths::Vector2f(nightmare->GetPosition().x + (speed * _delta), nightmare->GetPosition().y));
				for (Sprite* sprite : nightmare->GetComponentsByType<Sprite>()) {
					if (sprite) sprite->SetScale(-1 * nightmare->GetScale().GetX(), nightmare->GetScale().GetY());
				}
				if (nightmare->GetPosition().x >= 2200)
				{
					nightmareArrive = true;
					AllerRetourHorse(nightmareArrive, _delta);
				}
			}
		}
		else if (_randomAttackCheval == 0)
		{
			if (nightmare->GetPosition().x >= -200)
			{
				nightmare->SetPosition(Maths::Vector2f(nightmare->GetPosition().x - (speed * _delta), nightmare->GetPosition().y));
				for (Sprite* sprite : nightmare->GetComponentsByType<Sprite>()) {
					if (sprite) sprite->SetScale(nightmare->GetScale().GetX(), nightmare->GetScale().GetY());
				}
				if (nightmare->GetPosition().x <= -200)
				{
					nightmareArrive = true;
					AllerRetourHorse(nightmareArrive, _delta);
				}
			}
		}
	}

	if (player, nightmare) {
		if (RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(nightmare->GetComponent<RigidBody2D>())))
		{
			cooldownAttackHorse -= _delta;
			if (cooldownAttackHorse <= 0.0f)
			{
				hitHorse = true;

			}
			if (hitHorse)
			{
				player->GetComponent<Character>()->TakeDamage(5);
				hitHorse = false;
				cooldownAttackHorse = 0.15f;
			}
			if (nightmare->GetPosition().GetX() > positionPlayer.GetX())
			{
				player->GetComponent<RigidBody2D>()->AddForces(Maths::Vector2f(nightmare->GetPosition().x / nightmare->GetPosition().x - 15.0f, nightmare->GetPosition().y / nightmare->GetPosition().y - 80.0f));
			}
			else
			{
				player->GetComponent<RigidBody2D>()->AddForces(Maths::Vector2f(nightmare->GetPosition().x / nightmare->GetPosition().x + 20.0f, nightmare->GetPosition().y / nightmare->GetPosition().y - 60.0f));
			}
		}
	}
}

void Hades::AllerRetourHorse(bool _nightmareArrive, const float& _delta)
{
	if (_nightmareArrive) {
		newRandomAttackCheval = randomAttackCheval;

		do
		{
			randomAttackCheval = rand() % 2;
		} while (randomAttackCheval == newRandomAttackCheval);

		if (randomAttackCheval == 1) {
			nightmare->SetPosition(Maths::Vector2f(-500, 1000));
		}
		else if (randomAttackCheval == 0) {
			nightmare->SetPosition(Maths::Vector2f(2200, 1000));
		}

		AttackHorse(randomAttackCheval, _delta);

		ManageHorseAllerRetour(_delta);

		_nightmareArrive = false;
	}
}

void Hades::ManageHorseAllerRetour(const float& _delta)
{
	// Permet de check les aller retour selon les Steps du Boss

	if (countAllerRetour != 0)
	{
		countAllerRetour--;
	}

	if (countAllerRetour2 != 0 && countAllerRetour == 0)
	{
		countAllerRetour2--;
	}

	if (countAllerRetour3 != 0 && countAllerRetour == 0 && countAllerRetour2 == 0)
	{
		countAllerRetour3--;
	}

	// Permet de relancer l'attaque cheval elle est appellé

	if (countAllerRetour == 0)
	{
		cooldoawnAttack -= _delta;
		if (cooldoawnAttack <= 0.0f)
		{
			randomAttackFeu = rand() % 2;
			countAllerRetour = 2;
		}
		cooldoawnRoar = 3.0f;
	}
	if (countAllerRetour2 == 0)
	{
		randomAttackFeu = rand() % 2;
		countAllerRetour2 = 3;
	}
	if (countAllerRetour3 == 0)
	{
		randomAttackFeu = rand() % 2;
		countAllerRetour3 = 3;
	}
}

void Hades::ManageAttack(const float& _delta)
{
	if (attackFire)
	{
		if (randomAttackFeu == 0)
		{

			if (cooldown >= 0.0f)
			{
				cooldown -= _delta;
				AttackFire(_delta);
				cooldoawnAttack = 5.0f;
			}
			else {
				cooldoawnAttack -= _delta;
				if (cooldoawnAttack <= 0.0f)
				{
					randomAttackFeu = rand() % 2;
					cooldown = 10.0f;
				}
			}
			cooldoawnRoar = 3.0f;
		}
		else if (randomAttackFeu == 1)
		{

			if (cooldoawnRoar >= 0.0f)
			{
				cooldoawnRoar -= _delta;
				state = Hades::State::Roar;
				cooldoawnAttack = 5.0f;
			}
			else
			{
				state = Hades::State::Idle;
			}
			AttackHorse(randomAttackCheval, _delta);
		}
	}
}

void Hades::Update(const float& _delta)
{
	Entity::Update(_delta);
	GameObject* hades = GetOwner();

	DamageZoneHades(_delta);

	ManageAttack(_delta);

	if (protection)
	{
		protection->SetPosition(hades->GetPosition());
		Animation* animation = protection->GetComponent<Animation>();
		if (!animation->GetIsPlaying())
		{
			animation->GetSprite()->SetRecTexture(5, animation->GetWidth() / 6, animation->GetHeight());
			animation->GetSprite()->SetActiveAndVisible(true);
		}

	}

	SetDirection();
	
	if (state == Hades::State::Idle)
	{
		if (!GetAnimation("idle")->GetIsPlaying()) {
			GetAnimation("roar")->Stop();
			GetAnimation("attack")->Stop();
			GetAnimation("idle")->Play();
		}
	}
	else if (state == Hades::State::Move)
	{
		if (!GetAnimation("idle")->GetIsPlaying()) {
			GetAnimation("roar")->Stop();
			GetAnimation("attack")->Stop();
			GetAnimation("idle")->Play();
		}
	}
	else if (state == Hades::State::Attack)
	{
		if (!GetAnimation("attack")->GetIsPlaying()) {
			GetAnimation("idle")->Stop();
			GetAnimation("roar")->Stop();
			GetAnimation("attack")->Play();
		}
	}
	else if (state == Hades::State::Roar)
	{
		if (!GetAnimation("roar")->GetIsPlaying()) {
			GetAnimation("idle")->Stop();
			GetAnimation("attack")->Stop();
			GetAnimation("roar")->Play();
		}
	}

	if (healthPoint > maxHealthPoint * 66 / 100) step = Step1;
	else if (healthPoint > maxHealthPoint * 33 / 100 && healthPoint < maxHealthPoint * 66 / 100) step = Step2;
	else step = Step3;

	if (balls.empty())
	{
		if (protection) {
			SceneManager::GetActiveGameScene()->RemoveGameObject(protection);
			delete protection;
			protection = nullptr;
		}
		isInvicible = false;
		actualTime += _delta;
		if (actualTime >= timeSpawnBalls)
		{
			SetProtection(_delta);
			isInvicible = true;
			actualTime = 0.f;
		}
	}
}