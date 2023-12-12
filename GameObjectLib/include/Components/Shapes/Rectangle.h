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

	void SetSize(const float& _width, const float& _height);
	void SetScale(const float& _scaleX, const float& _scaleY);
private:
	float width = 0.f;
	float height = 0.f;
	float scaleX = 0.f;
	float scaleY = 0.f;
	sf::RectangleShape rectangle;

};
