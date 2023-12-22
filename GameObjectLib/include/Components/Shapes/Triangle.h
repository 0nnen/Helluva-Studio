#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

class Triangle : public Component {

public:
    Triangle();

    void Render(sf::RenderWindow* _window) override;
    void RenderGUI(sf::RenderWindow* _window) override;
    void Update(const float& _delta) override;

    void SetBase(const float& _base);
    void SetHeight(const float& _height);
    void SetPositionTriangle(const float& _widthPos, const float& _heightPos, const float& _rotation);

private:
    sf::VertexArray triangle;
    float base;
    float height;
    float widthPos;
    float heightPos;
    float rotation;

};