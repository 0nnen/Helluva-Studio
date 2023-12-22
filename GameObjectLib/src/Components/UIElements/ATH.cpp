#include "Components/UIElements/ATH.h"
#include "Managers/WindowManager.h"
#include "Managers/HUDManager.h"


ATH::ATH()
{

    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(50, 50);

    healthBarBackground.setFillColor(sf::Color::Black);
    healthBarBackground.setPosition(50, 50);

    weaponFrame.setSize(sf::Vector2f(150, 150)); // Taille du cadre
    weaponFrame.setFillColor(sf::Color::Transparent);
    weaponFrame.setOutlineThickness(2);
    weaponFrame.setOutlineColor(sf::Color::White);
    weaponFrame.setPosition(50, 100);

    if (weaponTexture.loadFromFile("Assets/Graphics/UI/Icons/gun_icon.png")) {
        weaponSprite.setTexture(weaponTexture);
        weaponSprite.setPosition(50, 100);
        weaponSprite.setScale(0.5f, 0.5f);
    }
}

void ATH::SetCharacter(Character* _character)
{
    character = _character;
    maxHealth = character->GetMaxHealthPoint();
    maxHealthBarWidth = maxHealth * 6;
    healthBar.setSize(sf::Vector2f(maxHealthBarWidth, 30));
    healthBarBackground.setSize(sf::Vector2f(maxHealthBarWidth, 30));
}

void ATH::Update(const float& _delta) {
    float healthPercentage = static_cast<float>(character->GetHealthPoint()) / maxHealth;
    healthBar.setSize(sf::Vector2f(maxHealthBarWidth * healthPercentage, 30));

    if (maxHealthBarWidth * healthPercentage > maxHealth * 0.6666f)
    {
        healthBar.setFillColor(sf::Color::Green);
    }
    else if (maxHealthBarWidth * healthPercentage > maxHealth * 0.3333f)
    {
        healthBar.setFillColor(sf::Color::Yellow);
    }
    else
    {
        healthBar.setFillColor(sf::Color::Red);
    }
}

void ATH::Render(sf::RenderWindow* _window) {
    Component::RenderGUI(_window);

    _window->draw(weaponFrame);
    _window->draw(weaponSprite);
    _window->draw(healthBarBackground);
    _window->draw(healthBar);

}