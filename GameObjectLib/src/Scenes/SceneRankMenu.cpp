#include "Scenes/SceneRankMenu.h"
#include "Managers/SceneManager.h"
#include "Managers/WindowManager.h"
#include "Managers/AssetManager.h"

#include "Components/UIElements/Button.h"
#include "BuilderGameObject.h"

SceneRankMenu::SceneRankMenu(const std::string& _newName) : Scene(_newName)
{
	this->Awake();
	Scene::Create();
}

void SceneRankMenu::Create()
{
	Scene::Create();
	sf::Texture backgroundTexture2;

	if (!backgroundTexture2.loadFromFile("../assets/Sprite_LOL/background/background2_lol.png"))
	{
		std::cout << "pas d'image" << std::endl;
	}
	this->CreateSceneButtonsMenu();
}

void SceneRankMenu::Render(sf::RenderWindow* _window)
{
	Scene::Render(_window);
}

void SceneRankMenu::CreateSceneButtonsMenu(){}

void SceneRankMenu::SetOrigin()
{
	float widthScreen = WindowManager::GetWindow()->getSize().x;
	float heightScreen = WindowManager::GetWindow()->getSize().y;

	text.setOrigin(sf::Vector2f(widthScreen / 2, heightScreen / 2));
}

void SceneRankMenu::Update(const float& _delta)
{
	Scene::Update(_delta);
	if (backButton->GetComponent<Button>()->IsClicked())
	{
		SceneManager::RunScene("SceneMainMenu");
	}
}