#pragma once

#include "Component.h"

class ExplosionCircle : public Component
{
public:
	ExplosionCircle();
	~ExplosionCircle();

	void SetGameObject(GameObject* circle);
	GameObject* GetGameObject() { return circle; };


	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;

private:
	GameObject* player = nullptr;
	GameObject* circle = nullptr;
	float cooldownExplosion = 2.0f;
	bool alreadyHit = false;
};

