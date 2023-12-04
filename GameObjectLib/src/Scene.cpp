#include "Scene.h"
#include "Managers/WindowManager.h"
#include "Managers/WindowManager.h"

Scene::Scene(const std::string& _name)
{
	name = _name;
	blackRectangle.setSize(sf::Vector2f(WindowManager::GetFloatWindowWidth(), WindowManager::GetFloatWindowHeight()));
}

//Initialize the scene
void Scene::Preload() {}

//Create Object from the scene
void Scene::Create() {}

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
	if (isFadeIn)
	{
		FadeIn(_delta);
	}
	if (isFadeOut)
	{
		FadeOut(_delta);
	}
}

void Scene::Render(sf::RenderWindow* _window)
{
	this->ApplyDepth();
	for (GameObject* const& gameObject : gameObjects)
	{
		gameObject->Render(_window);
	}
	if (isFadeIn || isFadeOut)
	{
		ShowFade(_window);
	}
}

void Scene::ApplyDepth()
{
	std::sort(gameObjects.begin(), gameObjects.end(), [](const GameObject* obj1, const GameObject* obj2)
		{
			return obj1->GetDepth() < obj2->GetDepth();
		});
}


void Scene::FadeIn(const float& _delta)
{
	blackRectangle.setFillColor(sf::Color::Black);

	// Calculer le taux de variation d'alpha par seconde
	float alphaChangeRate = 255.0f / fadeInTime;

	// Mettre à jour l'alpha du rectangle noir
	sf::Uint8 currentAlpha = blackRectangle.getFillColor().a;
	if (currentAlpha > 0) {
		currentAlpha = static_cast<sf::Uint8>(std::max(0, static_cast<int>(currentAlpha - alphaChangeRate * _delta)));
		blackRectangle.setFillColor(sf::Color(0, 0, 0, currentAlpha));
	}
	else
	{
		blackRectangle.setFillColor(sf::Color::Transparent);
		isFadeIn = false;
	}

}

void Scene::FadeOut(const float& _delta)
{
	blackRectangle.setFillColor(sf::Color::Transparent);
	// Calculer le taux de variation d'alpha par seconde
	float alphaChangeRate = 255.0f / fadeOutTime;

	// Mettre à jour l'alpha du rectangle noir
	sf::Uint8 currentAlpha = blackRectangle.getFillColor().a;
	if (currentAlpha > 0) {
		currentAlpha = static_cast<sf::Uint8>(std::max(0, static_cast<int>(currentAlpha + alphaChangeRate * _delta)));
		blackRectangle.setFillColor(sf::Color(0, 0, 0, currentAlpha));
	}
	else
	{
		blackRectangle.setFillColor(sf::Color::Black);
		isFadeOut = false;
	}
}

void Scene::ShowFade(sf::RenderWindow* _window)
{
	_window->draw(blackRectangle);
}