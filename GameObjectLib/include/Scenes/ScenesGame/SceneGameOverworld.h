#pragma once

#include "Scenes/SceneGameAbstract.h"

class SceneGameOverworld : public SceneGameAbstract 
{
public:
	SceneGameOverworld(const std::string& _newName);
	~SceneGameOverworld();

	void Awake() override;
	void Preload() override;

	void CreateEnemy();

	void Collinding();
	void CollindingEntity(GameObject* _entity);
	void CollisionRengePosition(const float& _delta, GameObject* _entity);
	void CollisionRengeAttack(const float& _delta, GameObject* _entity);
	void CollisionBulletPlayer( GameObject* _entity);
	void DeadEnemy(GameObject* _entity);

	void RemoveEnemy(GameObject* _entity) 
	{
		enemys.erase(std::remove_if(enemys.begin(), enemys.end(),
			[_entity](GameObject* obj)
			{
				return obj == _entity;
			}), enemys.end());
	}


	//GameObject* GetEnemy() { return enemy; }

	static bool GetFlip() { return flip; }

	void Create() override;
	void Delete() override;
	void Physics(const float& _delta) override;
	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;

private:
	GameObject* tileMap = nullptr;
	GameObject* plateform = nullptr;
	GameObject* bulletEnemy = nullptr;
	GameObject* door = nullptr;
	static bool flip;
};

