#include "Managers/EventManager.h"
#include "Managers/WindowManager.h"
#include "Managers/CameraManager.h"
#include "Managers/SceneManager.h"
#include "Scenes/SceneGameAbstract.h"
#include "Engine.h"
#include <iostream>

sf::Event EventManager::event = sf::Event();

void EventManager::Update(const float& _delta)
{
	sf::RenderWindow* window = WindowManager::GetWindow();
	Engine* engine = Engine::GetInstance();
	SceneGameAbstract* sceneGame = SceneManager::GetActiveGameScene();
	while (window->pollEvent(EventManager::event))
	{
		if (event.type == sf::Event::Closed) engine->Quit();
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::LAlt) if (event.key.code == sf::Keyboard::F4) engine->Quit();

			if (sceneGame)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					sceneGame->Pause();
				}
				
			}
		}
		if (SceneManager::GetActiveScene() == SceneManager::GetSceneByKey("SceneMainMenu"))
		{
			if (event.key.code == sf::Keyboard::Escape) engine->Quit();
		}
		if (sceneGame)
		{
			if (event.type == sf::Event::LostFocus)
			{
				sceneGame->Pause(true);
			}
		}
	}
	CameraManager::Update(_delta);
}