#include "Managers/WindowManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

int WindowManager::fps = 60;
int WindowManager::minFps = 30;
int WindowManager::maxFps = 240;
sf::RenderWindow* WindowManager::window = nullptr;

void WindowManager::Init()
{
	window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "HELLUVA REVENGE", sf::Style::Fullscreen);
}