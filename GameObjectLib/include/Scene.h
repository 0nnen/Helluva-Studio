#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics.hpp>

#include "GameObject.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	explicit Scene(const std::string& _name);

	virtual void Create();
	virtual void Delete();
	virtual void Update(const float& _delta);
	virtual void Render(sf::RenderWindow* _window);

	virtual void Awake();

	GameObject* CreateGameObject(const std::string& _name);

	void RemoveGameObject(GameObject* _objectToRemove);

	GameObject* GetGameObject(const std::string& _objectName);
	inline std::vector<GameObject*> GetGameObjectVector() const { return gameObjects; }


	inline bool GetIsActive() const { return isActive; }
	void SetIsActive(const bool& _state) { isActive = _state; }
	inline std::string GetName() const { return name; }

	void ApplyDepth();

protected:
	std::string name = "DefaultScene";
	std::vector<GameObject*> gameObjects;
	bool isActive = true;
};
