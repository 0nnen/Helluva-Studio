#include "Components/Shapes/Circle.h"

Circle::Circle()
{
	circle.setFillColor(sf::Color::Transparent);
}

void Circle::Render(sf::RenderWindow* _window)
{
    const auto position = GetOwner()->GetPosition();
    circle.setPosition(position.x, position.y);
    Component::Render(_window);
    _window->draw(circle);
}

void Circle::RenderGUI(sf::RenderWindow* _window)
{
    const auto position = GetOwner()->GetPosition();
    circle.setPosition(position.x, position.y);
    Component::RenderGUI(_window);
    _window->draw(circle);
}

void Circle::Update(const float& _delta)
{
    Component::Update(_delta);
}

void Circle::SetRadius(const float& _radius)
{
    radius = _radius;
    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
}