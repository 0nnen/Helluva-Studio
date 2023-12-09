#pragma once

#include "Scenes/SceneGameAbstract.h"
#include "Managers/SceneManager.h"
#include "Managers/AssetManager.h"
#include <Managers/WindowManager.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>


class SceneGameWorld : public SceneGameAbstract
{
public:
	SceneGameWorld(const std::string& _newName);

	void Preload() override;
	void Create() override;
	void Delete() override;

	void CreateSceneButtonsMenu();

	void Render(sf::RenderWindow* _window) override;
	void Update(const float& _delta) override;

private:
	GameObject* backButton = nullptr;
	GameObject* creditsButton = nullptr;
	GameObject* plateform = nullptr;
};