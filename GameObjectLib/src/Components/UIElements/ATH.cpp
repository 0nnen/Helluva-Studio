#include "Components/UIElements/ATH.h"
#include "Managers/WindowManager.h"
#include "Managers/HUDManager.h"


ATH::ATH(Character* character, int maxHealth)
    : character(character), maxHealth(maxHealth), maxHealthBarWidth(100.0f) {

    healthBar.setSize(sf::Vector2f(maxHealthBarWidth, 20));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition(10, 1000);
}

void ATH::Update(float deltaTime) {
    float healthPercentage = static_cast<float>(character->GetHealthPoint()) / maxHealth;
    healthBar.setSize(sf::Vector2f(maxHealthBarWidth * healthPercentage, 20));
}

/*
void ATH::Render(sf::RenderWindow& window) {
    window.draw(healthBar);
}
*/

void ATH::Render(sf::RenderWindow& window) {
    sf::RectangleShape healthBar(sf::Vector2f(character->GetHealthPoint() * 6, 30));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(50, 50);
    window.draw(healthBar);

    sf::RectangleShape weaponFrame;
    weaponFrame.setSize(sf::Vector2f(150, 150)); // Taille du cadre
    weaponFrame.setFillColor(sf::Color::Transparent);
    weaponFrame.setOutlineThickness(2);
    weaponFrame.setOutlineColor(sf::Color::White);
    weaponFrame.setPosition(50, 100);

    sf::Texture weaponTexture;
    sf::Sprite weaponSprite;
    if (weaponTexture.loadFromFile("Assets/Graphics/UI/Icons/gun_icon.png")) {
        weaponSprite.setTexture(weaponTexture);
        weaponSprite.setPosition(50, 100); 
        weaponSprite.setScale(0.5f, 0.5f);

        window.draw(weaponFrame);
        window.draw(weaponSprite);
    }
}

