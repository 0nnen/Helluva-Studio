#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "Scene.h"
#include "Components/Entity/Character.h"

class ATH : public Component 
{
public:
    ATH(Character* character, int maxHealth);
    void Update(float deltaTime);
    void Render(sf::RenderWindow& window);

private:
    Character* character;
    sf::RectangleShape healthBar;
    float maxHealthBarWidth;
    int maxHealth;
};