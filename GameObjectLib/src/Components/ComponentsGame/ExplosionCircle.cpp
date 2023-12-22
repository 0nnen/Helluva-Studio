#include "Components/ComponentsGame/ExplosionCircle.h"
#include <Components/RigidBody2D.h>
#include <Managers/SceneManager.h>
#include <Components/Entity/Character.h>

ExplosionCircle::ExplosionCircle() 
{
	player = SceneManager::GetActiveGameScene()->GetPlayer();
	alreadyHit = false;
}

void ExplosionCircle::SetGameObject(GameObject* _circle)
{
	circle = _circle;
}

void ExplosionCircle::Update(const float& _delta)
{
	cooldownExplosion -= _delta;
	if (player && circle) {
		if (RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(circle->GetComponent<RigidBody2D>())))
		{
			if (cooldownExplosion >= 0.0f && !alreadyHit)
			{
				SceneManager::GetActiveGameScene()->GetPlayer()->GetComponent<Character>()->SetHealthPoint(SceneManager::GetActiveGameScene()->GetPlayer()->GetComponent<Character>()->GetHealthPoint() - 25);
				alreadyHit = true;
				ExplosionCircle::~ExplosionCircle();
			}
		}
	}
	if (cooldownExplosion <= 0.0f)
	{
		ExplosionCircle::~ExplosionCircle();
	}
}

ExplosionCircle::~ExplosionCircle()
{
	SceneManager::GetActiveGameScene()->RemoveGameObject(circle);
}

void ExplosionCircle::Render(sf::RenderWindow* _window) {
	Component::Render(_window);
}