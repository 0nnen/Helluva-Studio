#include "Scenes/SceneGameWorld.h"
#include "BuilderGameObject.h"

SceneGameWorld::SceneGameWorld(const std::string& _newName) : SceneGameAbstract(_newName) {}

void SceneGameWorld::Preload()
{
	Scene::Preload();
	AssetManager::AddAsset("BackgroundMapWorld", "../Assets/worldMap.png");
}
void SceneGameWorld::Create()
{
	Scene::Create();
	GameObject* backgroundWorldMap = BuilderGameObject::CreateBackgroundGameObject("BackgroundMapWorld1", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, *AssetManager::GetAsset("BackgroundMapWorld"));
	//this->CreateSceneButtonsMenu();
	this->CreateSceneBackgroundOption();
}

void SceneGameWorld::CreateSceneButtonsMenu()
{
	creditsButton = BuilderGameObject::CreateButtonGameObject("Crédits", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 13, 20);
	backButton = BuilderGameObject::CreateButtonGameObject("Retourrrrrrrrrrrr", WindowManager::GetWindowWidth() / 2.1, WindowManager::GetWindowHeight() / 13, 25);
}

void SceneGameWorld::CreateSceneBackgroundOption()
{
	backgroundAlpha.setSize(sf::Vector2f(WindowManager::GetFloatWindowWidth(), WindowManager::GetFloatWindowHeight()));
	backgroundAlpha.setOrigin(sf::Vector2f(WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() / 2));
	backgroundAlpha.setFillColor(sf::Color(0, 0, 0, 112));
	backgroundAlpha.setPosition(WindowManager::GetFloatWindowWidth() / 2, WindowManager::GetFloatWindowHeight() / 2);
}

void SceneGameWorld::ShowFadeWorldOption(sf::RenderWindow* _window)
{
	_window->draw(backgroundAlpha);
}

void SceneGameWorld::Delete()
{
	Scene::Delete();
}

void SceneGameWorld::Render(sf::RenderWindow* _window)
{
	Scene::Render(_window);

	ShowFadeWorldOption(_window);
}

void SceneGameWorld::Update(const float& _delta)
{
	Scene::Update(_delta);
}