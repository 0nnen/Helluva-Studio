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
	virtual void Physics(const float& _delta);
	virtual void Update(const float& _delta);
	virtual void Render(sf::RenderWindow* _window);

	virtual void Awake();

	GameObject* CreateGameObject(const std::string& _name);
	void AddGameObject(GameObject* _gameObject);

	void RemoveGameObject(GameObject* _objectToRemove);

	GameObject* GetGameObject(const std::string& _objectName);
	inline std::vector<GameObject*> GetGameObjectVector() const { return gameObjects; }


	inline bool GetIsActive() const { return isActive; }
	inline void SetIsActive(const bool& _state) { isActive = _state; }
	inline std::string GetName() const { return name; }

	inline float GetFadeInTime() const { return fadeInTimeDefault; }
	inline float GetFadeInTimeActual() const { return fadeInTimeActual; }
	inline void SetFadeInTime(const float& _fadeInTime) { fadeInTimeDefault = _fadeInTime; }
	bool FadeIn(const float& _delta);

	inline float GetFadeOutTime() const { return fadeOutTimeDefault; }
	inline float GetFadeOutTimeActual() const { return fadeOutTimeActual; }
	inline void SetFadeOutTime(const float& _fadeOutTime) { fadeOutTimeDefault = _fadeOutTime; }
	bool FadeOut(const float& _delta);

	void ShowFadeIn(sf::RenderWindow* _window);
	void ShowFadeOut(sf::RenderWindow* _window);

	void ApplyDepth();

protected:
	std::string name = "DefaultScene";
	std::string language;
	std::vector<GameObject*> gameObjects;
	std::vector<GameObject*> backgrounds;
	bool isActive = true;


	float fadeInTimeDefault = 3.f;
	float fadeOutTimeDefault = 3.f;
	float fadeInTimeActual= 0.f;
	float fadeOutTimeActual = 0.f;
	bool isFadeIn = false;
	bool isFadeOut = false;
	sf::RectangleShape fadeInRectangle;
	sf::RectangleShape fadeOutRectangle;
};
