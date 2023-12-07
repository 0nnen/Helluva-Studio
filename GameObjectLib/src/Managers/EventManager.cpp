#include "Managers/EventManager.h"
#include "Managers/WindowManager.h"
#include "Managers/CameraManager.h"
#include "Managers/SceneManager.h"
#include <iostream>

sf::Event EventManager::event = sf::Event();

void EventManager::Update(const float& _delta)
{
	sf::RenderWindow* window = WindowManager::GetWindow();

	while (window->pollEvent(EventManager::event))
	{
		if (event.type == sf::Event::Closed) window->close();
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::LAlt) if (event.key.code == sf::Keyboard::F4) window->close();
		}
		if (SceneManager::GetActiveGameScene() == SceneManager::GetSceneByKey("SceneMainMenu"))
		{
			if (event.key.code == sf::Keyboard::Escape) window->close();
		}
		if (SceneManager::GetActiveGameScene() == SceneManager::GetSceneByKey("SceneGameLVSR"))
		{
			CameraManager::Event(event);
		}
	}
	CameraManager::Update(_delta);
}