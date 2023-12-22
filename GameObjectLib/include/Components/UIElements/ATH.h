#pragma once

#include <SFML/Graphics.hpp>
#include "Component.h"
#include "Scene.h"
#include "Components/Entity/Character.h"

class ATH : public Component
{
public:

    ATH();
    void Update(const float& _delta) override;
    void Render(sf::RenderWindow* window) override;
    void SetCharacter(Character* _character);

private:
    Character* character = nullptr;

    sf::Texture weaponTexture;
    sf::Sprite weaponSprite;
    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape weaponFrame;

    float maxHealthBarWidth;
    int maxHealth;
};