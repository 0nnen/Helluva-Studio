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

	void CreateBackground();
	void Create() override;
	void Delete() override;
	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;


	std::vector<GameObject*> GetEnemies() { return enemies; }
	GameObject* GetEnemie(int _index) { return enemies[_index]; }
	std::vector<GameObject*> GetTowers() { return towers; }
	GameObject* GetTowers(int _index) { return towers[_index]; }

protected:
	std::vector<GameObject*> towers;
	std::vector<GameObject*> enemies;
	std::vector<GameObject*> gameTowers;
	GameObject* player = nullptr;
	GameObject* nexus = nullptr;
	GameObject* ressource = nullptr;
	GameObject* ressourceText = nullptr;
	GameObject* pausePlayButton = nullptr;
	GameObject* pauseOptionsButton = nullptr;
	GameObject* pauseMenuPrincipalButton = nullptr;
	GameObject* pauseQuitButton = nullptr;
	GameObject* pauseBongoButton = nullptr;
	GameObject* victory = nullptr;
	GameObject* defeat = nullptr;
	float endTime = 5.f;
	sf::Texture* texture;
	sf::Text text;
};

