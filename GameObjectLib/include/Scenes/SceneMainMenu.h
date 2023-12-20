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
	void ActiveOption(const bool& _state);
	void ActiveMenu(const bool& _state);
	~SceneMainMenu();

private:
	GameObject* playButton = nullptr;
	GameObject* worldButton = nullptr;
	GameObject* fadeButton = nullptr;
	GameObject* optionsButton = nullptr;
	GameObject* quitButton = nullptr;
	GameObject* englishButton = nullptr;
	GameObject* frenchButton = nullptr;
	GameObject* backButton = nullptr;
	//GameObject* successButton = nullptr;
	//GameObject* rankButton = nullptr;
	//GameObject* creditsButton = nullptr;
	GameObject* signupLoginButton = nullptr;
	GameObject* sliderVolume = nullptr;
	GameObject* sliderFPS = nullptr;
	bool option = false;
};

