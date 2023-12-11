#include "Components/ComponentsGame/Gun.h"
#include "BuilderGameObject.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "Managers/AssetManager.h"
#include "Managers/WindowManager.h"

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
		sf::RenderWindow* window = WindowManager::GetWindow();
		GameObject* player = SceneManager::GetActiveGameScene()->GetPlayer();

		const sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
		const sf::Vector2f worldMousePosition = window->mapPixelToCoords(mousePosition);
		Maths::Vector2f mousePositionVector = Maths::Vector2f(mousePosition.x, mousePosition.y);
		const Maths::Vector2f direction = mousePositionVector - player->GetPosition();
		const float length = direction.Magnitude();
		if (length != 0) {
			bullets.push_back(BuilderEntityGameObject::CreateBulletGameObject("Bullet", AssetManager::GetAsset("bullet"), player, 2.5f, 2.5f, 25.f, 1500.f, direction / length));
		}
		else
		{
			bullets.push_back(BuilderEntityGameObject::CreateBulletGameObject("Bullet", AssetManager::GetAsset("bullet"), player, 2.5f, 2.5f, 25.f, 1500.f, direction / length));
		}
		
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