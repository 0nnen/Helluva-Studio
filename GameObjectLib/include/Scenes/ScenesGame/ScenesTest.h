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

	void CreatePlatform();
	void Collinding();

	void Create() override;
	void Delete() override;
	void Update(const float& _delta);
	void Render(sf::RenderWindow* _window) override;

private:
	GameObject* tileMap = nullptr;
};

