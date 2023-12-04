#include "Scenes/SceneOpening.h"
#include "Managers/WindowManager.h"
#include "Managers/WindowManager.h"

SceneOpening::SceneOpening() : Scene(std::string("SceneOpening")) {}
SceneOpening::SceneOpening(const std::string& _name) : Scene(_name){}

void SceneOpening::Create() {}



void SceneOpening::Delete()
{
	Scene::Delete();
}

void SceneOpening::Awake()
{
	Scene::Awake();
}

void SceneOpening::Update(const float& _delta)
{
	Scene::Update(_delta);
}

void SceneOpening::Render(sf::RenderWindow* _window)
{
}