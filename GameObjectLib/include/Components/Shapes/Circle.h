#include "Component.h"
#include <SFML/Graphics.hpp>

class Circle : public Component {
public:
    Circle();

    void Render(sf::RenderWindow* _window) override;

    void RenderGUI(sf::RenderWindow* _window) override;

    void Update(const float& _delta) override;

    void SetRadius(const float& _radius);

private:
    sf::CircleShape circle;
    float radius = 50.0f;
};
