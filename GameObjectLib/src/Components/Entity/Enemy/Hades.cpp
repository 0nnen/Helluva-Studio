#include "Components/Entity/Enemy/Hades.h"
#include "Managers/SceneManager.h"
#include <Components/RigidBody2D.h>
#include <Components/Entity/Enemy/ProtectionBall.h>

Hades::Hades() : Entity(1000, 200, 500.f, 40.f, 10000.f)
{
	platformFeu = BuilderEntityGameObject::CreateRangeHadesCollisionGameObject("CollisionRangeHades", 100, 1000, 2.0f, 2.5f);
	damageZone = BuilderEntityGameObject::CreateRangeHadesCollisionGameObject("DamageZone", 0, 1000, 2.0f, 7.5f);
	float nightmareX = (randomAttackCheval == 0) ? 2200 : 0;
	nightmare = BuilderEntityGameObject::CreateChevalGameObject("Nightmare", nightmareX, 1000, 2.5f, 2.5f, AssetManager::GetAsset("NightmareGalloping"));
	stateSwitch = true;
	this->CreateBouleFeu();
}
Hades::Hades(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range) : Entity(_hp, _damage, _speed, _attackSpeed, _range)
{

}

void Hades::SetProtection(const float& _delta)
{
	isInvicible = true;
	int randomNumber;
	Maths::Vector2f positionHades = GetOwner()->GetPosition();
	protection = BuilderEntityGameObject::CreateProtectionGameObject("Protection", positionHades.GetX(), positionHades.GetY(), 2.5f, 2.5f, AssetManager::GetAsset("protectionHades"));

	switch (step)
	{
	case Hades::Step3:
		randomNumber = rand() % 8;
		randomAttackCheval = rand() % 2;
		countAllerRetour3 = 3;
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection4", 500, 500, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber, GetOwner()));
		AllerRetourCheval(true, _delta, countAllerRetour, countAllerRetour2, countAllerRetour3);
	case Hades::Step2:
		randomNumber = rand() % 8;
		randomAttackCheval = rand() % 2;
		countAllerRetour2 = 3;
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection3", 1500, 800, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber, GetOwner()));
		AllerRetourCheval(true, _delta, countAllerRetour, countAllerRetour2, countAllerRetour3);
	case Hades::Step1:
		randomNumber = rand() % 8;
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection2", 1250, 400, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber, GetOwner()));
		randomNumber = rand() % 8;
		randomAttackCheval = rand() % 2;
		countAllerRetour = 2;
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection1", 1000, 200, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber, GetOwner()));
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("FireBall", 500, 1000, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), 1, GetOwner()));
		AllerRetourCheval(true, _delta, countAllerRetour, countAllerRetour2, countAllerRetour3);
		break;
	default:
		break;
	}
}

