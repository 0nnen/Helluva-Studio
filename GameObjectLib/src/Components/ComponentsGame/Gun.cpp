#include "Components/ComponentsGame/Gun.h"
#include "BuilderGameObject.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/AssetManager.h"
#include "Managers/WindowManager.h"
#include "Components/SpriteRenderer.h"
#include "Components/Entity/Character.h"
#include <cmath>
#include <Managers/AudioManager.h>
# define M_PI           3.14159265358979323846  /* pi */

Gun::Gun() {
	fireRate = 0.2f;
	mag = 10;
	maxAmo = 10;
	reload = 2.f;
	activeReload = 0.f;

}

void Gun::Update(const float& _delta) {
	Weapon::Update(_delta);
	timeSinceEmpty = 0.0f;

	if (activeReload > 0.f) {
		activeReload -= _delta;
		timeSinceEmpty += _delta;
		if (mag <= 0) {
			if (timeSinceEmpty >= reloadSoundDelay) {
				AudioManager::PlaySound("GunReload");
				timeSinceEmpty = 0.0f;
			}
		}
	}
	if (activeReload <= 0 && mag <= 0) {
		mag = maxAmo;
		underCooldown = false;
	}
	if (cooldown > 0.f) {
		cooldown -= _delta;
	}
}

void Gun::Attack() {
	Weapon::Attack();
	GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
	Character* character = player->GetComponent<Character>();
	if (!underCooldown)
	{
		if (!character->GetAnimation("shootArm")->GetIsPlaying() && !character->GetAnimation("shootBody")->GetIsPlaying()) {
			if (character->GetAnimation("idle")->GetIsPlaying()) character->GetAnimation("idle")->Stop();
			if (character->GetAnimation("run")->GetIsPlaying()) character->GetAnimation("run")->Stop();
			if (character->GetAnimation("jump")->GetIsPlaying()) character->GetAnimation("jump")->Stop();
			character->GetAnimation("shootBody")->Play();
			const std::string nameArm = "arm";
			character->GetAnimation("shootArm")->Play(nameArm);
		}
	}
	else
	{
		if (character->GetAnimation("shootBody")->GetIsPlaying()) character->GetAndSetAnimation("shootBody")->Stop();
		if (character->GetAnimation("shootArm")->GetIsPlaying()) character->GetAndSetAnimation("shootArm")->Stop();
		if (!character->GetAnimation("run")->GetIsPlaying())
		{
			if (!character->GetAnimation("idle")->GetIsPlaying()) {
				character->GetAndSetAnimation("idle")->Play();
			}
		}
	}
	if (mag > 0 && cooldown <= 0 && activeReload <= 0) {
		cooldown = fireRate;
		sf::RenderWindow* window = WindowManager::GetWindow();
		GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();
		RigidBody2D* rigidBody2D = player->GetComponent<RigidBody2D>();
		const sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		const sf::Vector2f worldMousePosition = window->mapPixelToCoords(mousePosition);
		Maths::Vector2f worldMousePositionVector = Maths::Vector2f(worldMousePosition.x, worldMousePosition.y);
		const Maths::Vector2f direction = worldMousePositionVector - player->GetPosition();
		const float length = direction.Magnitude();

		const std::string nameArm = "arm";
		float angleDegre = 0.f;
		float angleRadian = 0.f;
		for (Sprite* _sprite : player->GetComponentsByType<Sprite>())
		{

			if (_sprite->GetName() == nameArm) {
				if (direction.x >= 0) angleRadian = std::atan2(worldMousePositionVector.y - player->GetPosition().y, worldMousePositionVector.x - player->GetPosition().x);
				else angleRadian = std::atan2(worldMousePositionVector.y - player->GetPosition().y, -(worldMousePositionVector.x - player->GetPosition().x));
				angleDegre = angleRadian * 180 / M_PI;
				if (direction.x >= 0)
				{
					rigidBody2D->AddForces(-Maths::Vector2f(50.f, 0.f));
					_sprite->Rotate(angleDegre);
				}
				else
				{
					rigidBody2D->AddForces(Maths::Vector2f(50.f, 0.f));
					_sprite->Rotate(-angleDegre);
				}
			}
		}
		if (length != 0) {
			AudioManager::PlaySound("GunShot");
			if (direction.x >= 0)bullets.push_back(BuilderEntityGameObject::CreateBulletGameObject("Bullet", AssetManager::GetAsset("bullet"), player, 1.f, 1.f, 25.f, 1500.f, worldMousePositionVector, angleRadian, Maths::Vector2f(25.f, -7.f)));
			else bullets.push_back(BuilderEntityGameObject::CreateBulletGameObject("Bullet", AssetManager::GetAsset("bullet"), player, 1.f, 1.f, 25.f, 1500.f, worldMousePositionVector, -angleRadian + M_PI, Maths::Vector2f(25.f, 7.f)));
		}
		mag -= 1;
		if (mag == 0) {
			underCooldown = true;
			activeReload = reload;
			cooldown = 0.f;
		}
		else if (mag == 0 && cooldown <= 0 && activeReload <= 0) {
			AudioManager::PlaySound("GunEmpty");
			cooldown = fireRate;
		}
	}

}

void Gun::Render(sf::RenderWindow* _window) {
	Component::Render(_window);
}

void Gun::ClearBullets()
{
	bullets.clear();
}

Gun::~Gun() {
	delete texture;
	this->ClearBullets();
}