#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"
#include "Scene.h"

class Carre : public Component
{

public:

	Carre();

	void Render(sf::RenderWindow* _window) override;
	void RenderGUI(sf::RenderWindow* _window) override;

	bool IsClicked();
	inline void SetOrigin() { square.setOrigin(sf::Vector2f(side / 2, side / 2)); }

	void SetColor(const sf::Color& _fillColor);
	sf::Color GetFillColor() const { return fillColor; }

	void SetOutline(const float& _outlineThickness, const sf::Color& _outlineColor);
	inline float GetOutlineThickness() const { return outlineThickness; }
	inline sf::Color GetOutlineColor() const { return outlineColor; }


	void SetSize(const float& _side);
	inline float GetSize() const { return side; }

	sf::RectangleShape GetSquare() const { return square;  }

private:

	sf::RectangleShape square;

	float side;
	float outlineThickness;

	sf::Color fillColor;
	sf::Color outlineColor;
};

