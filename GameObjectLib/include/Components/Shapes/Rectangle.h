#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>


class Rectangle final : public Component
{
public:
	Rectangle();
	void Render(sf::RenderWindow* _window) override;
	void RenderGUI(sf::RenderWindow* _window) override;
	void Update(const float& _delta) override;

private:
	sf::RectangleShape rectangle;

};
