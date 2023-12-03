#include "Component.h"
#include "Managers/CameraManager.h"
#include "Managers/HUDManager.h"

Component::Component(GameObject* owner)
{
	this->owner = owner;
}
void Component::Start() {}

void Component::Update(const float& _delta) {}

void Component::Render(sf::RenderWindow* _window) 
{
	_window->setView(CameraManager::GetView());
}

void Component::RenderGUI(sf::RenderWindow* _window)
{
	_window->setView(HUDManager::GetHud());
}

void Component::RenderBackground(sf::RenderWindow* _window)
{
	_window->setView(CameraManager::GetView());
}