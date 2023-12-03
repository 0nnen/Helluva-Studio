#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "Scene.h"



class Input : public Component
{

public:
	Input();

	void SetInput(unsigned int fontSize);
	void SetOrigin();
	void SetSize(float _width, float _height);
	void SetPosition(float _x, float _y);

	bool IsClicked();

	void Render(sf::RenderWindow* _window) override;
	void RenderGUI(sf::RenderWindow* _window) override;
	void Update(const float& _delta) override;

	~Input();

private:
	float width, height;
	sf::Font font;
	sf::RectangleShape rectangle;
	sf::Text text;
	sf::FloatRect textBounds;
	bool isEnteringText = false;
};

