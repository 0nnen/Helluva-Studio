#include "Components/SpriteRenderer.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Managers/AssetManager.h"
#include "Managers/HUDManager.h"
#include "Managers/CameraManager.h"

Sprite::Sprite()
{
	texture.create(100, 100);
	scalex = 1.0f;
	scaley = 1.0f;
}

sf::Vector2f Sprite::GetBounds() const
{
	return sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}
void Sprite::SetTexture(const sf::Texture& _texture)
{
	texture = _texture;
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void Sprite::SetRecTexture(const sf::IntRect& _rectTexture)
{
	rectTexture = _rectTexture;
	sprite.setTextureRect(rectTexture);
}


void Sprite::SetScale(const float& _scalex, const float& _scaley)
{
	scalex = _scalex;
	scaley = _scaley;
	sprite.setScale(scalex, scaley);
}

void Sprite::SetOrigin()
{
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}


void Sprite::Update(const float& _delta) {}

void Sprite::SetSprite()
{
	const auto position = GetOwner()->GetPosition();
	sprite.setPosition(position.x, position.y);
}

void Sprite::Render(sf::RenderWindow* _window)
{

	this->SetSprite();
	Component::Render(_window);
	_window->draw(sprite);
}

void Sprite::RenderGUI(sf::RenderWindow* _window)
{
	this->SetSprite();
	Component::RenderGUI(_window);
	_window->draw(sprite);
}
