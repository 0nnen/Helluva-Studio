#pragma once

#include <iostream>
#include <map>

#include "Scene.h"
#include "Scenes/SceneMainMenu.h"
#include "Scenes/SceneGameAbstract.h"

class SceneManager
{
public:

	//Add a new scene to the scene list
	template <typename T>
	inline static void AddScene(const std::string& _key, T* _scene) { SceneManager::scenes.insert(std::make_pair(_key, _scene)); }

	//Run a scene
	static void RunScene(std::string _key);

	//Stop a scene (don't forget to run a scene after calling this function)	
	static void StopScene();

	//Get the current scene
	inline static Scene* GetActiveScene() { return activeScene; }
	inline static SceneGameAbstract* GetActiveGameScene() { return dynamic_cast<SceneGameAbstract*>(activeScene); }
	static Scene* GetSceneByKey(const std::string& _key);

	inline static void SetPause(const bool& _state) { isPaused = _state; }
	inline static bool GetPause() { return isPaused; }


	~SceneManager();

private:
	static std::map<std::string, Scene*> scenes;
	static Scene* activeScene;
	static bool isPaused;
};

