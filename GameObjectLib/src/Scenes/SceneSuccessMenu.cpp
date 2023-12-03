#include "Scenes/SceneSuccessMenu.h"
#include "Managers/SceneManager.h"
#include "Managers/WindowManager.h"
#include "Managers/AssetManager.h"

#include "Components/UIElements/Button.h"

#include "BuilderGameObject.h"

SceneSuccessMenu::SceneSuccessMenu(const std::string& _newName) : Scene(_newName)
{
	this->Awake();
	Scene::Create();
}

SceneSuccessMenu::~SceneSuccessMenu() 
{
	this->Delete();
}

void SceneSuccessMenu::Create() 
{
	Scene::Create();
	sf::Texture backgroundTexture2;

	if (!backgroundTexture2.loadFromFile("../assets/Sprite_LOL/background/background2_lol.png"))
	{
		std::cout << "pas d'image" << std::endl;
	}
	GameObject* background2 = BuilderGameObject::CreateBackgroundGameObject("Background2", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, backgroundTexture2);
	this->CreateSceneButtonsMenu();
}

void SceneSuccessMenu::Delete() 
{
	Scene::Delete();
}

void SceneSuccessMenu::Render(sf::RenderWindow* _window) 
{
	Scene::Render(_window);
}

void SceneSuccessMenu::CreateSceneButtonsMenu() 
{
	successButton = BuilderGameObject::CreateButtonGameObject("Success", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 10, 50);
	backButton = BuilderGameObject::CreateButtonGameObject("Retour", WindowManager::GetWindowWidth() / 15, WindowManager::GetWindowHeight() / 13, 20);
	firstSuccessButton = BuilderGameObject::CreateButtonGameObject("\tNombre de partie gagne", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 3.5, 70);
}

void SceneSuccessMenu::SetOrigin() 
{
	text.setOrigin(sf::Vector2f(WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2));
}

void SceneSuccessMenu::Update(const float& _delta)
{
	Scene::Update(_delta);
	if (firstSuccessButton->GetComponent<Button>()->IsClicked()) 
	{
		std::cout << "texte" << std::endl;
	}
	if (backButton->GetComponent<Button>()->IsClicked()) 
	{
		SceneManager::RunScene("SceneMainMenu");
	}
}