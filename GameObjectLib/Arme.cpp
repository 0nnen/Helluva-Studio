#include "Arme.h"
#include "BuilderGameObject.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"

Arme::Arme() {
	fireRate = 0.2f;
	fireCooldown = 0;
	mag = 10;
	maxAmo = 10;
	reload = 2.f;
	activeReload = 0.f;
}

void Arme::Update(const float& _delta) {
	Component::Update(_delta);

	if (activeReload > 0.f) {
		activeReload -= _delta;
	}
	if (activeReload <= 0 && mag <= 0) {
		mag = maxAmo;
	}
	if (fireCooldown > 0.f) {
		fireCooldown -= _delta;
	}

}

void Arme::Shoot() {
	if (mag > 0 && fireCooldown <= 0 && activeReload <= 0) {
		mag -= 1;
		fireCooldown = fireRate;
		bullets.push_back(BuilderEntityGameObject::CreateBulletGameObject("Bullet", *texture, 2.5f, 2.5f, GetOwner()));
		if (mag == 0) {
			activeReload = reload;
			fireCooldown = 0.f;
		}
	}

}

void Arme::Render(sf::RenderWindow* _window) {
	Component::Render(_window);
}

void Arme::ClearBullets()
{
	bullets.clear();
}

Arme::~Arme() {
	delete texture;
	this->ClearBullets();
}