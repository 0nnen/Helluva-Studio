#pragma once
#include <SFML/Graphics.hpp>


class CameraManager
{
public:

    static void SetWindow(sf::RenderWindow* _window);
    inline static sf::View GetView() { return view; }

    static void Update(const float& _delta);
    static void Event(const sf::Event& event);

    static void Move(const float& offsetX, const float& offsetY);

    static void SetCenter(const float& x, const float& y);

    static void Zoom(const float& factor);

    static void SetZoom(const float& _zoom);

private:
    static sf::RenderWindow* window;
    static sf::View view;
    static float minZoom, zoom, maxZoom;
    static int initialX, initialY;
    static bool isDragging;
    static sf::Vector2i lastMousePos;
};

