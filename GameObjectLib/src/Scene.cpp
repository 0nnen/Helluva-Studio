#include "Scene.h"
#include "Managers/WindowManager.h"
#include "Managers/CameraManager.h"
#include "Managers/LanguageManager.h"
#include "BuilderGameObject.h"

#include <iostream>
Scene::Scene(const std::string& _name)
{
	name = _name;
}

//Initialize the scene
void Scene::Preload() 
{
	language = LanguageManager::GetInstance()->GetLanguage();
}

//Create Object from the scene
void Scene::Create() 
{
	CameraManager::DefaultZoom();
	fadeOutRectangle.setSize(sf::Vector2f(WindowManager::GetFloatWindowWidth(), WindowManager::GetFloatWindowHeight()));
	fadeInRectangle.setSize(sf::Vector2f(WindowManager::GetFloatWindowWidth(), WindowManager::GetFloatWindowHeight()));
	fadeOutRectangle.setFillColor(sf::Color::Transparent);
	fadeInRectangle.setFillColor(sf::Color::Black);
}

//Create GameObject
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

void Scene::AddGameObject( GameObject* _gameObject)
{
	gameObjects.push_back(_gameObject);
	this->ApplyDepth();
	
}

//Get GameObject
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

//Remove GameObject
void Scene::RemoveGameObject(GameObject* _objectToRemove)
{
	gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(),
		[_objectToRemove](GameObject* obj)
		{
			return obj == _objectToRemove;
		}), gameObjects.end());
}

//Delete Scene
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

void Scene::Physics(const float& _delta)
{
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Physics(_delta);
	}
}

void Scene::Render(sf::RenderWindow* _window)
{
	this->ApplyDepth();
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}
	if (isFadeIn)
	{
		ShowFadeIn(_window);
	}
	if (isFadeOut)
	{
		ShowFadeOut(_window);
	}
}

void Scene::ApplyDepth()
{
	std::sort(gameObjects.begin(), gameObjects.end(), [](const GameObject* obj1, const GameObject* obj2)
		{
			return obj1->GetDepth() < obj2->GetDepth();
		});
}


bool Scene::FadeIn(const float& _delta)
{
	sf::Uint8 currentAlpha = fadeInRectangle.getFillColor().a;
	if (fadeInTimeDefault > fadeInTimeActual) {
		currentAlpha = static_cast<sf::Uint8>(std::min(255, static_cast<int>(255.0f - 255.0f * (fadeInTimeActual / fadeInTimeDefault))));
		fadeInRectangle.setFillColor(sf::Color(0, 0, 0, currentAlpha));
		fadeInTimeActual += _delta;
		return false;
	}
	else
	{
		fadeInRectangle.setFillColor(sf::Color::Transparent);
		fadeOutRectangle.setFillColor(sf::Color::Transparent);
		isFadeIn = false;
		fadeInTimeActual = 0.0f;
		return true;
	}

}

bool Scene::FadeOut(const float& _delta)
{
	sf::Uint8 currentAlpha = fadeOutRectangle.getFillColor().a;
	if (fadeOutTimeDefault > fadeOutTimeActual) {
		currentAlpha = static_cast<sf::Uint8>(std::min(255, static_cast<int>(255.0f * (fadeOutTimeActual / fadeOutTimeDefault))));
		fadeOutRectangle.setFillColor(sf::Color(0, 0, 0, currentAlpha));
		fadeOutTimeActual += _delta;
		return false;
	}
	else
	{
		fadeOutRectangle.setFillColor(sf::Color::Black);
		fadeInRectangle.setFillColor(sf::Color::Black);
		isFadeOut = false;
		fadeOutTimeActual = 0.f;
		return true;
	}
}

void Scene::ShowFadeIn(sf::RenderWindow* _window)
{
	_window->draw(fadeInRectangle);
}

void Scene::ShowFadeOut(sf::RenderWindow* _window)
{
	_window->draw(fadeOutRectangle);
}