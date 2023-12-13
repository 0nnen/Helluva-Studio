#include "Scenes/SceneLoginSignup.h"
#include "Managers/WindowManager.h"
#include "Managers/SceneManager.h"
#include "Managers/AssetManager.h"
#include "Components/UIElements/Button.h"
#include "BuilderGameObject.h"

SceneLoginSignup::SceneLoginSignup(const std::string& _newName) : Scene(_newName)
{
	this->Create();
}

void SceneLoginSignup::Preload()
{
	Scene:Preload();
	AssetManager::AddAsset("BackgroundLogin", "../assets/bgMenu.png");
}

void SceneLoginSignup::Create() 
{
	Scene::Create();

	GameObject* background = BuilderGameObject::CreateBackgroundGameObject("Background", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, 1.0f, 1.0f, AssetManager::GetAsset("BackgroundLogin"));
	loginName = BuilderGameObject::CreateInputGameObject("loginName", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 8);
	loginPassWord = BuilderGameObject::CreateInputGameObject("loginPassWord", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 7);
	buttonLogin = BuilderGameObject::CreateButtonGameObject("buttonLogin", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 6, 30);
	signupName = BuilderGameObject::CreateInputGameObject("signupName", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 5);
	signupPassWord = BuilderGameObject::CreateInputGameObject("signupPassWord", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 4);
	buttonSignup = BuilderGameObject::CreateButtonGameObject("buttonSignup", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 3, 30);
	buttonReturn = BuilderGameObject::CreateButtonGameObject("Retour", WindowManager::GetWindowWidth() / 15, WindowManager::GetWindowHeight() / 13, 20);
}

void SceneLoginSignup::Update(const float& _delta)
{
	Scene::Update(_delta);
	if (buttonReturn->GetComponent<Button>()->IsClicked() && buttonReturn->GetActive()) 
	{
		SceneManager::RunScene("SceneMainMenu");
	}
}

void SceneLoginSignup::Render(sf::RenderWindow* _window)
{
	Scene::Render(_window);
}
