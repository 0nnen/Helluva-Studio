#pragma once
#include "Scene.h"

class SceneSuccessMenu : public Scene
{
public:
	SceneSuccessMenu(const std::string& _newName);
	~SceneSuccessMenu();

	void CreateSceneButtonsMenu();

	void SetOrigin();

	void Create() override;
	void Delete() override;
	void Render(sf::RenderWindow* _window) override;
	void Update(const float& _delta) override;

private:
	GameObject* successButton = nullptr;
	GameObject* backButton = nullptr;
	GameObject* firstSuccessButton = nullptr;
	GameObject* firstSuccessBonusButton = nullptr;
	sf::Text text;
};

