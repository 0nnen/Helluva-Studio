#include "Components/Entity/Enemy/Hades.h"
#include "Managers/SceneManager.h"


Hades::Hades() : Entity(1000, 200, 500.f, 40.f, 10000.f)
{

}
Hades::Hades(const int& _hp, const int& _damage, const float& _speed, const float& _attackSpeed, const float& _range) : Entity(_hp, _damage, _speed, _attackSpeed, _range)
{

}

void Hades::SetProtection()
{
	isInvicible = true;
	int randomNumber;
	Maths::Vector2f positionHades = GetOwner()->GetPosition();

	protection = BuilderEntityGameObject::CreateProtectionGameObject("Protection", positionHades.GetX(), positionHades.GetY(), 2.5f, 2.5f, AssetManager::GetAsset("protectionHades"));
	switch (step)
	{
	case Hades::Step3:
		randomNumber = rand() % 8;
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection4", 500, 500, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber, GetOwner()));
	case Hades::Step2:
		randomNumber = rand() % 8;
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection3", 1500, 800, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber, GetOwner()));
	case Hades::Step1:
		randomNumber = rand() % 8;
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection2", 1250, 400, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber, GetOwner()));
		randomNumber = rand() % 8;
		balls.push_back(BuilderEntityGameObject::CreateProtectionBallGameObject("Protection1", 1000, 200, 0.5f, 0.5f, AssetManager::GetAsset("protectionBallsHades"), randomNumber, GetOwner()));
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

void Hades::Update(const float& _delta)
{
	Entity::Update(_delta);


	GameObject* hades = GetOwner();
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
			SetProtection();
			isInvicible = true;
			actualTime = 0.f;
		}
	}
}