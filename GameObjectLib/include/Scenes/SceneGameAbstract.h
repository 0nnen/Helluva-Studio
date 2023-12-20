#pragma once
#include "Scene.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>

class SceneGameAbstract : public Scene
{
public:
	SceneGameAbstract(const std::string& _newName);
	~SceneGameAbstract();

	void Pause();
	void Pause(const bool& _state);

	void Awake() override;
	void Create() override;
	void CreatePlayer();
	void CreatePlayer(const float& _positionX, const float& _positionY);
	void Preload() override;
	void Delete() override;
	void Physics(const float& _delta) override;
	void Update(const float& _delta) override;
	void Render(sf::RenderWindow* _window) override;

	GameObject* GetPlayer() { return player; }
	std::vector<GameObject*>GetPlatforms() { return platforms; }
	std::vector<GameObject*> GetEnemies() { return enemies; }
	GameObject* GetEnemie(int _index) { return enemies[_index]; }

	void SetFirstCollide(const bool& _state) { firstCollide = _state; }
	bool GetFirstCollide() const { return firstCollide; }

	GameObject* GetEnemy() { return enemy; }

protected:
	std::vector<GameObject*> enemies;
	GameObject* player = nullptr;
	std::vector<GameObject*> platforms;
	GameObject* pausePlayButton = nullptr;
	GameObject* pauseMenuPrincipalButton = nullptr;
	GameObject* pauseQuitButton = nullptr;
	GameObject* backgroundPause = nullptr;
	float endTime = 5.f;

	GameObject* enemy;

	bool firstCollide = true;
	bool isPause = true;
};

