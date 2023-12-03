#pragma once

#include <SFML/Graphics.hpp>
class EventManager
{
public:

	static void Update(const float& _delta);
	inline static sf::Event GetEvent() { return event; }
	inline static void SetEvent(const sf::Event& _event) { event = _event; }

private:
	static sf::Event event;
};