void Hades::SetDirection()
{
	Maths::Vector2f positionPlayer = SceneManager::GetActiveGameScene()->GetPlayer()->GetPosition();
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

void Hades::AttackFeu()
{
	Maths::Vector2f positionPlayer = SceneManager::GetActiveGameScene()->GetPlayer()->GetPosition();
	Maths::Vector2f positionHades = GetOwner()->GetPosition();

	platformFeu->SetPosition(Maths::Vector2f(positionHades.x + 50.0f, 1000));
	platformFeu->GetComponent<RigidBody2D>()->SetHeightCollider(positionHades.y);
	platformFeu->GetComponent<RigidBody2D>()->SetWidthCollider(positionHades.x);

	// si y'a collision avec le boss et que le player est dans la range du boss alors il va attacker/toucher le player
	if (SceneManager::GetActiveGameScene()->GetPlayer(), platformFeu) {
		
		if (RigidBody2D::IsColliding(*(SceneManager::GetActiveGameScene()->GetPlayer()->GetComponent<RigidBody2D>()), *(platformFeu->GetComponent<RigidBody2D>())))
		{
			if(positionPlayer.y > positionHades.y && stateSwitch)
			{
				state = Hades::State::Attack;
				stateSwitch = false;
				// implémenter les dégats subis du joueur
			}
		}
		else
		{
			state = Hades::State::Idle;
			stateSwitch = true;
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

void Hades::DamageZoneHades()
{
	Maths::Vector2f positionPlayer = SceneManager::GetActiveGameScene()->GetPlayer()->GetPosition();
	Maths::Vector2f positionHades = GetOwner()->GetPosition();

	damageZone->SetPosition(Maths::Vector2f(positionHades.x + 50.0f, positionHades.y));
	damageZone->GetComponent<RigidBody2D>()->SetHeightCollider(positionHades.y);
	damageZone->GetComponent<RigidBody2D>()->SetWidthCollider(positionHades.x);

	// si y'a collision avec le boss et que le player est dans la range du boss alors il va attacker/toucher le player
	if (SceneManager::GetActiveGameScene()->GetPlayer(), damageZone) {

		if (RigidBody2D::IsColliding(*(SceneManager::GetActiveGameScene()->GetPlayer()->GetComponent<RigidBody2D>()), *(damageZone->GetComponent<RigidBody2D>())))
		{
			if (stateSwitchZone)
			{
				stateSwitchZone = false;
				// implémenter les dégats subis du joueur
			}
		}
		else
		{
			stateSwitchZone = true;
		}
	}
}

void Hades::AttackCheval(int _randomAttackCheval, const float& _delta)
{
	Maths::Vector2f positionPlayer = SceneManager::GetActiveGameScene()->GetPlayer()->GetPosition();
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
					AllerRetourCheval(nightmareArrive, _delta, countAllerRetour, countAllerRetour2, countAllerRetour3);
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
					AllerRetourCheval(nightmareArrive, _delta, countAllerRetour, countAllerRetour2, countAllerRetour3);
				}
			}
		}
	}

	if (SceneManager::GetActiveGameScene()->GetPlayer(), nightmare) {
		if (RigidBody2D::IsColliding(*(SceneManager::GetActiveGameScene()->GetPlayer()->GetComponent<RigidBody2D>()), *(nightmare->GetComponent<RigidBody2D>())))
		{
			if (nightmare->GetPosition().GetX() > positionPlayer.GetX())
			{
				SceneManager::GetActiveGameScene()->GetPlayer()->GetComponent<RigidBody2D>()->AddForces(Maths::Vector2f(nightmare->GetPosition().x / nightmare->GetPosition().x - 15.0f, nightmare->GetPosition().y / nightmare->GetPosition().y - 80.0f));
			}
			else
			{
				SceneManager::GetActiveGameScene()->GetPlayer()->GetComponent<RigidBody2D>()->AddForces(Maths::Vector2f(nightmare->GetPosition().x / nightmare->GetPosition().x + 20.0f, nightmare->GetPosition().y / nightmare->GetPosition().y - 60.0f));
			}
			
			
		}
	}
}

void Hades::SpawnRandomBall()
{
	switch (spawn)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	default:
		break;
	}
}

void Hades::CreateBouleFeu()
{
	circle = BuilderEntityGameObject::CreateSphereFeuGameObject("FireCircle", 500, 1000, 100);
}

void Hades::BouleFeu()
{
	std::cout << "\n" << balls[2]->GetComponent<ProtectionBall>()->GetHealthPoint() << "\n";
	if (balls[2]->GetComponent<ProtectionBall>()->GetHealthPoint() <= 0)
	{
		std::cout << "il est dead boy\n";
	}
	if (SceneManager::GetActiveGameScene()->GetPlayer(), circle) {
		if (RigidBody2D::IsColliding(*(SceneManager::GetActiveGameScene()->GetPlayer()->GetComponent<RigidBody2D>()), *(circle->GetComponent<RigidBody2D>())))
		{
			// enelver des PV au joueur;
			std::cout << "Cirlce en collision\n";
		}
	}
}

void Hades::AllerRetourCheval(bool _nightmareArrive, const float& _delta, int& _countAllerRetour, int& _countAllerRetour2, int& _countAllerRetour3)
{
	if (_nightmareArrive) {
		newRandomAttackCheval = randomAttackCheval;

		do
		{
			randomAttackCheval = rand() % 2;
		} while (randomAttackCheval == newRandomAttackCheval);

		if (randomAttackCheval == 1) {
			nightmare->SetPosition(Maths::Vector2f(-200, 1000));
		}
		else if (randomAttackCheval == 0) {
			nightmare->SetPosition(Maths::Vector2f(2200, 1000));
		}

		AttackCheval(randomAttackCheval, _delta);

		if (_countAllerRetour != 0)
		{
			_countAllerRetour--;
		}

		if (_countAllerRetour2 != 0 && _countAllerRetour == 0)
		{
			_countAllerRetour2--;
		}

		if (_countAllerRetour3 != 0 && _countAllerRetour == 0 && _countAllerRetour2 == 0)
		{
			_countAllerRetour3--;
		}
		_nightmareArrive = false;
	}
}

void Hades::Update(const float& _delta)
{
	Entity::Update(_delta);
	GameObject* hades = GetOwner();

	SpawnRandomBall();

	DamageZoneHades();

	if (platformFeu)
	{
		if (cooldown >= 0.0f)
		{
			cooldown -= _delta;
			if (randomAttackFeu <= 1)
			{
				AttackFeu();
			}
		}
		else
		{
			state = Hades::State::Idle;
			cooldown = 10.0f;
			randomAttackFeu = rand() % 4;
		}
	}

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
	AttackCheval(randomAttackCheval, _delta);
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
			BouleFeu();
		}
	}
}