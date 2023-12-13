#include "Scenes/ScenesGame/SceneGameUnderground.h"

SceneGameUnderground::SceneGameUnderground(const std::string& _newName) : SceneGameAbstract(_newName) {}


void SceneGameUnderground::Preload()
{
	Scene::Preload();

}
void SceneGameUnderground::Create()
{
	Scene::Create();
}
void SceneGameUnderground::Delete()
{
	Scene::Delete();
}

void SceneGameUnderground::Render(sf::RenderWindow* _window)
{
	Scene::Render(_window);
}

void SceneGameUnderground::Update(const float& _delta)
{
	Scene::Update(_delta);
}