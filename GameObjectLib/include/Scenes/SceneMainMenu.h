#pragma once
#include "Scene.h"

class SceneMainMenu : public Scene
{
public:
	SceneMainMenu(const std::string& _newName);

	void CreateSceneButtonsMenu();

	void Preload() override;
	void Create() override;
	void Delete() override;
	void Render(sf::RenderWindow* _window) override;
	void Update(const float& _delta) override;
	void activeOption(const bool& _state);
	void activeMenu(const bool& _state);
	~SceneMainMenu();

private:
	GameObject* playButton = nullptr;
	GameObject* worldButton = nullptr;
	GameObject* fadeButton = nullptr;
	GameObject* optionsButton = nullptr;
	GameObject* quitButton = nullptr;
	GameObject* backButton = nullptr;
	GameObject* successButton = nullptr;
	GameObject* rankButton = nullptr;
	GameObject* creditsButton = nullptr;
	GameObject* signupLoginButton = nullptr;
	GameObject* player = nullptr;
	GameObject* bullet = nullptr;
	GameObject* sliderVolume = nullptr;
	GameObject* sliderFPS = nullptr;
	GameObject* buttonPlay = nullptr;
	sf::Texture* texture;
	sf::Texture* textureBullet;
	bool option = false;
};

