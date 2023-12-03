#include "Managers/TimeManager.h"

float TimeManager::deltaTime = 0.f;
sf::Clock TimeManager::clock = sf::Clock();
sf::Clock TimeManager::deltaClock = sf::Clock();

void TimeManager::Init()
{
	deltaClock.restart();
	clock.restart();
}

void TimeManager::Update()
{

	const sf::Time delta = deltaClock.restart();
	deltaTime = delta.asSeconds();
}

float TimeManager::GetDeltaTime() 
{
	return deltaTime;
}

float TimeManager::GetTimeSinceBeginning() 
{
	return clock.getElapsedTime().asSeconds();
}

sf::Clock TimeManager::GetDeltaClock() 
{
	return deltaClock;
}

sf::Clock TimeManager::GetClockSinceBeginning() 
{
	return clock;
}
