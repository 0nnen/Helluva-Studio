#pragma once
#include "Component.h"

class Arme : public Component
{
public:
	Arme();
	~Arme();


	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;
	void Shoot();
	void RemoveBullet(GameObject* _objectToRemove) {
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
			[_objectToRemove](GameObject* obj) {
				return obj == _objectToRemove;
			}), bullets.end());
	}

	void ClearBullets();
	int GetDamage() const { return damage; }
	void SetDamage(const int _damage) { damage = _damage; }
	std::vector<GameObject*> GetBullets() { return bullets; }
	GameObject* GetBullet(int _index) const { return bullets[_index]; }

private:
	int damage = 20;
	float fireRate = 1.f;
	float fireCooldown = 0.f;
	int mag = 10;
	int maxAmo = 10;
	float reload = 1.f;
	float activeReload = 0.f;
	sf::Texture* texture;
	std::vector<GameObject*> bullets;
};


