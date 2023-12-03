#pragma once

#include <SFML/System/Clock.hpp>

class TimeManager
{
public:
	TimeManager() = default;
	~TimeManager() = default;

	static void Init();
	static void Update();

	static float GetDeltaTime();
	static float GetTimeSinceBeginning();

	static sf::Clock GetDeltaClock();
	static sf::Clock GetClockSinceBeginning();

private:
	static sf::Clock deltaClock;
	static sf::Clock clock;

	static float deltaTime;
};

