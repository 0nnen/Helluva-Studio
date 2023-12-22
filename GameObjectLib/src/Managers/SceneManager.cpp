#include "Managers/SceneManager.h"
#include "Managers/WindowManager.h"
#include "Managers/HUDManager.h"

Scene* SceneManager::activeScene = nullptr;
std::map<std::string, Scene*> SceneManager::scenes;

bool isPaused = false;


void SceneManager::StopScene()
{
	activeScene->Delete();
	activeScene = nullptr;
}

void SceneManager::RunScene(std::string _key)
{
	if (scenes.find(_key) != scenes.end())
	{
		if (activeScene)
		{
			StopScene();
		}
		activeScene = scenes.at(_key);
		activeScene->Preload();
		activeScene->Create();
	}
}


 Scene* SceneManager::GetSceneByKey(const std::string& _key) 
 {
	 if (scenes.find(_key) != scenes.end()) {
		return scenes.at(_key); 
	 }
	 return nullptr;
 }

SceneManager::~SceneManager()
{
	for (const auto scene : scenes)
	{
		delete scene.second;
	}
	if(activeScene) delete activeScene;
	scenes.clear();
}