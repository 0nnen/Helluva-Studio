#pragma once
#include "Components/ComponentsGame/Weapon.h"

class Gun : public Weapon
{
public:
	Gun();
	~Gun();


	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;
	void Attack() override;
	void RemoveBullet(GameObject* _objectToRemove) {
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
			[_objectToRemove](GameObject* obj) {
				return obj == _objectToRemove;
			}), bullets.end());
	}

	void ClearBullets();
	std::vector<GameObject*> GetBullets() { return bullets; }
	GameObject* GetBullet(int _index) const { return bullets[_index]; }

private:
	float fireRate = 1.f;
	int mag = 10;
	int maxAmo = 10;
	float reload = 1.f;
	float activeReload = 0.f;
	sf::Texture* texture;
	std::vector<GameObject*> bullets;

	float timeSinceEmpty = 0.0f;
	float reloadSoundDelay = 1.5f;
};


