#pragma once

#include "Scenes/SceneGameAbstract.h"

#include "TileMap/TileMap.h"

class SceneGameSpawn : public SceneGameAbstract
{
public:
	SceneGameSpawn(const std::string& _newName);
	~SceneGameSpawn();

	void Awake() override;
	void Preload() override;

	void Create() override;
	void Delete() override;
	void Physics(const float& _delta) override;
	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;

private:
	GameObject* hades = nullptr;
	GameObject* textDialogue = nullptr;
	GameObject* plateform = nullptr;
	float timeBetweenDialogues = 3.f;
	float currentTime = 0.f;
	unsigned int step = 0;
	bool startText = false;
};