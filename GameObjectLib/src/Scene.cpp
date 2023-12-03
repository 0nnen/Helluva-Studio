#include "Scene.h"
#include "Managers/WindowManager.h"
#include "Managers/WindowManager.h"

Scene::Scene(const std::string& _name) 
{
	name = _name;
}

void Scene::Create() {}

GameObject* Scene::CreateGameObject(const std::string& _name)
{
	GameObject* const gameObject = new GameObject();
	gameObject->SetName(_name);
	gameObject->SetActive(true);
	gameObject->SetVisible(true);
	gameObjects.push_back(gameObject);
	this->ApplyDepth();
	return gameObject;
}



GameObject* Scene::GetGameObject(const std::string& _objectName)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		if (gameObject->GetName() == _objectName)
		{
			return gameObject;
		}
	}
	return nullptr;
}

void Scene::RemoveGameObject(GameObject* _objectToRemove)
{
	gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
		[_objectToRemove](GameObject* obj)
		{
			return obj == _objectToRemove;
		}), gameObjects.end());
}

void Scene::Delete() 
{
	for (GameObject* const& gameObject : this->gameObjects)
	{
		delete gameObject;
	}
	gameObjects.clear();
}

void Scene::Awake() 
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update(const float& _delta)
{
	if (isActive)
	{
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Update(_delta);
		}
	}
}

void Scene::Render(sf::RenderWindow* _window)
{
	this->ApplyDepth();
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}
}

void Scene::ApplyDepth()
{
	std::sort(gameObjects.begin(), gameObjects.end(), [](const GameObject* obj1, const GameObject* obj2)
		{
		return obj1->GetDepth() < obj2->GetDepth();
		});
}