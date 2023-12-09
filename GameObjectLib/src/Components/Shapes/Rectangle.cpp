#include "Components/Shapes/Rectangle.h"

Rectangle::Rectangle()
{
	rectangle.setFillColor(sf::Color::Green);
}
void Rectangle::Render(sf::RenderWindow* _window)
{
	const auto position = GetOwner()->GetPosition();
	rectangle.setPosition(position.x, position.y);
	Component::Render(_window);
	_window->draw(rectangle);
}

void Rectangle::RenderGUI(sf::RenderWindow* _window)
{
	const auto position = GetOwner()->GetPosition();
	rectangle.setPosition(position.x, position.y);
	Component::RenderGUI(_window);
	_window->draw(rectangle);
}

void Rectangle::Update(const float& _delta)
{
	Component::Update(_delta);

}

void Rectangle::SetSize(const float& _width, const float& _height)
{
	width = _width;
	height = _height;
	rectangle.setSize(sf::Vector2f(width, height));
	rectangle.setOrigin(sf::Vector2f(width / 2, height / 2));
}

void Rectangle::SetScale(const float& _scaleX, const float& _scaleY)
{
	scaleX = _scaleX;
	scaleY = _scaleY;
	rectangle.setScale(sf::Vector2f(scaleX, scaleY));
}