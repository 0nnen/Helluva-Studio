#pragma once
#include "Scene.h"


class SceneGameAbstract : public Scene
{
public:
	SceneGameAbstract(const std::string& _newName);
	~SceneGameAbstract();

	void Awake() override;

	void ManagePause();
	void ManageSceneGameButtonsPause(bool _states);
	void CreatePauseMenuButtons();
	void CreateChartacter();

	void CreateBackground();
	void Create() override;
	void Delete() override;
	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;

	GameObject* GetPlayer() { return player; }
	GameObject* GetPlatform() { return platform; }
	std::vector<GameObject*> GetEnemies() { return enemies; }
	GameObject* GetEnemie(int _index) { return enemies[_index]; }

protected:
	std::vector<GameObject*> enemies;
	GameObject* player = nullptr;
	GameObject* nexus = nullptr;
	GameObject* ressource = nullptr;
	GameObject* platform = nullptr;
	GameObject* ressourceText = nullptr;
	GameObject* pausePlayButton = nullptr;
	GameObject* pauseOptionsButton = nullptr;
	GameObject* pauseMenuPrincipalButton = nullptr;
	GameObject* pauseQuitButton = nullptr;
	GameObject* pauseBongoButton = nullptr;
	GameObject* victory = nullptr;
	GameObject* defeat = nullptr;
	float endTime = 5.f;
	sf::Texture* texture = nullptr;
	sf::Text text;
};

