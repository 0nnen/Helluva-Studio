#pragma once
#include "Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

class SceneGameAbstract : public Scene
{
public:
	SceneGameAbstract(const std::string& _newName);
	~SceneGameAbstract();

	void Awake() override;

	//void ManagePause();
	void ManageDefaultButtonsPause(bool _states);
	void CreatePauseMenuButtons();
	void CreateChartacter();

	void Pause();
	void CreateSceneBackgroundOption();

	void CreateBackground();
	void Create() override;
	void Preload() override;
	void Delete() override;
	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;

	GameObject* GetPlayer() { return player; }
	GameObject* GetPlatform() { return platform; }
	std::vector<GameObject*> GetEnemies() { return enemies; }
	GameObject* GetEnemie(int _index) { return enemies[_index]; }

	void SetFirstCollide(const bool& _state) { firstCollide = _state; }
	bool GetFirstCollide() const { return firstCollide; }

protected:
	std::vector<GameObject*> enemies;
	GameObject* player = nullptr;
	GameObject* platform = nullptr;
	GameObject* pausePlayButton = nullptr;
	GameObject* pauseOptionsButton = nullptr;
	GameObject* pauseMenuPrincipalButton = nullptr;
	GameObject* pauseQuitButton = nullptr;
	GameObject* pauseBongoButton = nullptr;
	float endTime = 5.f;
	sf::Texture* texture = nullptr;
	sf::Text text;

	struct AlphaBackkground
	{
		sf::RectangleShape backgroundAlpha;
	};

	AlphaBackkground backgroundAlpha1;
	AlphaBackkground backgroundAlpha2;

	bool firstCollide = true;

	bool isPause = true;
};

