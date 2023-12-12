#include "Components/Shapes/Triangle.h"

Triangle::Triangle() : base(10.0f), height(10.0f), widthPos(100), heightPos(100), rotation(0)  {
    triangle.setPrimitiveType(sf::Triangles);
    triangle.resize(3);

    // Position du triangle de base
    triangle[0].position = sf::Vector2f(10, 10);
    triangle[1].position = sf::Vector2f(100, 10);
    triangle[2].position = sf::Vector2f(100, 100);

    triangle[0].color = sf::Color::Green;
    triangle[1].color = sf::Color::Green;
    triangle[2].color = sf::Color::Green;
}

void Triangle::Render(sf::RenderWindow* _window) {
    const auto position = GetOwner()->GetPosition();
    Component::Render(_window);
    _window->draw(triangle);
}

void Triangle::RenderGUI(sf::RenderWindow* _window)
{
    const auto position = GetOwner()->GetPosition();
    Component::RenderGUI(_window);
    _window->draw(triangle);
}

void Triangle::Update(const float& _delta)
{
    Component::Update(_delta);

}

void Triangle::SetBase(const float& _base) {
    base = _base;
    triangle[0].position = sf::Vector2f(base, base);
    triangle[1].position = sf::Vector2f(base * base, base);
    triangle[2].position = sf::Vector2f(base * base, base * base);
}

void Triangle::SetHeight(const float& _height) {
    height = _height;
    triangle[0].position = sf::Vector2f(height, height);
    triangle[1].position = sf::Vector2f(height * height, height);
    triangle[2].position = sf::Vector2f(height * height, height * height);
}

void Triangle::SetPositionTriangle(const float& _widthPos, const float& _heightPos, const float& _rotation) {
    widthPos = _widthPos;
    heightPos = _heightPos;
    rotation = _rotation;
    sf::Vector2f offset(_widthPos, _heightPos);

    for (int i = 0; i < 3; ++i) {
        triangle[i].position += offset;
    }

    sf::Vector2f center(_widthPos, _heightPos);

    float angle = _rotation;
    float radians = angle * 3.14159f / 180.f; // Conversion en radians

    // Rotation de chaque point du triangle autour du de la position du triangle
    for (int i = 0; i < 3; ++i) {
        float xOffset = triangle[i].position.x - center.x;
        float yOffset = triangle[i].position.y - center.y;

        triangle[i].position.x = xOffset * cos(radians) - yOffset * sin(radians) + center.x;
        triangle[i].position.y = xOffset * sin(radians) + yOffset * cos(radians) + center.y;
    }
}