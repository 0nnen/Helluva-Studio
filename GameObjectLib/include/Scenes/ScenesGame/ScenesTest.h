#pragma once

#include "Scenes/SceneGameAbstract.h"
#include "Managers/AssetManager.h"
#include "Managers/WindowManager.h"
#include "Managers/SceneManager.h"

#include "BuildersGameObject/BuilderEntityGameObject.h"
#include "BuildersGameObject/BuilderShapeGameObject.h"

#include "Components/RigidBody2D.h"
#include "TileMap/TileMap.h"

class ScenesTest : public SceneGameAbstract 
{
public:
	ScenesTest(const std::string& _newName);
	~ScenesTest();

	void Awake() override;
	void Preload() override;

	void CreatePlatform();
	void CreateEnemy();
	void CreateRengeEnemy();
	void Collinding();
	void CollindingEntity(GameObject* _entity);
	void CollisionRengePosition(const float& _delta, GameObject* _entity, GameObject* regnePosition);
	void CollisionRengeAttack(const float& _delta, GameObject* _entity, GameObject* _rengeAttack);

	GameObject* GetEnemy() { return enemy; }

	static bool GetFlip() { return flip; }

	void Create() override;
	void Delete() override;
	void Physics(const float& _delta) override;
	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;

private:
	GameObject* tileMap = nullptr;
	GameObject* plateform = nullptr;
	GameObject* rengePosition = nullptr;
	GameObject* rengeAttack = nullptr;
	GameObject* bulletEnemy = nullptr;

	static bool flip;
};

