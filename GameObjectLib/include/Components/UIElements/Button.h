#pragma once
#include <SFML/Graphics.hpp>
#include "Component.h"
#include "Scene.h"

class Button : public Component
{

public:
	Button();

	void SetOrigin();
	void SetSize();
	void SetSize(const float& _width, const float& _height);
	void SetPosition(const float& _x, const float& _y);
	void SetPosition(const Maths::Vector2f& _position);
	void SetFont(const sf::Font& _font);
	void SetFontSize(const unsigned int& _fontSize);
	void SetText(const std::string& _text, const sf::Color& _color);

	void Render(sf::RenderWindow* _window) override;
	void RenderGUI(sf::RenderWindow* _window) override;

	void Update(const float& _delta) override;
	bool IsClicked();

	~Button();

private:

	float width, height;
	unsigned int fontSize;
	sf::Font font;
	sf::RectangleShape rectangle;
	sf::Text text;
};

