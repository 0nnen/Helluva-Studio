#include "Scenes/SceneGameWorld.h"
#include "BuilderGameObject.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"

SceneGameWorld::SceneGameWorld(const std::string& _newName) : SceneGameAbstract(_newName) {}

void SceneGameWorld::Preload()
{
	Scene::Preload();
	AssetManager::AddAsset("BackgroundMapBackgroundWorld", "../Assets/worldMapBackground.png");
	AssetManager::AddAsset("BackgroundMapWorld", "../Assets/worldMap1.png");
}

void SceneGameWorld::Create()
{
	Scene::Create();
	GameObject* backgroundWorldMap = BuilderGameObject::CreateBackgroundGameObject("BackgroundMapWorld1", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, AssetManager::GetAsset("BackgroundMapBackgroundWorld"));
	GameObject* backgroundWorldMap2 = BuilderGameObject::CreateBackgroundGameObject("BackgroundMapWorld2", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, AssetManager::GetAsset("BackgroundMapWorld"));
	//this->CreateSceneButtonsMenu();
	plateform = BuilderEntityGameObject::CreatePlateformGameObject("plateform", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 1.2, 5,2);
	this->CreateSceneBackgroundOption();
	this->CreatePauseMenuButtons();
}

void SceneGameWorld::CreateSceneButtonsMenu()
{
	creditsButton = BuilderGameObject::CreateButtonGameObject("Cr�dits", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 13, 20);
	backButton = BuilderGameObject::CreateButtonGameObject("Retourrrrrrrrrrrr", WindowManager::GetWindowWidth() / 2.1, WindowManager::GetWindowHeight() / 13, 25);
}

void SceneGameWorld::Delete()
{
	Scene::Delete();
}

void SceneGameWorld::Render(sf::RenderWindow* _window)
{
	Scene::Render(_window);
	_window->draw(SceneGameAbstract::isPause ? backgroundAlpha2.backgroundAlpha : backgroundAlpha1.backgroundAlpha);
}

void SceneGameWorld::Update(const float& _delta)
{
	Scene::Update(_delta);
	SceneGameAbstract::Update(_delta);
}