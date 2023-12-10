#include "Components/ComponentsGame/Gun.h"
#include "BuilderGameObject.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"

Gun::Gun() {
	fireRate = 0.2f;
	mag = 10;
	maxAmo = 10;
	reload = 2.f;
	activeReload = 0.f;
}

void Gun::Update(const float& _delta) {
	Weapon::Update(_delta);

	if (activeReload > 0.f) {
		activeReload -= _delta;
	}
	if (activeReload <= 0 && mag <= 0) {
		mag = maxAmo;
	}
	if (cooldown > 0.f) {
		cooldown -= _delta;
	}
}

void Gun::Attack() {
	if (mag > 0 && cooldown <= 0 && activeReload <= 0) {
		mag -= 1;
		cooldown = fireRate;
		bullets.push_back(BuilderEntityGameObject::CreateBulletGameObject("Bullet", texture, 2.5f, 2.5f, GetOwner()));
		if (mag == 0) {
			activeReload = reload;
			cooldown = 0.f;
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