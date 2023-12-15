#include "Managers/EventManager.h"
#include "Managers/WindowManager.h"
#include "Managers/CameraManager.h"
#include "Managers/SceneManager.h"
#include "Engine.h"
#include <iostream>

sf::Event EventManager::event = sf::Event();

void EventManager::Update(const float& _delta)
{
	sf::RenderWindow* window = WindowManager::GetWindow();
	Engine* engine = Engine::GetInstance();
	while (window->pollEvent(EventManager::event))
	{
		if (event.type == sf::Event::Closed) engine->Quit();
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::LAlt) if (event.key.code == sf::Keyboard::F4) engine->Quit();
			if (SceneManager::GetActiveGameScene())
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					SceneManager::GetActiveGameScene()->Pause();
				}
			}
		}
		if (SceneManager::GetActiveGameScene() == SceneManager::GetSceneByKey("SceneMainMenu"))
		{
			if (event.key.code == sf::Keyboard::Escape) engine->Quit();
		}
	}
	CameraManager::Update(_delta);
}