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

	virtual void Preload();
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

	float GetFadeInTime() const { return fadeInTime; }
	void SetFadeInTime(const float& _fadeInTime) { fadeInTime = _fadeInTime; }
	void FadeIn(const float& _delta);

	float GetFadeOutTime() const { return fadeOutTime; }
	void SetFadeOutTime(const float& _fadeOutTime) { fadeOutTime = _fadeOutTime; }
	void FadeOut(const float& _delta);

	void ShowFade(sf::RenderWindow* _window);

	void ApplyDepth();

protected:
	std::string name = "DefaultScene";
	std::vector<GameObject*> gameObjects;
	bool isActive = true;


	float fadeInTime = 3.f;
	float fadeOutTime = 3.f;
	bool isFadeIn = false;
	bool isFadeOut = false;
	sf::RectangleShape blackRectangle;
};
