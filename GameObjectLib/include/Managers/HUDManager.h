#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class HUDManager
{
public:
	HUDManager();
	inline static sf::View GetHud() { return hudView; }
	inline static void AddGameObjectHud(GameObject* const& _gameObject) { hudGameObjects.push_back(_gameObject); }
	inline static GameObject* GetHudGameObject(const int& _index) { return hudGameObjects[_index]; }
	inline static std::vector<GameObject* > GetHudGameObjects() { return hudGameObjects; }

	inline static sf::Vector2f GetRectangleCenter(const std::string& _key) { return centerRectangle.at(_key); }

	inline static void SetDisplay(const bool& _state) { isShown = _state; }
	inline static bool GetDisplay() { return isShown; }

	static void Render(sf::RenderWindow* _window);
	static void Preload();

private:
	static sf::View hudView;
	static std::map<std::string, sf::Vector2f> centerSquare;
	static std::vector<GameObject* > hudGameObjects;

	static std::vector<sf::Vector2f> column;
	static std::vector<sf::Vector2f> line;
	static float widthRectange, heightRectangle;
	static std::map<std::string, sf::Vector2f> centerRectangle;
	static bool isShown;
};

