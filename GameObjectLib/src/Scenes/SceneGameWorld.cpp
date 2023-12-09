#include "Scenes/SceneGameWorld.h"
#include "BuilderGameObject.h"
#include "BuildersGameObject/BuilderEntityGameObject.h"

SceneGameWorld::SceneGameWorld(const std::string& _newName) : SceneGameAbstract(_newName) {}

void SceneGameWorld::Preload()
{
	SceneGameAbstract::Preload();
	AssetManager::AddAsset("BackgroundMapBackgroundWorld", "../Assets/worldMapBackground.png");
	AssetManager::AddAsset("BackgroundMapWorld", "../Assets/worldMap1.png");
}

void SceneGameWorld::Create()
{
	SceneGameAbstract::Create();
	//GameObject* backgroundWorldMap = BuilderGameObject::CreateBackgroundGameObject("BackgroundMapWorld1", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, AssetManager::GetAsset("BackgroundMapBackgroundWorld"));
	//GameObject* backgroundWorldMap2 = BuilderGameObject::CreateBackgroundGameObject("BackgroundMapWorld2", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 2, AssetManager::GetAsset("BackgroundMapWorld"));
	//this->CreateSceneButtonsMenu();
	this->CreateChartacter();
	plateform = BuilderEntityGameObject::CreatePlateformGameObject("plateform", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 1.2, 5, 2);
	this->CreateSceneBackgroundOption();
}

void SceneGameWorld::CreateSceneButtonsMenu()
{
	creditsButton = BuilderGameObject::CreateButtonGameObject("Crédits", WindowManager::GetWindowWidth() / 2, WindowManager::GetWindowHeight() / 13, 20);
	backButton = BuilderGameObject::CreateButtonGameObject("Retourrrrrrrrrrrr", WindowManager::GetWindowWidth() / 2.1, WindowManager::GetWindowHeight() / 13, 25);
}

void SceneGameWorld::Delete()
{
	Scene::Delete();
}

void SceneGameWorld::Render(sf::RenderWindow* _window)
{
	Scene::Render(_window);
	_window->draw(isPause ? backgroundAlpha2.backgroundAlpha : backgroundAlpha1.backgroundAlpha);
}

void SceneGameWorld::Update(const float& _delta)
{
	SceneGameAbstract::Update(_delta);
	if (player && plateform)
	{
		if (RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(plateform->GetComponent<RigidBody2D>())) && firstCollide)
		{
			player->GetComponent<RigidBody2D>()->SetIsGravity(false);
			firstCollide = false;
		}
		else if (!RigidBody2D::IsColliding(*(player->GetComponent<RigidBody2D>()), *(plateform->GetComponent<RigidBody2D>())))
		{
			firstCollide = true;
		}
	}

}