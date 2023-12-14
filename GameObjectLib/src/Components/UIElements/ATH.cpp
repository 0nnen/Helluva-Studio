#include "Components/UIElements/ATH.h"
#include "Managers/WindowManager.h"
#include "Managers/HUDManager.h"


ATH::ATH(Character* character, int maxHealth)
    : character(character), maxHealth(maxHealth), maxHealthBarWidth(200.0f) {

    healthBar.setSize(sf::Vector2f(maxHealthBarWidth, 20));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition(10, 1000);
}

void ATH::Update(float deltaTime) {
    float healthPercentage = static_cast<float>(character->GetHealth()) / maxHealth;
    healthBar.setSize(sf::Vector2f(maxHealthBarWidth * healthPercentage, 20));
}

/*
void ATH::Render(sf::RenderWindow& window) {
    window.draw(healthBar);
}
*/

void ATH::Render(sf::RenderWindow& window) {
    sf::RectangleShape healthbar(sf::Vector2f(600, 30));
    healthbar.setFillColor(sf::Color::Green);
    healthbar.setPosition(50, 50);
    window.draw(healthbar);

    sf::RectangleShape weaponFrame;
    weaponFrame.setSize(sf::Vector2f(150, 150)); // Taille du cadre
    weaponFrame.setFillColor(sf::Color::Transparent);
    weaponFrame.setOutlineThickness(2);
    weaponFrame.setOutlineColor(sf::Color::White);
    weaponFrame.setPosition(50, 100);

    sf::Texture weaponTexture;
    sf::Sprite weaponSprite;
    if (weaponTexture.loadFromFile("../Assets/Graphics/UI/Icons/gun_icon.png")) {
        weaponSprite.setTexture(weaponTexture);
        weaponSprite.setPosition(50, 100); 
        weaponSprite.setScale(0.5f, 0.5f);

        // Dessin du cadre et de l'image
        window.draw(weaponFrame);
        window.draw(weaponSprite);
    }
}

